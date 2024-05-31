library ieee;
use ieee.std_logic_1164.all;

entity aes_encoder_logic_tb is
end aes_encoder_logic_tb;

architecture aes_encoder_logic_arch_tb of aes_encoder_logic_tb is
    -- Declarative section
    component aes_encoder_logic is
    port
    (
        plain_text_in: in std_logic_vector(127 downto 0);
        key_in: in std_logic_vector(127 downto 0);
        cipher_text_out: out std_logic_vector(127 downto 0)
    );
    end component;

    signal tb_plain_text_in: std_logic_vector(127 downto 0) := (others => '0');
    signal tb_key_in: std_logic_vector(127 downto 0) := (others => '0');
    signal tb_cipher_text_inout: std_logic_vector(127 downto 0);

begin
    -- Descriptive section
    stimulus_process: process
    begin
        tb_plain_text_in <= x"00000101030307070f0f1f1f3f3f7f7f"; -- expected output: x"c7 d1 24 19 48 9e 3b 62 33 a2 c5 a7 f4 56 31 72"
        tb_key_in <= x"00000000000000000000000000000000";
        wait for 50 ns;
        tb_key_in <= x"00000000000000000000000000000001";        -- expected output: x"7f 0a 53 34 27 a3 37 f8 7f 3c 3d 22 cd 9d 0a 08"
        wait for 50 ns;
        tb_plain_text_in <= x"3b7f8dc2a0e555b2a8becc612844bfc1"; -- expected output: x"ac 4d b6 2c 51 ce d0 3b ec 40 05 e5 55 93 67 bb"
        wait for 50 ns;
        tb_key_in <= x"00000000000000000000000012345678";
        wait; -- Wait indefinitely
    end process stimulus_process;

    AES128_ENCODER: aes_encoder_logic
    port map
    (
        plain_text_in => tb_plain_text_in,
        key_in => tb_key_in,
        cipher_text_out => tb_cipher_text_inout
    );

end aes_encoder_logic_arch_tb;