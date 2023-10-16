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

entity staged_mac is
  generic(
      -- Parameters of mac
      C_DATA_WIDTH : integer := 32
    );
	port (
        ACLK	: in	std_logic;
		ARESETN	: in	std_logic;       

        -- AXIS slave data interface
		SD_AXIS_TREADY	: out	std_logic;
		SD_AXIS_TDATA	: in	std_logic_vector(C_DATA_WIDTH*2-1 downto 0);  -- Packed data input
		SD_AXIS_TLAST	: in	std_logic;
        SD_AXIS_TUSER   : in    std_logic_vector(C_DATA_WIDTH-1 downto 0);  -- (NOTE: Changed from 1 bit to 32 bits. Used for accumulation)Should we treat this first value in the stream as an inital accumulate value?
		SD_AXIS_TVALID	: in	std_logic;
        SD_AXIS_TID     : in    std_logic_vector(7 downto 0); -- Ignore for now?

        -- AXIS master accumulate result out interface
		MO_AXIS_TVALID	: out	std_logic;
		MO_AXIS_TDATA	: out	std_logic_vector(C_DATA_WIDTH*2 downto 0);
		MO_AXIS_TLAST	: out	std_logic;
		MO_AXIS_TREADY	: in	std_logic;
		MO_AXIS_TID     : out   std_logic_vector(7 downto 0) -- Ignore for now?
    );

attribute SIGIS : string; 
attribute SIGIS of ACLK : signal is "Clk"; 

end staged_mac;


architecture behavioral of staged_mac is
    -- Internal Signals
    signal S_SD_AXIS_TREADY: std_logic;
	signal S_SD_AXIS_TLAST	: std_logic;
    signal S_SD_AXIS_TUSER   : std_logic_vector(C_DATA_WIDTH-1 downto 0);  -- Should we treat this first value in the stream as an inital accumulate value?
    signal S_SD_AXIS_TVALID	: std_logic;
    signal S_SD_AXIS_TID     : std_logic_vector(7 downto 0); -- Ignore for now?

    -- AXIS master accumulate result out interface
    signal S_MO_AXIS_TVALID	: std_logic;
	signal S_AXIS_TDATA	: std_logic_vector(C_DATA_WIDTH*2 downto 0);
	signal S_MO_AXIS_TLAST	: std_logic;
	signal S_MO_AXIS_TREADY	: std_logic;
	signal S_MO_AXIS_TID    : std_logic_vector(7 downto 0); -- Ignore for now?
    
    signal S_D1 : std_logic_vector(C_DATA_WIDTH-1 downto 0); -- Upper half of the TDATA input
    signal S_D2 : std_logic_vector(C_DATA_WIDTH-1 downto 0); -- Lower half of the TDATA input
    signal S_MULT_RESULT : std_logic_vector(C_DATA_WIDTH*2-1 downto 0); -- Result of D1 * D2 
	
	
	-- Mac state
    type STATE_TYPE is (WAIT_FOR_VALUES);
    signal state : STATE_TYPE;
	
	-- Debug signals, make sure we aren't going crazy
    signal mac_debug : std_logic_vector(31 downto 0);

begin

    -- Interface signals
    S_D1 <= SD_AXIS_TDATA(C_DATA_WIDTH*2-1 downto C_DATA_WIDTH);
	S_D2 <= SD_AXIS_TDATA(C_DATA_WIDTH-1 downto 0);
	S_MULT_RESULT <= std_logic_vector(unsigned(S_D1) * unsigned(S_D2));
	    
	S_SD_AXIS_TLAST <= SD_AXIS_TLAST;
	S_SD_AXIS_TUSER <= SD_AXIS_TUSER;
	S_SD_AXIS_TVALID <= SD_AXIS_TVALID;
	S_MO_AXIS_TREADY <= MO_AXIS_TREADY;
	S_SD_AXIS_TID <= SD_AXIS_TID;
    
    
    

    -- Internal signals
	internal_signals : process is
	   begin
	       
	       if (S_MULT_RESULT /= x"0000000000000000") and (SD_AXIS_TVALID = '1') then
	           S_AXIS_TDATA(C_DATA_WIDTH*2-1 downto 0) <= S_MULT_RESULT;
	           MO_AXIS_TVALID <= '1';
	       end if;
	       
	       if (MO_AXIS_TREADY = '1') then
	           MO_AXIS_TDATA <= S_AXIS_TDATA;
	       end if;
	       
	       MO_AXIS_TID <= S_SD_AXIS_TID;
	       MO_AXIS_TLAST  <= S_SD_AXIS_TLAST;
	       SD_AXIS_TREADY <= MO_AXIS_TREADY;
	       
	       
	   end process internal_signals;
	   
	   
	-- Debug Signals
    mac_debug <= x"00000000";  -- Double checking sanity
   
   process (ACLK) is
   begin 
    if rising_edge(ACLK) then  -- Rising Edge

      -- Reset values if reset is low
      if ARESETN = '0' then  -- Reset
        state       <= WAIT_FOR_VALUES;

      else
        case state is  -- State
            -- Wait here until we receive values
            when WAIT_FOR_VALUES =>
                -- Wait here until we recieve valid values
			
			
			-- Other stages go here	
			
            when others =>
                state <= WAIT_FOR_VALUES;
                -- Not really important, this case should never happen
                -- Needed for proper synthisis         
        end case;  -- State
      end if;  -- Reset

    end if;  -- Rising Edge
   end process;
end architecture behavioral;
