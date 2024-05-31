library ieee;
use ieee.std_logic_1164.all;

entity aes_sub_bytes is
port
(
    state_in: in std_logic_vector(127 downto 0);
    result_out: out std_logic_vector(127 downto 0)
);
end aes_sub_bytes;

architecture aes_sub_bytes_arch of aes_sub_bytes is
    -- Declarative section
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

begin
    -- Descriptive section.
    SUB_16_BYTES : substitute_N_bytes
    generic map
    (
        N_bytes => 16
    )
    port map
    (
        data_in => state_in,
        data_out => result_out
    );
end aes_sub_bytes_arch;