library ieee;
use ieee.std_logic_1164.all;

entity aes_round is
port
(
    state_in: in std_logic_vector(127 downto 0);
    key_in: in std_logic_vector(127 downto 0);
    result_out: out std_logic_vector(127 downto 0)
);
end aes_round;

architecture aes_round_arch of aes_round is
    -- Declarative section

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

    component aes_mix_columns is
    port
    (
        state_in: in std_logic_vector(127 downto 0);
        result_out: out std_logic_vector(127 downto 0)
    );
    end component;

    signal substituted_bytes: std_logic_vector(127 downto 0);
    signal shifted_rows: std_logic_vector(127 downto 0);
    signal mixed_columns: std_logic_vector(127 downto 0);

begin
    SUB_BYTES : aes_sub_bytes
    port map
    (
        state_in => state_in,
        result_out => substituted_bytes
    );

    SHIFT_ROWS : aes_shift_rows
    port map
    (
        state_in => substituted_bytes,
        result_out => shifted_rows
    );

    MIX_COLUMNS : aes_mix_columns
    port map
    (
        state_in => shifted_rows,
        result_out => mixed_columns
    );

    result_out <= mixed_columns xor key_in;

end aes_round_arch;