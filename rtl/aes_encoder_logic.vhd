library ieee;
use ieee.std_logic_1164.all;

entity aes_encoder_logic is
port
(
    plain_text_in: in std_logic_vector(127 downto 0);
    key_in: in std_logic_vector(127 downto 0);
    cipher_text_out: out std_logic_vector(127 downto 0)
);
end aes_encoder_logic;

architecture aes_encoder_logic_arch of aes_encoder_logic is

    -- Declarative section
    type round_data is array (1 to 9) of std_logic_vector(127 downto 0);
    type key_array is array(0 to 10) of std_logic_vector(127 downto 0);

    component aes_key_expander is
    port
    (
        key_in: in std_logic_vector(127 downto 0);  -- 16 bytes key
        round_keys_out: out std_logic_vector((128*11) - 1 downto 0) -- We generate 11 round keys as result
    );
    end component;

    component aes_round is
    port
    (
        state_in: in std_logic_vector(127 downto 0);
        key_in: in std_logic_vector(127 downto 0);
        result_out: out std_logic_vector(127 downto 0)
    );
    end component;

    component aes_sub_bytes is
    port
    (
        state_in: in std_logic_vector(127 downto 0);
        result_out: out std_logic_vector(127 downto 0)
    );
    end component;

    component aes_shift_rows is
    port
    (
        state_in: in std_logic_vector(127 downto 0);
        result_out: out std_logic_vector(127 downto 0)
    );
    end component;

    signal round_keys: std_logic_vector((128*11) - 1 downto 0);
    signal substituted_bytes: std_logic_vector(127 downto 0);
    signal shifted_rows: std_logic_vector(127 downto 0);
    signal keys : key_array;
    signal round_inputs: round_data;
    signal round_outputs: round_data;

begin

    -- 01. Instantiate aes_key_expander
    KEY_EXPANDER : aes_key_expander
    port map
    (
        key_in => key_in,
        round_keys_out => round_keys
    );

    -- 02. Route the expanded key (1408 bits) to individual keys (11 x 128bits)
    EXPAND_KEYS: for i in 0 to 10 generate
        keys(i) <= round_keys( (128*(11-i) - 1) downto (128*(10-i)) );
    end generate;

    -- 03. Instantiate the rounds 1 to 9 and connect them to the signal arrays
    GENERATE_ROUNDS: for i in 1 to 9 generate
    ROUND_i: aes_round
    port map
    (
        state_in => round_inputs(i),
        key_in => keys(i),
        result_out => round_outputs(i)
    );
    end generate;

    -- 04. Connect each round input with the previous round's output, with exception
    -- of the first round which is the XOR operation between the plain text and the original key
    round_inputs(1) <= plain_text_in xor keys(0);
    CONNECT_ROUNDS: for i in 2 to 9 generate
        round_inputs(i) <= round_outputs(i - 1);
    end generate;

    -- 05. The last round (number 10) is quite similar, but without the MixColumns step.
    -- We're doing it manually

    -- 05.01: Substitute bytes from the last round
    SUB_BYTES : aes_sub_bytes
    port map
    (
        state_in => round_outputs(9),
        result_out => substituted_bytes
    );

    -- 05.02: Shift rows
    SHIFT_ROWS : aes_shift_rows
    port map
    (
        state_in => substituted_bytes,
        result_out => shifted_rows
    );

    -- 05.03: Add last round key, and with this we have the cipher text!
    cipher_text_out <= shifted_rows xor keys(10);

end aes_encoder_logic_arch;