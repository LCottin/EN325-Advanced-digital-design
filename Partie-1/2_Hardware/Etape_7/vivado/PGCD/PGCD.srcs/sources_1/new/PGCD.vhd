----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 13.10.2021 08:08:56
-- Design Name: 
-- Module Name: PGCD - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity PGCD is
PORT ( 
	CLK      : in  STD_LOGIC;
	RESET    : in  STD_LOGIC;

	idata_a  : in  STD_LOGIC_VECTOR (31 downto 0);
	idata_b  : in  STD_LOGIC_VECTOR (31 downto 0);
	idata_en : in  STD_LOGIC;

	odata    : out STD_LOGIC_VECTOR (31 downto 0);
	odata_en : out STD_LOGIC
);
end PGCD;

architecture Behavioral of PGCD is

type state is (init, calc, end_c);

signal current, nxt : state;

signal A, B, A_init, B_init : signed(31 downto 0);
signal cpt : unsigned(7 downto 0);

begin

reg_current: process(reset, clk)
begin
    if reset = '1' then
        current <= init;
        
    elsif rising_edge(clk) then
        current <= nxt;
            
    end if;
end process;


calcul_nxt: process(current,idata_en, A, B)
begin
    if( current = init)then
        if(idata_en = '1') then
            nxt <= calc;
            assert (signed(idata_a) >= 0) report "Values must be positive." severity error;
            assert (signed(idata_b) >= 0) report "Values must be positive." severity error;
            assert (signed(idata_a) <= 65535) report "Values must be less than 65535." severity error;
            assert (signed(idata_b) <= 65535) report "Values must be less than 65535." severity error;
        else
            nxt <= init;
        end if;
    elsif(current = calc) then
        if(A = B) then
            nxt <= end_c;
        else
            nxt <= calc;
        end if;
    else
        -- pragma translate_off
        REPORT "cpt : " & integer'image(to_integer( cpt ));
        -- pragma translate_on
        assert (idata_en = '0') report "Can't load values while processing. 1" severity error;
        assert (signed(A) <= A_init or A_init = 0) report "Result cannot be greater than inputs." severity failure;
        assert (signed(A) <= B_init or B_init = 0) report "Result cannot be greater than inputs." severity failure;
        assert (signed(A) >= 0) report "Result must be positive." severity failure;
        nxt <= init;
    end if;
end process;    

output: process(current, A)
begin
    if(current = init) then
        odata_en <= '0';
        odata <= (others => '0');
        
    elsif(current = calc) then
        odata_en <= '0';
        odata <= (others => '0');
    
    else
        odata_en <= '1';
        odata <= std_logic_vector(A);
        
    end if;
end process;


calc_pgcd: process(current, clk, reset)
begin
    if reset = '1' then
        A <= (others => '0');
        B <= (others => '0');
        A_init <= (others => '0');
        B_init <= (others => '0');
        
    elsif rising_edge(clk) then
        if(current = init) then
            cpt <= to_unsigned(0, 8);
            A <= signed(idata_a);
            B <= signed(idata_b);
            A_init <= signed(idata_a);
            B_init <= signed(idata_b);
        elsif(current = calc) then
            assert (idata_en = '0') report "Can't load values while processing. 2" severity error;
            cpt <= cpt + 1;
            if (A = 0) then
                A <= B;                
            elsif (B = 0) then
                B <= A;
            elsif(A > (B(27 downto 0) & "0000")) then
                A <= A - (B(27 downto 0) & "0000");
            elsif(B > (A(27 downto 0) & "0000")) then
                B <= B - (A(27 downto 0) & "0000");
            elsif(A > B) then
                A <= A - B;
            elsif(A < B) then
                B <= B - A;
            end if;

        end if;
    end if;
end process;

end Behavioral;
