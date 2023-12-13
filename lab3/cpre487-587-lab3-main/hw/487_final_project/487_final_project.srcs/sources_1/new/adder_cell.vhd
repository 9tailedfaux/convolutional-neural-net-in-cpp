----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Trevor Friedl
-- 
-- Create Date: 12/11/2023 09:50:05 PM
-- Design Name: 
-- Module Name: adder_cell - Behavioral
-- Project Name: 487 Final Project
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity adder_cell is
    
    port    (X_Di   : in std_logic; -- First pair, first bit
             X_Si   : in std_logic; -- First pair, second bit
             Y_Di   : in std_logic;
             Y_Si   : in std_logic;
             C_Di   : in std_logic;
             C_Si   : in std_logic;
             i_sig  : in std_logic;
             
             Z_Do   : out std_logic;
             Z_So   : out std_logic;
             C_Do   : out std_logic;
             C_So   : out std_logic;
             o_sig  : out std_logic);
             
    
end adder_cell;

architecture Behavioral of adder_cell is
    
    signal S_ZD     : std_logic;
    signal S_ZS     : std_logic;
    signal S_CD     : std_logic;
    signal S_CS     : std_logic;
    
begin

    process(X_Di, X_Si, Y_Di, Y_Si, C_Di, C_Si)
    
        variable a1, a2, a3, a4, a5, a6, a7, a8 : std_logic; -- And gates
        variable x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11 : std_logic; -- Xnor gates
        variable na1, na2, na3, na4, na5 : std_logic; -- Nand gates
        variable n1 : std_logic; -- Not gate 
    
    begin
        -- Compute first layer
        x1 := X_Si xnor Y_Si; -- 0
        x2 := Y_Di xnor Y_Si; -- 0
        x3 := X_Di xnor X_Si; -- 0
        
        o_sig <= x1; -- 0
        
        a1 := X_Di and Y_Di; -- 0
        a2 := X_Si and Y_Si; -- 0
        a3 := X_Si and x2; -- 0
        a4 := Y_Di and x2;
        a5 := Y_Di and x3;
        a6 := Y_Si and x3;
        
        -- Not gate layer
        n1 := i_sig;
        
        x4 := a4 xnor a5;
        x5 := a3 xnor a6;
        
        x6  := n1 xnor x4;
        x7  := i_sig xnor x5;
        na1 := x4 nand x5;
        
        -- End of immediate carry step
        x8  := x6 xnor a1;
        x9  := x7 xnor a2;
        na2 := i_sig nand na1;
        na3 := n1 nand na1;
        
        -- Second step of the adder
        C_Do <= x8;
        C_So <= x9;
        
        a7  := x8 and C_Si;
        na4 := C_Di nand x9;
        na5 := x8 and C_Si;
        a8  := x9 and C_Di;
        
        x10 := a7 xnor na4;
        x11 := na5 xnor a8;
        
        -- Output the final signals from the cell
        Z_Do <= x11;
        Z_So <= x10;
        
       
            
    
    end process;

end Behavioral;
