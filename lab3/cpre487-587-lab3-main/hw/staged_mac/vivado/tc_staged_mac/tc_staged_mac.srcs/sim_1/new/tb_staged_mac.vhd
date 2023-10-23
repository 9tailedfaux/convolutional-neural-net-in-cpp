----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Trevor Friedl
-- 
-- Create Date: 10/16/2023 12:25:10 PM
-- Design Name: 
-- Module Name: tb_staged_mac - Behavioral
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

library work;
library IEEE;
library std;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity tb is
    generic(gCLK_HPER   : time := 10ns;
            N           : integer := 32);
end tb;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity tb_staged_mac is
--  Port ( );
        
end tb_staged_mac;

architecture Behavioral of tb_staged_mac is
    
    component staged_mac is
        generic(C_DATA_WIDTH : integer);
        port(ACLK            : in std_logic;
             ARESETN         : in std_logic;
        
             -- Slave data
             SD_AXIS_TREADY  : out std_logic;
             SD_AXIS_TDATA   : in  std_logic_vector(C_DATA_WIDTH*2-1 downto 0)
        );
    
    end component;
    
begin


end Behavioral;
