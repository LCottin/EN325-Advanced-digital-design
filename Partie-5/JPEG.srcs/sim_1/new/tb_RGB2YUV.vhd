----------------------------------------------------------------------------------
-- Company:
-- Engineer:
--
-- Create Date:
-- Design Name:
-- Module Name:
-- Project Name:
-- Target Devices:
-- Tool versions:
-- Description:
--
-- Dependencies:
--
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
----------------------------------------------------------------------------------
-- Testbench created online at:
--   www.doulos.com/knowhow/perl/testbench_creation/
-- Copyright Doulos Ltd
-- SD, 03 November 2002

library IEEE;
use IEEE.Std_logic_1164.all;
use IEEE.Numeric_Std.all;

entity tb_RGB2YUV is
end;

architecture bench of tb_RGB2YUV is

  component RGB2YUV
    PORT (
      clk     : in  STD_LOGIC;
      i_data  : in  STD_LOGIC_VECTOR (23 downto 0);
      o_data  : out STD_LOGIC_VECTOR (23 downto 0);
      i_valid : in  STD_LOGIC;
      o_valid : out STD_LOGIC
    );
  end component;

  signal clk    : STD_LOGIC;
  signal i_data : STD_LOGIC_VECTOR (23 downto 0);
  signal o_data : STD_LOGIC_VECTOR (23 downto 0);
  signal i_valid: STD_LOGIC;
  signal o_valid: STD_LOGIC ;

  constant TbPeriod : time := 10 ns;
  signal TbClock : std_logic := '0';

begin

  uut: RGB2YUV port map ( clk     => clk,
                            i_data  => i_data,
                            o_data  => o_data,
                            i_valid => i_valid,
                            o_valid => o_valid );

    TbClock <= not TbClock after TbPeriod/2;
    clk <= TbClock;
   
  stimulus: process
  begin
        i_data <= (others => '0');
        i_valid <= '0';
        wait for 5 * TbPeriod;
        
        i_data <= (others => '1');
        i_valid <= '1';
        wait for 1 * TbPeriod;
        i_valid <= '0';
        
        wait for 5 * TbPeriod;
  
        i_data <= x"FF0000";
        i_valid <= '1';
        wait for 1 * TbPeriod;
        i_valid <= '0';
        
        wait for 5 * TbPeriod;
          
        i_data <= x"00FF00";
        i_valid <= '1';
        wait for 1 * TbPeriod;
        i_valid <= '0';
        
        wait for 5 * TbPeriod;
          
        i_data <= x"0000FF";
        i_valid <= '1';
        wait for 1 * TbPeriod;
        i_valid <= '0';
                         
        wait;
  end process;


end;
