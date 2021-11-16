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
use STD.textio.all;
use ieee.std_logic_textio.all;

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
  
  signal w_out  : std_logic_vector(23 downto 0);

  constant TbPeriod : time := 10 ns;
  signal TbClock : std_logic := '0';

  file file_in   : text;
  file file_out  : text;

begin

  uut: RGB2YUV port map ( clk     => clk,
                            i_data  => i_data,
                            o_data  => o_data,
                            i_valid => i_valid,
                            o_valid => o_valid );

    TbClock <= not TbClock after TbPeriod/2;
    clk <= TbClock;
   
  stimulus: process
  variable v_ILINE     : line;
  variable v_OLINE     : line;
  variable v_rgb_vector : std_logic_vector(23 downto 0);
  begin
	i_data <= (others => '0');
        i_valid <= '0';

        file_open(file_in,  "data_in.txt", read_mode);
        file_open(file_out, "yuv_vhdl.txt", write_mode);
    
        while not endfile(file_in) loop
            readline(file_in, v_ILINE);
            read(v_ILINE, v_rgb_vector);
        
            i_data     <= v_rgb_vector;
            
            i_valid    <= '1';
            wait for TbPeriod;
            i_valid    <= '0';
            
            while o_valid = '0' loop
                i_valid <= '0';
                wait for 10 ns;
                end loop;
                
                w_out <= o_data;
                write(v_OLINE, w_out, right, 24);
                writeline(file_out, v_OLINE);
                
            wait for TbPeriod;
        end loop;
    
        file_close(file_in);
        file_close(file_out);
        
        wait;
    end process;


end;
