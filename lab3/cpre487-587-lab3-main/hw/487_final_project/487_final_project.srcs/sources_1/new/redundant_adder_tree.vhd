library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity redundant_adder_tree is
    generic (
        N : integer := 4  -- Number of stages in the adder tree
    );
    port (
        A_Di : in std_logic_vector(N-1 downto 0);  -- Input A
        A_Si : in std_logic_vector(N-1 downto 0);
        B_Di : in std_logic_vector(N-1 downto 0);  -- Input B
        B_Si : in std_logic_vector(N-1 downto 0);
        C_Di : in std_logic := '0';  -- Input carry
        C_Si : in std_logic := '0';
        Sum : out std_logic_vector(N-1 downto 0);  -- Output sum
        Cout : out std_logic  -- Output carry
    );
end redundant_adder_tree;

architecture Behavioral of redundant_adder_tree is

    signal C1 : std_logic_vector(N downto 1);  -- Internal carry signals
    signal C2 : std_logic_vector(N downto 1);
    signal S1 : std_logic_vector(N-1 downto 0);  -- Internal sum signals
    signal S2 : std_logic_vector(N-1 downto 0);

    begin

    adder_tree_stages : for i in 0 to N-1 generate
        adder_stage : if i < N-1 generate
            adder_cell_inst : entity work.adder_cell
                port map (
                    X_Di => A_Di(i),
                    X_Si => A_Si(i),
                    Y_Di => B_Di(i),
                    Y_Si => B_Si(i),
                    C_Di => C_Di,
                    C_Si => C_Si,
                    i_sig => '0',  -- Input carry is always '0' for the intermediate stages
                    Z_Do => S1(i),
                    Z_So => S2(i),
                    C_Do => C1(i+1),
                    C_So => C2(i+1),
                    o_sig => open  -- Output signal is not used in intermediate stages
                );
        end generate adder_stage;

        last_stage : if i = N-1 generate
            adder_cell_inst : entity work.adder_cell
                port map (
                    X_Di => A_Di(i),
                    X_Si => A_Si(i),
                    Y_Di => B_Di(i),
                    Y_Si => B_Si(i),
                    C_Di => C1(i),
                    C_Si => C2(i),
                    i_sig => C1(i),  -- Input carry for the last stage is the external carry input
                    Z_Do => S1(i),
                    Z_So => S2(i),  -- Output signals are not used in the last stage
                    C_Do => Cout,
                    C_So => open,
                    o_sig => open
                );
        end generate last_stage;
    end generate adder_tree_stages;

    Sum <= S1 + S2;  -- Output sum signals

end Behavioral;