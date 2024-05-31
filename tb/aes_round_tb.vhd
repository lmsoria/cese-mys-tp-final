library ieee;
use ieee.std_logic_1164.all;

entity aes_rounds_tb is
end aes_rounds_tb;

architecture aes_rounds_arch_tb of aes_rounds_tb is
    -- Declarative section
    component aes_round is
    port
    (
        state_in: in std_logic_vector(127 downto 0);
        key_in: in std_logic_vector(127 downto 0);
        result_out: out std_logic_vector(127 downto 0)
    );
    end component;

    signal tb_state_in: std_logic_vector(127 downto 0) := (others => '0');
    signal tb_key_in: std_logic_vector(127 downto 0) := (others => '0');
    signal tb_result_out: std_logic_vector(127 downto 0);

begin
    -- Descriptive section
    stimulus_process: process
    begin
        tb_state_in <= x"00000101030307070f0f1f1f3f3f7f7f"; -- expected output: x"3b 7f 8d c2 a0 e5 55 b2 a8 be cc 61 28 44 bf c1"
        tb_key_in <= x"62636363626363636263636362636363";
        wait for 100 ns;
        tb_state_in <= x"3b7f8dc2a0e555b2a8becc612844bfc1"; -- expected output: x"07 76 bd 96 e6 61 ca 7d 43 bc a2 bc ef 80 d4 1d"
        tb_key_in <= x"9b9898c9f9fbfbaa9b9898c9f9fbfbaa";
        wait; -- Wait indefinitely
    end process stimulus_process;

    ROUND: aes_round
    port map
    (
        state_in => tb_state_in,
        key_in => tb_key_in,
        result_out => tb_result_out
    );

end aes_rounds_arch_tb;