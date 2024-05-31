library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity multipliers_tb is
end multipliers_tb;

architecture multipliers_tb_arch of multipliers_tb is
    -- Declarative section

    component multiply_by_1_2_and_3 is
    port
    (
        byte_in : in std_logic_vector (7 downto 0);
        byte_by_1_out : out std_logic_vector (7 downto 0);
        byte_by_2_out : out std_logic_vector (7 downto 0);
        byte_by_3_out : out std_logic_vector (7 downto 0)
    );
    end component;

    signal tb_in: std_logic_vector(7 downto 0) := x"00";
    signal tb_by_1_out: std_logic_vector(7 downto 0);
    signal tb_by_2_out: std_logic_vector(7 downto 0);
    signal tb_by_3_out: std_logic_vector(7 downto 0);
begin
    -- Descriptive section

        stimulus_process: process
        begin
            tb_in <= x"D4";
            wait for 100 ns;

            tb_in <= x"BF";
            wait for 100 ns;

            tb_in <= x"5D";
            wait for 100 ns;

            tb_in <= x"30";
            wait for 100 ns;

            wait; -- Wait indefinitely
        end process stimulus_process;

    BY_1_2_AND_3: multiply_by_1_2_and_3
    port map
    (
        byte_in => tb_in,
        byte_by_1_out => tb_by_1_out,
        byte_by_2_out => tb_by_2_out,
        byte_by_3_out => tb_by_3_out
    );
end;