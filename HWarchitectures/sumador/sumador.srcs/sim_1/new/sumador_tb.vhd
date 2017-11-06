----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 21.09.2017 15:10:40
-- Design Name: 
-- Module Name: main_tb - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity sumador_tb is
--  Port ( );
end sumador_tb;

architecture Behavioral of sumador_tb is

component sumador is
    Port(
        a : in STD_LOGIC;
        b : in STD_LOGIC;
        Cin : in STD_LOGIC;
        Cout : out STD_LOGIC;
        Sal : out STD_LOGIC);
end component;

signal a: std_logic:='0';
signal b: std_logic:='0';
signal Cin: std_logic:='0';
signal Cout: std_logic:='0';
signal Sal: std_logic:='0';

begin

sum: sumador port map(
a=>a,
b=>b,
Cin=>Cin,
Cout=>Cout,
Sal=>Sal);

stim_proc: process
begin
a<='0';
b<='0';
Cin<='0';
wait for 10 ns;

a<='0';
b<='0';
Cin<='1';
wait for 10 ns;

a<='0';
b<='1';
Cin<='0';
wait for 10 ns;

a<='0';
b<='1';
Cin<='1';
wait for 10 ns;

a<='1';
b<='0';
Cin<='0';
wait for 10 ns;

a<='1';
b<='0';
Cin<='1';
wait for 10 ns;

a<='1';
b<='1';
Cin<='0';
wait for 10 ns;

a<='1';
b<='1';
Cin<='1';
wait for 10 ns;

wait;

end process;

end Behavioral;
