library ieee;
use ieee.std_logic_1164.all;

entity aes_shift_rows is
port
(
    state_in : in std_logic_vector (127 downto 0);
    result_out : out std_logic_vector (127 downto 0)
);
end aes_shift_rows;

architecture aes_shift_rows_arch of aes_shift_rows is
    -- Declarative section
    begin
    -- Descriptive section.

    -- Input, as a 128 bit bus:
    -- +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    -- | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0a | 0b | 0c | 0d | 0e | 0f |
    -- +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+

    -- The same input, but represented in column-major order:
    -- +----+----+----+----+
    -- | 00 | 04 | 08 | 0c |
    -- +----+----+----+----+
    -- | 01 | 05 | 09 | 0d |
    -- +----+----+----+----+
    -- | 02 | 06 | 0a | 0e |
    -- +----+----+----+----+
    -- | 03 | 07 | 0b | 0f |
    -- +----+----+----+----+

    -- Output after performing the shift-row operation
    -- +----+----+----+----+
    -- | 00 | 04 | 08 | 0c |
    -- +----+----+----+----+
    -- | 05 | 09 | 0d | 01 |
    -- +----+----+----+----+
    -- | 0a | 0e | 02 | 0c |
    -- +----+----+----+----+
    -- | 0f | 03 | 07 | 0b |
    -- +----+----+----+----+

    -- The same output, now as a 128 bit bus:
    -- +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    -- | 00 | 05 | 0a | 0f | 04 | 09 | 0e | 03 | 08 | 0d | 02 | 07 | 0c | 01 | 06 | 0b |
    -- +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+

    result_out(127 downto 120) <= state_in(127 downto 120);
    result_out(119 downto 112) <= state_in(87 downto 80);
    result_out(111 downto 104) <= state_in(47 downto 40);
    result_out(103 downto 96)  <= state_in(7 downto 0);
    result_out(95 downto 88)   <= state_in(95 downto 88);
    result_out(87 downto 80)   <= state_in(55 downto 48);
    result_out(79 downto 72)   <= state_in(15 downto 8);
    result_out(71 downto 64)   <= state_in(103 downto 96);
    result_out(63 downto 56)   <= state_in(63 downto 56);
    result_out(55 downto 48)   <= state_in(23 downto 16);
    result_out(47 downto 40)   <= state_in(111 downto 104);
    result_out(39 downto 32)   <= state_in(71 downto 64);
    result_out(31 downto 24)   <= state_in(31 downto 24);
    result_out(23 downto 16)   <= state_in(119 downto 112);
    result_out(15 downto 8)    <= state_in(79 downto 72);
    result_out(7 downto 0)     <= state_in(39 downto 32);

end aes_shift_rows_arch;