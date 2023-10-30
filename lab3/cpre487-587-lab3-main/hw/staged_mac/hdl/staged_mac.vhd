-------------------------------------------------------------------------
-- Matthew Dwyer
-- Department of Electrical and Computer Engineering
-- Iowa State University
-------------------------------------------------------------------------


-- staged_mac.vhd
-------------------------------------------------------------------------
-- DESCRIPTION: This file contains a basic staged axi-stream mac unit. It
-- multiplies two integer/Q values togeather and accumulates them.
--
-- NOTES:
-- 10/25/21 by MPD::Inital template creation
-------------------------------------------------------------------------

library work;
library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;
use IEEE.std_logic_signed.all;

entity staged_mac is
  generic(C_DATA_WIDTH : integer := 32);
	port (
        ACLK	: in	std_logic;
		ARESETN	: in	std_logic;       

        -- AXIS slave data interface
		SD_AXIS_TREADY	: out	std_logic;
		SD_AXIS_TDATA	: in	std_logic_vector(C_DATA_WIDTH*2-1 downto 0);  -- Packed data input
		SD_AXIS_TLAST	: in	std_logic;
        SD_AXIS_TUSER   : in    std_logic;
		SD_AXIS_TVALID	: in	std_logic;
        SD_AXIS_TID     : in    std_logic_vector(7 downto 0); -- Ignore for now?

        -- AXIS master accumulate result out interface
		MO_AXIS_TVALID	: out	std_logic;
		MO_AXIS_TDATA	: out	std_logic_vector(C_DATA_WIDTH*2-1 downto 0);
		MO_AXIS_TLAST	: out	std_logic;
		MO_AXIS_TREADY	: in	std_logic;
		MO_AXIS_TID     : out   std_logic_vector(7 downto 0) -- Ignore for now?
    );

attribute SIGIS : string; 
attribute SIGIS of ACLK : signal is "Clk"; 

end staged_mac;


architecture behavioral of staged_mac is
    -- Internal Signals
    signal S_AXIS_TREADY     : std_logic;
    signal S_AXIS_TDATA	     : std_logic_vector(C_DATA_WIDTH*2-1 downto 0);  -- Packed data input, made wider based off of suggestion from TA
	signal S_AXIS_TLAST	     : std_logic;
    signal S_AXIS_TUSER      : std_logic;
    signal S_AXIS_TVALID	 : std_logic;
    signal S_AXIS_TID        : std_logic_vector(7 downto 0);
	
	signal S_D1                 : std_logic_vector(C_DATA_WIDTH-1 downto 0); -- serves as weights
    signal S_D2                 : std_logic_vector(C_DATA_WIDTH-1 downto 0); -- serves as activations
    
    signal S_MULT_OUTPUT        : std_logic_vector(C_DATA_WIDTH*2-1 downto 0);
    signal S_ACCUMULATE_OUTPUT  : std_logic_vector(C_DATA_WIDTH*2-1 downto 0);
	
	
	-- Mac state
    type STATE_TYPE is (WAIT_FOR_VALUES, MULT, ACCUMULATE, OUTPUT);
    signal state : STATE_TYPE;
	
	-- Debug signals, make sure we aren't going crazy
    signal mac_debug : std_logic_vector(31 downto 0);

begin
	   
	-- Debug Signals
    mac_debug <= x"00000000";  -- Double checking sanity
   
   process (ACLK) is
   begin 
    if rising_edge(ACLK) then  -- Rising Edge

      -- Reset values if reset is low
      if ARESETN = '0' then  -- Reset
        state       <= WAIT_FOR_VALUES;
        S_ACCUMULATE_OUTPUT <= x"0000000000000000"; -- Zero the accumulate signal

      else
        case state is  -- State
            -- Wait here until we receive values
            when WAIT_FOR_VALUES =>
                -- Wait here until we recieve valid values
               S_AXIS_TDATA <= SD_AXIS_TDATA;
                
               S_D1 <= S_AXIS_TDATA(C_DATA_WIDTH*2-1 downto C_DATA_WIDTH);
			   S_D2 <= S_AXIS_TDATA(C_DATA_WIDTH-1 downto 0);
			   
			   S_AXIS_TREADY <= MO_AXIS_TREADY;
			   S_AXIS_TVALID <= SD_AXIS_TVALID;
			   S_AXIS_TID <= SD_AXIS_TID;
			   S_AXIS_TUSER <= SD_AXIS_TUSER;
			   S_AXIS_TLAST <= SD_AXIS_TLAST;
			   
			   
			
			   -- Finish state and move on to next stage, MULTIPLY
			   state <= MULT;
			
			   -- Other stages go here	
			   when MULT =>
			   
			   S_MULT_OUTPUT<= S_D1 * S_D2;
			
			   -- Finish state and move on to the next stage, ACCUMULATE
			   state <= ACCUMULATE;
			
			when ACCUMULATE =>
			   if S_AXIS_TUSER = '1' then
			      S_ACCUMULATE_OUTPUT <= S_MULT_OUTPUT + S_AXIS_TDATA;
			   else
			      S_ACCUMULATE_OUTPUT <= S_MULT_OUTPUT;
			   end if;
			      
			
			   -- Now we want to assign all of our output signals
			
			   state <= OUTPUT;
			   
			when OUTPUT =>
			   MO_AXIS_TDATA <= S_ACCUMULATE_OUTPUT; -- Let's just do this for now...
			   MO_AXIS_TVALID <= S_AXIS_TVALID;
			   SD_AXIS_TREADY <= S_AXIS_TREADY;
			   MO_AXIS_TID <= S_AXIS_TID;
			   MO_AXIS_TLAST <= S_AXIS_TLAST;
			   
			   
			   state <= WAIT_FOR_VALUES;		
			
            when others =>
                state <= WAIT_FOR_VALUES;
                -- Not really important, this case should never happen
                -- Needed for proper synthisis         
        end case;  -- State
      end if;  -- Reset

    end if;  -- Rising Edge
   end process;
end architecture behavioral;
