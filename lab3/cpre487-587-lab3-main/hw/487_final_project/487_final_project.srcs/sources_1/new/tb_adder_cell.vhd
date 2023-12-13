library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity tb_adder_cell is
end tb_adder_cell;

architecture behavior of tb_adder_cell is

    signal X_Di_TB, X_Si_TB, Y_Di_TB, Y_Si_TB, C_Di_TB, C_Si_TB, i_sig_TB : std_logic;
    signal Z_Do_TB, Z_So_TB, C_Do_TB, C_So_TB, o_sig_TB : std_logic;

    component adder_cell
        port    (X_Di   : in std_logic;
                 X_Si   : in std_logic;
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
    end component;

begin

    -- Instantiate the adder_cell module
    UUT: adder_cell
        port map (X_Di_TB, X_Si_TB, Y_Di_TB, Y_Si_TB, C_Di_TB, C_Si_TB, i_sig_TB, Z_Do_TB, Z_So_TB, C_Do_TB, C_So_TB, o_sig_TB);

    -- Stimulus process
    stim_proc: process
    begin
        -- Initialize inputs
        X_Di_TB <= '0';
        X_Si_TB <= '1';
        Y_Di_TB <= '1';
        Y_Si_TB <= '0';
        C_Di_TB <= '0';
        C_Si_TB <= '1';
        i_sig_TB <= '1';

        -- Wait for a few simulation cycles
        wait for 10 ns;

        -- Change inputs
        X_Di_TB <= '1';
        X_Si_TB <= '0';
        Y_Di_TB <= '0';
        Y_Si_TB <= '1';
        C_Di_TB <= '1';
        C_Si_TB <= '0';
        i_sig_TB <= '0';

        -- Wait for a few simulation cycles
        wait for 10 ns;
    
        X_Di_TB <= '0';
        X_Si_TB <= '0';
        Y_Di_TB <= '1';
        Y_Si_TB <= '1';
        C_Di_TB <= '0';
        C_Si_TB <= '1';
        i_sig_TB <= '1';
        wait for 10 ns;

        X_Di_TB <= '1';
        X_Si_TB <= '1';
        Y_Di_TB <= '0';
        Y_Si_TB <= '0';
        C_Di_TB <= '1';
        C_Si_TB <= '0';
        i_sig_TB <= '0';
        wait for 10 ns;
    
        X_Di_TB <= '1';
        X_Si_TB <= '0';
        Y_Di_TB <= '1';
        Y_Si_TB <= '1';
        C_Di_TB <= '1';
        C_Si_TB <= '0';
        i_sig_TB <= '1';
        wait for 10 ns;


    end process stim_proc;

    -- Check results
    check_results: process
    begin
        wait for 20 ns;

        wait;

    end process check_results;

end behavior;