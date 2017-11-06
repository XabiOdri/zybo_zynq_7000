----------------------------------------------------------------------------------
-- Company: 
-- Engineer: Xabier Odriozola
-- 
-- Create Date: 21.09.2017 23:15:53
-- Design Name: 
-- Module Name: sumador - Behavioral
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

entity sumador is
    Port ( 
            a : in STD_LOGIC;
            b : in STD_LOGIC;
            Cin : in STD_LOGIC;
            Cout : out STD_LOGIC;
            Sal : out STD_LOGIC);
end sumador;

architecture Behavioral of sumador is

begin

Sal <=  ( (not a) and (not b) and Cin ) 
        or ( (not a) and b and (not Cin) ) 
        or ( a and (not b) and (not Cin) ) 
        or ( a and b and Cin );
        
Cout <= ( (not a) and b and Cin ) 
        or ( a and (not b) and Cin ) 
        or ( a and b and (not Cin)) 
        or (a and b and Cin);

end Behavioral;
