library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity RGB2YUV is
    port(
        clk     : in  STD_LOGIC;
        i_data  : in  STD_LOGIC_VECTOR(23 downto 0);
        o_data  : out STD_LOGIC_VECTOR(23 downto 0);
        i_valid : in  STD_LOGIC;
        o_valid : out STD_LOGIC
        );
end RGB2YUV;

architecture Behavioral of RGB2YUV is

signal v_int, valid : std_logic;
signal r, g, b : signed(8 downto 0);
signal y, u, v : unsigned(7 downto 0);
signal y_w_frac, u_w_frac, v_w_frac, y_q, u_q, v_q : signed(16 downto 0);
signal c1, c2, c3, c4, c5, c6, c7, c8 : signed(7 downto 0);

begin

c1 <= to_signed( 38, 8);
c2 <= to_signed( 75, 8);
c3 <= to_signed( 15, 8);
c4 <= to_signed(-22, 8);
c5 <= to_signed(-42, 8);
c6 <= to_signed(-54, 8);
c7 <= to_signed(-10, 8);
c8 <= to_signed( 64, 8);

process(clk)
begin
    if rising_edge(clk) then
        if (i_valid = '1') then
            r <= signed('0' & i_data(23 downto 16));
            g <= signed('0' & i_data(15 downto 8));
            b <= signed('0' & i_data(7 downto 0));
            v_int <= not(i_valid);
        end if;
    end if;
end process;

y_w_frac <= (c1 * r + c2 * g + c3 * b);
u_w_frac <= (c4 * r + c5 * g + c8 * b) + to_signed(16384, 16);
v_w_frac <= (c8 * r + c6 * g + c7 * b) + to_signed(16384, 16);

process(clk)
begin
    if rising_edge(clk) then
        y_q <= y_w_frac;
        u_q <= u_w_frac;
        v_q <= v_w_frac;
        valid <= not(v_int);
    end if;
end process;

process(y_q, u_q, v_q)
begin
    if(y_q(16 downto 7) > to_signed(255,10)) then
        y <= to_unsigned(255, 8);
    elsif(y_q < to_signed(0,10)) then
        y <= to_unsigned(0, 8);
    else
        y <= unsigned(y_q(14 downto 7));
    end if;
            
    if(u_q(16 downto 7) > to_signed(255,10)) then
        u <= to_unsigned(255, 8);
    elsif(y_q < to_signed(0,10)) then
        u <= to_unsigned(0, 8);
    else
        u <= unsigned(u_q(14 downto 7));
    end if;
        
    if(v_q(16 downto 7) > to_signed(255,10)) then
        v <= to_unsigned(255, 8);
    elsif(y_q < to_signed(0,10)) then
        v <= to_unsigned(0, 8);
    else
        v <= unsigned(v_q(14 downto 7));
    end if;
end process;

process(clk)
begin
    if rising_edge(clk) then
        o_data (23 downto 16) <= STD_LOGIC_VECTOR(y);
        o_data (15 downto  8) <= STD_LOGIC_VECTOR(u);
        o_data ( 7 downto  0) <= STD_LOGIC_VECTOR(v);
        o_valid <= valid;
    end if;
end process;

end Behavioral;
