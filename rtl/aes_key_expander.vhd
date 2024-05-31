library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity aes_key_expander is
port
(
    key_in: in std_logic_vector(127 downto 0);  -- 16 bytes key
    round_keys_out: out std_logic_vector((128*11) - 1 downto 0) -- We generate 11 round keys as result
);
end aes_key_expander;

architecture aes_key_expander_arch of aes_key_expander is
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

    -- We need to generate 44 32-bit keys (4 first words are the the actual key, and the remaining ones are generated)
    type key_words is array (0 to 4*(N_ROUNDS + 1) - 1) of std_logic_vector(31 downto 0);
    signal words : key_words := (others => (others => '0'));

    -- We need to perform the g() function to 9 words (3, 7, 11, 15, 19, 23, 27, 31, 35 and 39)
    type generated_words is array (0 to N_ROUNDS - 1) of std_logic_vector(31 downto 0);
    signal g_words : generated_words := (others => (others => '0'));

begin
    -- Descriptive section

    -- 01. Instantiate g_function_word DUTs and connect them
    G_FUNCTIONS: for i in 0 to N_ROUNDS-1 generate
    G_FUNCTION_i: g_function_word
    generic map
    (
        N_round => i + 1
    )
    port map
    (
        word_in => words(4*i + 3),
        word_out => g_words(i)
    );
    end generate;

    -- 02. Connect all the words between them to expand the key
    words(0) <= key_in(127 downto 96);
    words(1) <= key_in(95 downto 64);
    words(2) <= key_in(63 downto 32);
    words(3) <= key_in(31 downto 0);

    CONNECT_WORDS: for i in 1 to (N_ROUNDS) generate
        words(4*i + 0) <= words(4*(i-1)) xor g_words(i-1);
        words(4*i + 1) <= words(4*(i-1) + 1) xor words(4*i + 0);
        words(4*i + 2) <= words(4*(i-1) + 2) xor words(4*i + 1);
        words(4*i + 3) <= words(4*(i-1) + 3) xor words(4*i + 2);
    end generate;

    -- 03. Join the words into round_keys_out. Is there a better way of doing this?
    round_keys_out <=
        words(0)  & words(1)  & words(2)  & words(3)  &
        words(4)  & words(5)  & words(6)  & words(7)  &
        words(8)  & words(9)  & words(10) & words(11) &
        words(12) & words(13) & words(14) & words(15) &
        words(16) & words(17) & words(18) & words(19) &
        words(20) & words(21) & words(22) & words(23) &
        words(24) & words(25) & words(26) & words(27) &
        words(28) & words(29) & words(30) & words(31) &
        words(32) & words(33) & words(34) & words(35) &
        words(36) & words(37) & words(38) & words(39) &
        words(40) & words(41) & words(42) & words(43);

end aes_key_expander_arch;