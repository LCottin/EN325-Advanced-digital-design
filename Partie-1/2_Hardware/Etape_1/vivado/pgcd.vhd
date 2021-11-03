library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

ENTITY PGCD IS
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
END PGCD;

architecture Behavioral of PGCD is
    TYPE STATE_TYPE IS (init, compute, output);
    SIGNAL current_state, next_state : STATE_TYPE;
    
    --signal A : STD_LOGIC_VECTOR(31 downto 0) : idata_a;
    signal A    : signed(31 downto 0);
    signal B    : signed(31 downto 0);

begin

    --State register
    PROCESS (CLK, RESET)
    BEGIN
        IF RESET = '1' THEN
            current_state  <= init;
        ELSIF (CLK'EVENT AND CLK = '1') THEN
            current_state <= next_state;
        END IF;
    END PROCESS;

    --next state
    PROCESS(current_state, A, B)
    begin
        case current_state is
            when init => 
                if (idata_en = '1') THEN
                    next_state <= compute;
                else 
                    next_state <= current_state;
                end if;

            when compute =>
                if (A = B) then
                    next_state <= output;
                else
                    next_state <= current_state;
                end if;

            when output => 
                    next_state <= init;
        end case;
    end process;

    --output
    process(current_state)
    begin
        case current_state is
            when init | compute =>  odata_en    <= '0';
                                    odata       <= std_logic_vector(A);
                        
            when output =>          odata_en    <= '1';
                                    odata       <= std_logic_vector(A);
        end case;
    end process;

    --compute pgcd
    process(CLK, RESET, current_state)
    begin
        IF (RESET = '1') THEN
            A  <= (others => '0');

        elsif (current_state = init) then
            A  <= signed(idata_a);
            B  <= signed(idata_b);

        ELSIF (CLK'EVENT AND CLK = '1' AND current_state = compute) THEN
            if (A = 0) then
                A <= B;
            elsif (B = 0) then
                B <= A;
            elsif (A > B) then 
                A <= A - B;
            elsif (B > A) then 
                B <= B - A;
            end if;
        end if;
    end process;

end Behavioral;