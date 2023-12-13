library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity tb_redundant_adder_tree is
end tb_redundant_adder_tree;

architecture behavior of tb_redundant_adder_tree is

    signal A_Di_TB, A_Si_TB, B_Di_TB, B_Si_TB : std_logic_vector(3 downto 0);
    signal C_Di_TB, C_Si_TB : std_logic := '0';
    signal Sum_TB : std_logic_vector(3 downto 0);
    signal Cout_TB : std_logic;

    component redundant_adder_tree
        generic (
            N : integer := 4
        );
        port (
            A_Di : in std_logic_vector(N-1 downto 0);
            A_Si : in std_logic_vector(N-1 downto 0);
            B_Di : in std_logic_vector(N-1 downto 0);
            B_Si : in std_logic_vector(N-1 downto 0);
            C_Di : in std_logic := '0';
            C_Si : in std_logic := '0';
            Sum : out std_logic_vector(N-1 downto 0);
            Cout : out std_logic
        );
    end component;

begin

    UUT: redundant_adder_tree
        generic map (N => 4)
        port map (
            A_Di => A_Di_TB,
            A_Si => A_Si_TB,
            B_Di => B_Di_TB,
            B_Si => B_Si_TB,
            C_Di => C_Di_TB,
            C_Si => C_Si_TB,
            Sum => Sum_TB,
            Cout => Cout_TB
        );

    -- Stimulus process
    stim_proc: process
    begin
        -- Initialize inputs
        A_Di_TB <= "0101";
        A_Si_TB <= "0000";
        B_Di_TB <= "1010";
        B_Si_TB <= "0000";
        C_Di_TB <= '0';
        C_Si_TB <= '0';

        wait for 20 ns;

        -- Add more test cases if needed
        
        A_Di_TB <= "1001";
        A_Si_TB <= "0000";
        B_Di_TB <= "1011";
        B_Si_TB <= "0011";
        C_Di_TB <= '1';
        C_Si_TB <= '0';
        
        wait for 20 ns;
        
        A_Di_TB <= "1111";
        A_Si_TB <= "1010";
        B_Di_TB <= "1111";
        B_Si_TB <= "1101";
        C_Di_TB <= '0';
        C_Si_TB <= '1';
        
        wait for 20 ns;
        
        A_Di_TB <= "0000";
        A_Si_TB <= "0000";
        B_Di_TB <= "0000";
        B_Si_TB <= "0001";
        C_Di_TB <= '0';
        C_Si_TB <= '1';
        
        wait for 20 ns;

        wait;

    end process stim_proc;

    -- Check results
    check_results: process
    begin
        wait for 20 ns;  -- Wait for simulation to stabilize;

        wait;

    end process check_results;

end behavior;