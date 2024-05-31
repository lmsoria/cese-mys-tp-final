library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity s_boxes_tb is
end s_boxes_tb;

architecture s_boxes_tb_arq of s_boxes_tb is
    -- Declarative section

    component s_box is
    port
    (
        byte_in : in std_logic_vector (7 downto 0);
        byte_out : out std_logic_vector (7 downto 0)
    );
    end component;

    signal tb_in: std_logic_vector(7 downto 0) := x"00";
    signal tb_out: std_logic_vector(7 downto 0);

    signal clk: std_logic := '0';
    signal counter: unsigned(7 downto 0) := x"00";

begin
    -- Descriptive section
    DUT: s_box
    port map
    (
        byte_in => tb_in,
        byte_out => tb_out
    );

    -- Increment tb_in every 10 ns
    clk <= not clk after 5 ns;
    tb_in_process: process(clk)
    begin
        if rising_edge(clk) then
            if counter < x"FF" then
                counter <= counter + 1;
            else
                counter <= (others => '0');
            end if;

            tb_in <= std_logic_vector(counter);
        end if;
    end process;
end;