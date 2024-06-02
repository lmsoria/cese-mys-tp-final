library ieee;
use ieee.std_logic_1164.all;

entity s_box is
port
(
    byte_in : in std_logic_vector (7 downto 0);
    byte_out : out std_logic_vector (7 downto 0)
);
end s_box;

architecture s_box_arch of s_box is
    -- Declarative section
begin
    -- Descriptive section
    process(byte_in) is
    begin
        case byte_in is
            when x"00" => byte_out <= x"63";
            when x"01" => byte_out <= x"7C";
            when x"02" => byte_out <= x"77";
            when x"03" => byte_out <= x"7B";
            when x"04" => byte_out <= x"F2";
            when x"05" => byte_out <= x"6B";
            when x"06" => byte_out <= x"6F";
            when x"07" => byte_out <= x"C5";
            when x"08" => byte_out <= x"30";
            when x"09" => byte_out <= x"01";
            when x"0A" => byte_out <= x"67";
            when x"0B" => byte_out <= x"2B";
            when x"0C" => byte_out <= x"FE";
            when x"0D" => byte_out <= x"D7";
            when x"0E" => byte_out <= x"AB";
            when x"0F" => byte_out <= x"76";

            when x"10" => byte_out <= x"CA";
            when x"11" => byte_out <= x"82";
            when x"12" => byte_out <= x"C9";
            when x"13" => byte_out <= x"7D";
            when x"14" => byte_out <= x"FA";
            when x"15" => byte_out <= x"59";
            when x"16" => byte_out <= x"47";
            when x"17" => byte_out <= x"F0";
            when x"18" => byte_out <= x"AD";
            when x"19" => byte_out <= x"D4";
            when x"1A" => byte_out <= x"A2";
            when x"1B" => byte_out <= x"AF";
            when x"1C" => byte_out <= x"9C";
            when x"1D" => byte_out <= x"A4";
            when x"1E" => byte_out <= x"72";
            when x"1F" => byte_out <= x"C0";

            when x"20" => byte_out <= x"B7";
            when x"21" => byte_out <= x"FD";
            when x"22" => byte_out <= x"93";
            when x"23" => byte_out <= x"26";
            when x"24" => byte_out <= x"36";
            when x"25" => byte_out <= x"3F";
            when x"26" => byte_out <= x"F7";
            when x"27" => byte_out <= x"CC";
            when x"28" => byte_out <= x"34";
            when x"29" => byte_out <= x"A5";
            when x"2A" => byte_out <= x"E5";
            when x"2B" => byte_out <= x"F1";
            when x"2C" => byte_out <= x"71";
            when x"2D" => byte_out <= x"D8";
            when x"2E" => byte_out <= x"31";
            when x"2F" => byte_out <= x"15";

            when x"30" => byte_out <= x"04";
            when x"31" => byte_out <= x"C7";
            when x"32" => byte_out <= x"23";
            when x"33" => byte_out <= x"C3";
            when x"34" => byte_out <= x"18";
            when x"35" => byte_out <= x"96";
            when x"36" => byte_out <= x"05";
            when x"37" => byte_out <= x"9A";
            when x"38" => byte_out <= x"07";
            when x"39" => byte_out <= x"12";
            when x"3A" => byte_out <= x"80";
            when x"3B" => byte_out <= x"E2";
            when x"3C" => byte_out <= x"EB";
            when x"3D" => byte_out <= x"27";
            when x"3E" => byte_out <= x"B2";
            when x"3F" => byte_out <= x"75";

            when x"40" => byte_out <= x"09";
            when x"41" => byte_out <= x"83";
            when x"42" => byte_out <= x"2C";
            when x"43" => byte_out <= x"1A";
            when x"44" => byte_out <= x"1B";
            when x"45" => byte_out <= x"6E";
            when x"46" => byte_out <= x"5A";
            when x"47" => byte_out <= x"A0";
            when x"48" => byte_out <= x"52";
            when x"49" => byte_out <= x"3B";
            when x"4A" => byte_out <= x"D6";
            when x"4B" => byte_out <= x"B3";
            when x"4C" => byte_out <= x"29";
            when x"4D" => byte_out <= x"E3";
            when x"4E" => byte_out <= x"2F";
            when x"4F" => byte_out <= x"84";

            when x"50" => byte_out <= x"53";
            when x"51" => byte_out <= x"D1";
            when x"52" => byte_out <= x"00";
            when x"53" => byte_out <= x"ED";
            when x"54" => byte_out <= x"20";
            when x"55" => byte_out <= x"FC";
            when x"56" => byte_out <= x"B1";
            when x"57" => byte_out <= x"5B";
            when x"58" => byte_out <= x"6A";
            when x"59" => byte_out <= x"CB";
            when x"5A" => byte_out <= x"BE";
            when x"5B" => byte_out <= x"39";
            when x"5C" => byte_out <= x"4A";
            when x"5D" => byte_out <= x"4C";
            when x"5E" => byte_out <= x"58";
            when x"5F" => byte_out <= x"CF";

            when x"60" => byte_out <= x"D0";
            when x"61" => byte_out <= x"EF";
            when x"62" => byte_out <= x"AA";
            when x"63" => byte_out <= x"FB";
            when x"64" => byte_out <= x"43";
            when x"65" => byte_out <= x"4D";
            when x"66" => byte_out <= x"33";
            when x"67" => byte_out <= x"85";
            when x"68" => byte_out <= x"45";
            when x"69" => byte_out <= x"F9";
            when x"6A" => byte_out <= x"02";
            when x"6B" => byte_out <= x"7F";
            when x"6C" => byte_out <= x"50";
            when x"6D" => byte_out <= x"3C";
            when x"6E" => byte_out <= x"9F";
            when x"6F" => byte_out <= x"A8";

            when x"70" => byte_out <= x"51";
            when x"71" => byte_out <= x"A3";
            when x"72" => byte_out <= x"40";
            when x"73" => byte_out <= x"8F";
            when x"74" => byte_out <= x"92";
            when x"75" => byte_out <= x"9D";
            when x"76" => byte_out <= x"38";
            when x"77" => byte_out <= x"F5";
            when x"78" => byte_out <= x"BC";
            when x"79" => byte_out <= x"B6";
            when x"7A" => byte_out <= x"DA";
            when x"7B" => byte_out <= x"21";
            when x"7C" => byte_out <= x"10";
            when x"7D" => byte_out <= x"FF";
            when x"7E" => byte_out <= x"F3";
            when x"7F" => byte_out <= x"D2";

            when x"80" => byte_out <= x"CD";
            when x"81" => byte_out <= x"0C";
            when x"82" => byte_out <= x"13";
            when x"83" => byte_out <= x"EC";
            when x"84" => byte_out <= x"5F";
            when x"85" => byte_out <= x"97";
            when x"86" => byte_out <= x"44";
            when x"87" => byte_out <= x"17";
            when x"88" => byte_out <= x"C4";
            when x"89" => byte_out <= x"A7";
            when x"8A" => byte_out <= x"7E";
            when x"8B" => byte_out <= x"3D";
            when x"8C" => byte_out <= x"64";
            when x"8D" => byte_out <= x"5D";
            when x"8E" => byte_out <= x"19";
            when x"8F" => byte_out <= x"73";

            when x"90" => byte_out <= x"60";
            when x"91" => byte_out <= x"81";
            when x"92" => byte_out <= x"4F";
            when x"93" => byte_out <= x"DC";
            when x"94" => byte_out <= x"22";
            when x"95" => byte_out <= x"2A";
            when x"96" => byte_out <= x"90";
            when x"97" => byte_out <= x"88";
            when x"98" => byte_out <= x"46";
            when x"99" => byte_out <= x"EE";
            when x"9A" => byte_out <= x"B8";
            when x"9B" => byte_out <= x"14";
            when x"9C" => byte_out <= x"DE";
            when x"9D" => byte_out <= x"5E";
            when x"9E" => byte_out <= x"0B";
            when x"9F" => byte_out <= x"DB";

            when x"A0" => byte_out <= x"E0";
            when x"A1" => byte_out <= x"32";
            when x"A2" => byte_out <= x"3A";
            when x"A3" => byte_out <= x"0A";
            when x"A4" => byte_out <= x"49";
            when x"A5" => byte_out <= x"06";
            when x"A6" => byte_out <= x"24";
            when x"A7" => byte_out <= x"5C";
            when x"A8" => byte_out <= x"C2";
            when x"A9" => byte_out <= x"D3";
            when x"AA" => byte_out <= x"AC";
            when x"AB" => byte_out <= x"62";
            when x"AC" => byte_out <= x"91";
            when x"AD" => byte_out <= x"95";
            when x"AE" => byte_out <= x"E4";
            when x"AF" => byte_out <= x"79";

            when x"B0" => byte_out <= x"E7";
            when x"B1" => byte_out <= x"C8";
            when x"B2" => byte_out <= x"37";
            when x"B3" => byte_out <= x"6D";
            when x"B4" => byte_out <= x"8D";
            when x"B5" => byte_out <= x"D5";
            when x"B6" => byte_out <= x"4E";
            when x"B7" => byte_out <= x"A9";
            when x"B8" => byte_out <= x"6C";
            when x"B9" => byte_out <= x"56";
            when x"BA" => byte_out <= x"F4";
            when x"BB" => byte_out <= x"EA";
            when x"BC" => byte_out <= x"65";
            when x"BD" => byte_out <= x"7A";
            when x"BE" => byte_out <= x"AE";
            when x"BF" => byte_out <= x"08";

            when x"C0" => byte_out <= x"BA";
            when x"C1" => byte_out <= x"78";
            when x"C2" => byte_out <= x"25";
            when x"C3" => byte_out <= x"2E";
            when x"C4" => byte_out <= x"1C";
            when x"C5" => byte_out <= x"A6";
            when x"C6" => byte_out <= x"B4";
            when x"C7" => byte_out <= x"C6";
            when x"C8" => byte_out <= x"E8";
            when x"C9" => byte_out <= x"DD";
            when x"CA" => byte_out <= x"74";
            when x"CB" => byte_out <= x"1F";
            when x"CC" => byte_out <= x"4B";
            when x"CD" => byte_out <= x"BD";
            when x"CE" => byte_out <= x"8B";
            when x"CF" => byte_out <= x"8A";

            when x"D0" => byte_out <= x"70";
            when x"D1" => byte_out <= x"3E";
            when x"D2" => byte_out <= x"B5";
            when x"D3" => byte_out <= x"66";
            when x"D4" => byte_out <= x"48";
            when x"D5" => byte_out <= x"03";
            when x"D6" => byte_out <= x"F6";
            when x"D7" => byte_out <= x"0E";
            when x"D8" => byte_out <= x"61";
            when x"D9" => byte_out <= x"35";
            when x"DA" => byte_out <= x"57";
            when x"DB" => byte_out <= x"B9";
            when x"DC" => byte_out <= x"86";
            when x"DD" => byte_out <= x"C1";
            when x"DE" => byte_out <= x"1D";
            when x"DF" => byte_out <= x"9E";

            when x"E0" => byte_out <= x"E1";
            when x"E1" => byte_out <= x"F8";
            when x"E2" => byte_out <= x"98";
            when x"E3" => byte_out <= x"11";
            when x"E4" => byte_out <= x"69";
            when x"E5" => byte_out <= x"D9";
            when x"E6" => byte_out <= x"8E";
            when x"E7" => byte_out <= x"94";
            when x"E8" => byte_out <= x"9B";
            when x"E9" => byte_out <= x"1E";
            when x"EA" => byte_out <= x"87";
            when x"EB" => byte_out <= x"E9";
            when x"EC" => byte_out <= x"CE";
            when x"ED" => byte_out <= x"55";
            when x"EE" => byte_out <= x"28";
            when x"EF" => byte_out <= x"DF";

            when x"F0" => byte_out <= x"8C";
            when x"F1" => byte_out <= x"A1";
            when x"F2" => byte_out <= x"89";
            when x"F3" => byte_out <= x"0D";
            when x"F4" => byte_out <= x"BF";
            when x"F5" => byte_out <= x"E6";
            when x"F6" => byte_out <= x"42";
            when x"F7" => byte_out <= x"68";
            when x"F8" => byte_out <= x"41";
            when x"F9" => byte_out <= x"99";
            when x"FA" => byte_out <= x"2D";
            when x"FB" => byte_out <= x"0F";
            when x"FC" => byte_out <= x"B0";
            when x"FD" => byte_out <= x"54";
            when x"FE" => byte_out <= x"BB";
            when x"FF" => byte_out <= x"16";

            when others => byte_out <= (others => 'X'); -- Handle default case
        end case;
    end process;

end s_box_arch;
