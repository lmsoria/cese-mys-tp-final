library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity g_function_word_tb is
end g_function_word_tb;

architecture g_function_word_tb_arch of g_function_word_tb is
    -- Declarative section

    constant N_ROUNDS : natural := 10;

    component g_function_word is
    generic
    (
        N_round : natural := 1
    );
    port
    (
        word_in : in std_logic_vector(31 downto 0);
        word_out: out std_logic_vector(31 downto 0)
    );
    end component;

    signal tb_word_in: std_logic_vector(31 downto 0) := x"abcd1234";

    type word_array is array (natural range <>) of std_logic_vector(31 downto 0);
    signal tb_word_outs: word_array(0 to N_ROUNDS-1);

begin
    -- Descriptive section

        -- Stimulus process. Just try with 0xabcd1234 and 0x1234abcd
        stimulus_process: process
        begin
            tb_word_in <= x"abcd1234";
            wait for 100 ns;

            tb_word_in <= x"1234abcd";
            wait for 100 ns;

            tb_word_in <= x"abcd1234";
            wait for 100 ns;
            wait; -- Wait indefinitely
        end process stimulus_process;

    -- Instantiate g_function_word DUTs and connect them
    DUTs: for i in 0 to N_ROUNDS-1 generate
        DUT_i: g_function_word
        generic map
        (
            N_round => i + 1
        )
        port map
        (
            word_in => tb_word_in,
            word_out => tb_word_outs(i)
        );
    end generate;
end;