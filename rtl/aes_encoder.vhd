library ieee;
use ieee.std_logic_1164.all;

entity aes_encoder is
port
(
    clk_in: in std_logic;
    rst_in: in std_logic;

    plain_text_in: in std_logic_vector(127 downto 0);
    key_in: in std_logic_vector(127 downto 0);
    cipher_text_out: out std_logic_vector(127 downto 0)
);
end aes_encoder;

architecture aes_encoder_arch of aes_encoder is
    -- Declarative section
    component aes_encoder_logic is
    port
    (
        plain_text_in: in std_logic_vector(127 downto 0);
        key_in: in std_logic_vector(127 downto 0);
        cipher_text_out: out std_logic_vector(127 downto 0)
    );
    end component;

    -- signal plain_text: std_logic_vector(127 downto 0);
    -- signal key: std_logic_vector(127 downto 0);
    -- signal cipher_text: std_logic_vector(127 downto 0);

begin

    -- AES: aes_encoder_logic
    -- port map
    -- (
    --     plain_text_in => plain_text,
    --     key_in => key,
    --     cipher_text_out => cipher_text
    -- );

    process(clk_in, rst_in)
    begin
        if rising_edge(clk_in) then
            if rst_in = '0' then
                cipher_text_out <= x"a5a5a5a5ffffffff5a5a5a5affffffff";
                -- cipher_text_out <= (others => '0');
            else
                cipher_text_out <= x"DEADBEEFDEADBEEFDEADBEEFDEADBEEF";
                -- cipher_text_out <= cipher_text;
            end if;

            -- plain_text <= plain_text_in;
            -- key <= key_in;
        end if;
    end process;

end aes_encoder_arch;