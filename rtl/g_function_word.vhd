library ieee;
use ieee.std_logic_1164.all;

entity g_function_word is
generic
(
    N_round : natural := 1
);
port
(
    word_in : in std_logic_vector(31 downto 0);
    word_out: out std_logic_vector(31 downto 0)
);
end g_function_word;

architecture g_function_word_arch of g_function_word is
    -- Declarative section

    type round_constant_words is array (1 to 10) of std_logic_vector(31 downto 0);
    constant ROUND_CONSTANT : round_constant_words :=
    (
        x"01000000",
        x"02000000",
        x"04000000",
        x"08000000",
        x"10000000",
        x"20000000",
        x"40000000",
        x"80000000",
        x"1B000000",
        x"36000000"
    );

    component substitute_N_bytes is
    generic
    (
        N_bytes : natural := 4
    );
    port
    (
        data_in: in std_logic_vector((N_bytes * 8 - 1) downto 0);
        data_out: out std_logic_vector((N_bytes * 8 - 1) downto 0)
    );
    end component;

    signal rot_word: std_logic_vector(31 downto 0);
    signal sub_word: std_logic_vector(31 downto 0);
    signal rc_word:  std_logic_vector(31 downto 0);

begin
    -- Descriptive section.

    -- First step: Rotate 8 bits to the left (ie 0xabcd1234 would become 0xcd1234ab)
    rot_word <= word_in(23 downto 0) & word_in(31 downto 24);

    -- Second step: Substitute each byte with the corresponding S-Box value
    S_BOX : substitute_N_bytes
    generic map
    (
        N_bytes => 4
    )
    port map
    (
        data_in => rot_word,
        data_out => sub_word
    );

    -- Third step: Perform a XOR operation with the round constant
    rc_word <= sub_word xor ROUND_CONSTANT(N_round);

    -- Done!
    word_out <= rc_word;

end g_function_word_arch;