library ieee;
use ieee.std_logic_1164.all;

entity aes_mix_columns is
port
(
    state_in : in std_logic_vector (127 downto 0);
    result_out : out std_logic_vector (127 downto 0)
);
end aes_mix_columns;

architecture aes_mix_columns_arch of aes_mix_columns is
    -- Declarative section

    -- Standard 4x4 matrix which holds 16x 8-bit values (128 bits in total).
    type matrix is array(15 downto 0) of std_logic_vector(7 downto 0);

    -- Intermediate signals used to hold the "results" of the operations.
    signal input_vector : matrix;
    signal times_1 : matrix;
    signal times_2 : matrix;
    signal times_3 : matrix;
    signal result : matrix;

    component multiply_by_1_2_and_3 is
    port
    (
        byte_in : in std_logic_vector (7 downto 0);
        byte_by_1_out : out std_logic_vector (7 downto 0);
        byte_by_2_out : out std_logic_vector (7 downto 0);
        byte_by_3_out : out std_logic_vector (7 downto 0)
    );
    end component;

    begin
    -- Descriptive section.

    -- Map the 128-bit plain bus into 16 vectors of 8 bits, and connect these bytes to the multipliers.
    state_to_matrix: for i in 15 downto 0 generate
        -- If input_vector = [ab cd 12 34 | ff aa ff bb | ...] then consider:
        -- [ab cd 12 34] as the first vector (aka input_vector(0), the first element of the array),
        -- [ff aa ff bb] as the second vector (aka input_vector(1), the second element of the array) and so on.
        input_vector(15-i) <= state_in((8*i)+7 downto (8*i));
        MULTIPLIER_i: multiply_by_1_2_and_3
        port map
        (
            byte_in  => input_vector(i),
            byte_by_1_out => times_1(i),
            byte_by_2_out => times_2(i),
            byte_by_3_out => times_3(i)
        );
    end generate;

    -- Perform the matrix multiplication by summing up (ie XOR'ing) the coefficients for each element
    matrix_multiplication: for i in 0 to 3 generate
        result(i*4 + 0) <= times_2(i*4 + 0) xor times_3(i*4 + 1) xor times_1(i*4 + 2) xor times_1(i*4 + 3); -- Row 0 [2 3 1 1].
        result(i*4 + 1) <= times_1(i*4 + 0) xor times_2(i*4 + 1) xor times_3(i*4 + 2) xor times_1(i*4 + 3); -- Row 1 [1 2 3 1].
        result(i*4 + 2) <= times_1(i*4 + 0) xor times_1(i*4 + 1) xor times_2(i*4 + 2) xor times_3(i*4 + 3); -- Row 2 [1 1 2 3].
        result(i*4 + 3) <= times_3(i*4 + 0) xor times_1(i*4 + 1) xor times_1(i*4 + 2) xor times_2(i*4 + 3); -- Row 3 [3 1 1 2].
    end generate;

    -- Now that we have the results, let's convert the vectors back to a 128-bit bus
    matrix_to_result: for i in 15 downto 0 generate
        result_out(((8*i) + 7) downto (8*i)) <= result(15 - i);
    end generate;

end aes_mix_columns_arch;