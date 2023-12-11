----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 12/11/2023 01:38:12 PM
-- Design Name: 
-- Module Name: booth_multiplier - Behavioral
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
use IEEE.STD_LOGIC_SIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity booth_multiplier is
    
    generic (b0 : INTEGER := 8;
             b1 : INTEGER := 8);
             
    port    (clk: in std_logic;
             p : in std_logic_vector(b0 - 1 downto 0);
             r : in std_logic_vector(b1 - 1 downto 0);
             m : out std_logic_vector(b0 + b1 - 1 downto 0));
    
end booth_multiplier;

architecture Behavioral of booth_multiplier is

   signal S_P          : std_logic_vector(b0 - 1 downto 0);
   signal S_R          : std_logic_vector(b1 - 1 downto 0);
   signal S_M          : std_logic_vector(b0 + b1 - 1 downto 0);

begin

    process(p, r, clk)
        
        constant B0_ZERO : std_logic_vector(b0 - 1 downto 0) := (others => '0');
        constant B1_ZERO : std_logic_vector(b1 - 1 downto 0) := (others => '0');
        
        variable r1, r2, r3 : std_logic_vector(b0 + b1 + 1 downto 0) := (others => '0');
        variable mn :         std_logic_vector(b0 - 1 downto 0);
    
    begin
    
        if rising_edge(clk) then
            
            if (p /= B0_ZERO and r /= B1_ZERO) then
        
                r1(b0 + b1 downto b1 + 1) := p;
                r1(b0 + b1 + 1) := p(b0 - 1);
            
                mn := (not p) + 1;
            
                r2(b0 + b1 downto b1 + 1) := mn;
                r2(b0 + b1 + 1) := not(p(b0 - 1));
            
                r3(b1 downto 1) := r;
            
                for i in 1 to b1 loop
            
                    if    (r3(1 downto 0) = "01") then
                        r3 := r3 + r1;
                    elsif (r3(1 downto 0) = "10") then
                        r3 := r3 + r2;
                    end if;
                
                
                    r3(b0 + b1 downto 0) := r3(b0 + b1 + 1 downto 1);
                
                end loop;
            
            end if;
            S_M <= r3(b0 + b1 downto 1);
            m <= S_M;
            S_P <= p;
            S_R <= r;
                
        end if;
    
        
    end process;
            
        

end Behavioral;
