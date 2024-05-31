library ieee;
use ieee.std_logic_1164.all;

entity multiply_by_1_2_and_3 is
port
(
    byte_in : in std_logic_vector (7 downto 0);
    byte_by_1_out : out std_logic_vector (7 downto 0);
    byte_by_2_out : out std_logic_vector (7 downto 0);
    byte_by_3_out : out std_logic_vector (7 downto 0)
);
end multiply_by_1_2_and_3;


architecture multiply_by_1_2_and_3_arch of multiply_by_1_2_and_3 is
-- Declarative section

    signal original_byte: std_logic_vector(7 downto 0);
    signal shifted_byte: std_logic_vector(7 downto 0);
    signal multiplied_byte: std_logic_vector(7 downto 0);
    signal msb: std_logic;
begin
    -- Descriptive section.
    msb <= byte_in(7);
    original_byte <= byte_in;
    shifted_byte <= byte_in(6 downto 0) & '0';

    -- multiplication by one is trivial. We put this just for demonstration purposes
    byte_by_1_out <= original_byte;

    -- multiplication of a value by 2 can be implemented as a 1-bit left shift followed by a conditional
    -- bitwise XOR with {1B - 0001 1011} if the leftmost bit of the original value (before the shift) is 1.
    with msb select
    multiplied_byte <= shifted_byte when '0',
                       shifted_byte xor x"1B" when '1',
                       (others => 'X') when others;

    byte_by_2_out <= multiplied_byte;

    -- multiplication by three can be thought as the sum of the multiplication by two and the original value.
    byte_by_3_out <= multiplied_byte xor original_byte;

end multiply_by_1_2_and_3_arch;