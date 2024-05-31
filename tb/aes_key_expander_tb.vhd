library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity aes_key_expander_tb is
end aes_key_expander_tb;

architecture aes_key_expander_tb_arch of aes_key_expander_tb is
    -- Declarative section

    -- Taken from Appendix A of https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
    constant KEY : std_logic_vector(127 downto 0) := x"2b7e151628aed2a6abf7158809cf4f3c";

    component aes_key_expander is
    port
    (
        clk_in : in std_logic;
        rst_in : in std_logic;
        key_in: in std_logic_vector(127 downto 0);  -- 16 bytes key
        round_keys_out: out std_logic_vector((128*11) - 1 downto 0) -- We generate 11 round keys as result
    );
    end component;

    signal tb_key: std_logic_vector(127 downto 0) := KEY;
    signal tb_clk: std_logic := '0';
    signal tb_rst: std_logic := '0';
    signal tb_round_keys: std_logic_vector((128*11) - 1 downto 0);
begin
    -- Descriptive section
    tb_clk <= not tb_clk after 10 ns;

    -- Instantiate g_function_word DUTs and connect them
    DUT: aes_key_expander
    port map
    (
        clk_in => tb_clk,
        rst_in => tb_rst,
        key_in => tb_key,
        round_keys_out => tb_round_keys
    );
end;