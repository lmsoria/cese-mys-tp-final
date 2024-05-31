library ieee;
use ieee.std_logic_1164.all;


entity aes_shift_rows_tb is
end aes_shift_rows_tb;

architecture aes_shift_rows_tb_arch of aes_shift_rows_tb is
    -- Declarative section
    component aes_shift_rows is
    port
    (
        state_in : in std_logic_vector (127 downto 0);
        result_out : out std_logic_vector (127 downto 0)
    );
    end component;

    component aes_inverse_shift_rows is
    port
    (
        state_in : in std_logic_vector (127 downto 0);
        result_out : out std_logic_vector (127 downto 0)
    );
    end component;

    signal tb_state_in: std_logic_vector(127 downto 0) := (others => '0');
    signal tb_result_out: std_logic_vector(127 downto 0);

begin
    -- Descriptive section

    stimulus_process: process
    begin
        -- expected output (normal):   x"00 05 0a 0f 04 09 0e 03 08 0d 02 07 0c 01 06 0b"
        -- expected output (inverted): x"00 0d 0a 07 04 01 0e 0b 08 05 02 0f 0c 09 06 03"
        tb_state_in <= x"000102030405060708090a0b0c0d0e0f";
        wait for 100 ns;

        -- expected output (normal):   x"00 55 aa ff 44 99 ee 33 88 dd 22 77 cc 11 66 bb"
        -- expected output (inverted): x"00 dd aa 77 44 11 ee bb 88 55 22 ff cc 99 66 33"
        tb_state_in <= x"00112233445566778899aabbccddeeff";
        wait for 100 ns;

        -- expected output (normal):   x"ff aa 55 00 bb 66 11 cc 77 22 dd 88 33 ee 99 44"
        -- expected output (inverted): x"ff 22 55 88 bb ee 11 44 77 aa dd 00 33 66 99 cc"
        tb_state_in <= x"ffeeddccbbaa99887766554433221100";
        wait for 100 ns;
        wait; -- Wait indefinitely
    end process stimulus_process;

    SHIFT_ROWS: aes_shift_rows
    port map
    (
        state_in => tb_state_in,
        result_out => tb_result_out
    );

end aes_shift_rows_tb_arch;