library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity substitute_N_bytes_tb is
end substitute_N_bytes_tb;

architecture substitute_N_bytes_tb_arch of substitute_N_bytes_tb is
    -- Declarative section

    constant N_BYTES_TB : natural :=4;

    component substitute_N_bytes is
    generic
    (
        N_bytes : natural := 4
    );

    port
    (
        data_in : in std_logic_vector ((N_bytes * 8 - 1) downto 0);
        data_out : out std_logic_vector ((N_bytes * 8 - 1) downto 0)
    );
    end component;

    signal tb_data_in: std_logic_vector((N_BYTES_TB*8 - 1) downto 0) := x"00000000";
    signal tb_data_out: std_logic_vector((N_BYTES_TB*8 - 1) downto 0);

    signal clk: std_logic := '1';
    signal counter: unsigned(31 downto 0) := x"00000000";

begin
    -- Descriptive section
    DUT: substitute_N_bytes
    generic map
    (
        N_bytes => N_BYTES_TB
    )
    port map
    (
        data_in => tb_data_in,
        data_out => tb_data_out
    );

    -- Increment tb_data_in every 20 ns
    clk <= not clk after 10 ns;

    tb_in_process: process(clk)
    begin
        if rising_edge(clk) then
            if counter < x"FFFFFFFF" then
                counter <= counter + 1;
            else
                counter <= (others => '0');
            end if;

            tb_data_in <= std_logic_vector(counter);
        end if;
    end process;
end;