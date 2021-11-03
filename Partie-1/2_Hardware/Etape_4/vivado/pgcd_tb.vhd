library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;
use STD.textio.all;
use ieee.std_logic_textio.all;

entity PGCD_tb is
end;

architecture bench of PGCD_tb is

    component PGCD
    PORT 
    ( 
        CLK      : in  STD_LOGIC;
        RESET    : in  STD_LOGIC;
        idata_a  : in  STD_LOGIC_VECTOR (31 downto 0);
        idata_b  : in  STD_LOGIC_VECTOR (31 downto 0);
        idata_en : in  STD_LOGIC;
        odata    : out STD_LOGIC_VECTOR (31 downto 0);
        odata_en : out STD_LOGIC
    );
    end component;

    signal CLK: STD_LOGIC;
    signal RESET: STD_LOGIC;
    signal idata_a: STD_LOGIC_VECTOR (31 downto 0);
    signal idata_b: STD_LOGIC_VECTOR (31 downto 0);
    signal idata_en: STD_LOGIC;
    signal odata: STD_LOGIC_VECTOR (31 downto 0);
    signal odata_en: STD_LOGIC ;

    constant clock_period: time := 10 ns;
    signal stop_the_clock: boolean;

    file file_A : text;
    file file_B : text;
    file file_RESULTS   : text;
 
    constant c_WIDTH : natural := 32;
    
    signal r_ADD_TERM1 : std_logic_vector(c_WIDTH-1 downto 0) := (others => '0');
    signal r_ADD_TERM2 : std_logic_vector(c_WIDTH-1 downto 0) := (others => '0');
    signal w_SUM       : std_logic_vector(c_WIDTH downto 0);

begin

    uut: PGCD port map ( CLK      => CLK,
                        RESET    => RESET,
                        idata_a  => idata_a,
                        idata_b  => idata_b,
                        idata_en => idata_en,
                        odata    => odata,
                        odata_en => odata_en );

    
    clocking: process
    begin
        while not stop_the_clock loop
        CLK <= '0', '1' after clock_period / 2;
        wait for clock_period;
        end loop;
        wait;
    end process;

    process
    variable v_ILINE     : line;
    variable v_OLINE     : line;
    variable v_ADD_TERM_A : std_logic_vector(c_WIDTH-1 downto 0);
    variable v_ADD_TERM_B : std_logic_vector(c_WIDTH-1 downto 0);
     
    begin    
        idata_a <= (others => '0');
        idata_b <= (others => '0');
        idata_en <= '0';

        RESET <= '1';
        wait for 5 ns;
        RESET <= '0';
        wait for 5 ns;

        file_open(file_A,       "../test_generator/data_a.txt", read_mode);
        file_open(file_B,       "../test_generator/data_b.txt", read_mode);
        file_open(file_RESULTS, "data_res.txt"                , write_mode);
    
        while not endfile(file_VECTORS_A) loop
            readline(file_A, v_ILINE); --read file A
            read(v_ILINE, v_ADD_TERM_A);
        
            readline(file_B, v_ILINE); --read file B
            read(v_ILINE, v_ADD_TERM_B);
        
            -- Pass the variable to a signal to allow the pgcd computing
            idata_a     <= v_ADD_TERM_A;
            idata_b     <= v_ADD_TERM_B;
            
            idata_en    <= '1';
            wait for clock_period;
            
            while odata_en = '0' loop
                idata_en <= '0';
                wait for 10 ns;
                end loop;
                
                w_SUM := odata;
                write(v_OLINE, w_SUM, right, c_WIDTH);
                writeline(file_RESULTS, v_OLINE);       --write to file res
                
            wait for clock_period;
        end loop;
    
        file_close(file_A);
        file_close(file_B);
        file_close(file_RESULTS);
        
        wait;
    end process;

end;