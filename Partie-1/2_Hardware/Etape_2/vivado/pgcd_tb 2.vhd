library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

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

begin

    uut: PGCD port map ( CLK      => CLK,
                        RESET    => RESET,
                        idata_a  => idata_a,
                        idata_b  => idata_b,
                        idata_en => idata_en,
                        odata    => odata,
                        odata_en => odata_en );

    stimulus: process
    begin
    
        -- Put initialisation code here
        idata_a <= (others => '0');
        idata_b <= (others => '0');
        idata_en <= '0';

        RESET <= '1';
        wait for 5 ns;
        RESET <= '0';
        wait for 5 ns;

        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(0, idata_a'length));
        idata_b <= std_logic_vector(to_signed(10, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata )= TO_SIGNED(10, 32) SEVERITY ERROR;

        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(10, idata_a'length));
        idata_b <= std_logic_vector(to_signed(0, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata ) = TO_SIGNED(10, 32)  SEVERITY ERROR;

        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(40, idata_a'length));
        idata_b <= std_logic_vector(to_signed(24, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata ) = TO_SIGNED(8, 32) SEVERITY ERROR;

        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(24, idata_a'length));
        idata_b <= std_logic_vector(to_signed(40, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata ) = TO_SIGNED(8, 32) SEVERITY ERROR;

        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(7, idata_a'length));
        idata_b <= std_logic_vector(to_signed(13, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata ) = TO_SIGNED(1, 32) SEVERITY ERROR;
        
        idata_en <= '1';
        idata_a <= std_logic_vector(to_signed(0, idata_a'length));
        idata_b <= std_logic_vector(to_signed(0, idata_b'length));
        wait for clock_period;
        while odata_en = '0' loop
            idata_en <= '0';
            wait for 10 ns;
        end loop;
        ASSERT SIGNED( odata ) = TO_SIGNED(0, 32) SEVERITY ERROR;

        wait for 200 ns;
        stop_the_clock <= true;
        wait;
    end process;

    clocking: process
    begin
        while not stop_the_clock loop
        CLK <= '0', '1' after clock_period / 2;
        wait for clock_period;
        end loop;
        wait;
    end process;

end;