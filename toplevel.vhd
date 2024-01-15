library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity toplevel is
	port (
		BP_SW  : in  std_logic_vector(7 downto 0) := (others => '0'); -- bp_sw.export
		CLK       : in  std_logic                    := '0';             --   clk.clk
		LEDS    : out std_logic_vector(7 downto 0);                    --   led.export
		RESET : in  std_logic                    := '0'              -- reset.reset_n
	);
end entity toplevel;

architecture rtl of toplevel is

	component lab1 is
		port ( 
			clk_clk       : in  std_logic                    := 'X';             -- clk
			reset_reset_n : in  std_logic                    := 'X';             -- reset_n
			led_export    : out std_logic_vector(7 downto 0);                    -- export
			bp_sw_export  : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component lab1;

begin
	u0 : component lab1
		port map (
			clk_clk       => CLK,       --   clk.clk
			reset_reset_n => RESET, -- reset.reset_n
			led_export    => LEDS,    --   led.export
			bp_sw_export  => BP_SW   -- bp_sw.export
		);


end architecture;