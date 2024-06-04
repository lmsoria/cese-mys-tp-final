from Crypto.Cipher import AES
import asyncio
import glob
import serial
import sys

# This python script open a serial port, and prompts the user for a key.
# Then, it will isten to incoming data and try to decode it using AES-128
# If we're able to decode the data as an ASCII character, we print it in green.
# Otherwise, we print the raw decoded output in red

# ANSI escape code for green text
GREEN = '\033[92m'

# ANSI escape code for red text
RED = '\033[91m'

# ANSI escape code to reset text color
RESET = '\033[0m'

# Packet buffer, where we store incoming data
packets = []

def serial_ports():
    """ Lists serial port names

        :raises EnvironmentError:
            On unsupported or unknown platforms
        :returns:
            A list of the serial ports available on the system
    """
    if sys.platform.startswith('win'):
        ports = ['COM%s' % (i + 1) for i in range(256)]
    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this excludes your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')
    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')
    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

# This function fires whenever data is received over the serial port.
async def handle_serial_data():
    global uart
    while True:
        # Ensure we read exactly 16 bytes
        if uart.in_waiting >= 16:
            data = uart.read(16)
            if data:
                packets.append(data)
        await asyncio.sleep(0.1)

# Function to allow us to await a packet
async def wait_for_packet():
    while not packets:
        await asyncio.sleep(0.1)
    return packets.pop(0)

def pad_key(key):
    """Pad the key to be 16 bytes by adding zeroes."""
    if len(key) > 16:
        return key[:16]
    elif len(key) < 16:
        return key.ljust(16, b'\0')
    return key

# Do everything in an async function so we can have loops, awaits etc
async def main():
    global uart
    print("Available Serial Ports:")
    for port in serial_ports():
        print("    > {}".format(port))

    # Prompt the user for the UART port
    user_input = input("Select Port: ")
    print("Opening port {} at 115200 bauds, 8N1".format(user_input))
    uart = serial.Serial(user_input, 115200)

    # Prompt the user for the key
    key_text = input("Enter a key (16 bytes): ").strip()
    try:
        # Convert text key to bytes
        key_bytes = key_text.encode('utf-8')
        # Pad the key with zeroes if necessary
        key_bytes = pad_key(key_bytes)
    except binascii.Error:
        print("Invalid key format. Ensure it's a text string.")
        exit(1)

    # Initialize AES cipher in ECB mode with the provided key
    cipher = AES.new(key_bytes, AES.MODE_ECB)

    # Start the serial data handling coroutine
    serial_task = asyncio.create_task(handle_serial_data())
    print('Waiting for packets...')

    while True:
        packet = await wait_for_packet()
        decrypted_packet = cipher.decrypt(packet)
        try:
            # Try to decode the decrypted packet as ASCII
            ascii_decoded_packet = decrypted_packet.decode('ascii')
            # Print ASCII decoded packet in green without newline
            print(GREEN + ascii_decoded_packet + RESET, end='', flush=False)
            # Exception to the rule: if we get a newline, we indeed need to print a newline.
            if '\n' in ascii_decoded_packet or '\r' in ascii_decoded_packet:
                print()
        except UnicodeDecodeError:
            # If we fail to decode the ASCII character, just print the raw hex message in red
            hex_packet = decrypted_packet.hex()
            print(RED + hex_packet + RESET, end='\n', flush=False)
        # Flush output to ensure it appears immediately
        sys.stdout.flush()

if __name__ == '__main__':
    asyncio.run(main())
