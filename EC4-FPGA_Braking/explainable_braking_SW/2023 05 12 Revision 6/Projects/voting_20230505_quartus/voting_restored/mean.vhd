library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity mean is
	generic(
		wordSize  : natural := 24; -- size of probabilities delivered by the input providers
		loss_comm : natural := 30  -- number of clock cycles for a loss of comunication of either 'a' or 'b'.
	);
	port(
		a, b : in std_logic_vector(wordSize-1 downto 0); -- vectors related to the non-braking probabilities delivered by the input providers
		a_vld, b_vld: in std_logic;                      -- flags related to the validity of the non-braking probabilities delivered by the input providers
		clk_mean: in std_logic;                          -- clock input
		c: out std_logic_vector(wordSize-1 downto 0);    -- resulting non-braking probability after combining both input providers and considering loss of sync
		c_vld : out std_logic                            -- resulting validity of the combined non-braking probability from both input providers and considering loss of sync
	);
end mean;

architecture rtl of mean is

signal sum : std_logic_vector(wordSize-1 downto 0);  -- register to sum the non-braking probabilities delivered by the input providers
signal init_flag : std_logic;                        -- flag for the initialization of the module
signal init_flag_a : std_logic := '0';               -- flag for the initialization of the module considering only the 1st 'a' input source. Initialized with '0'.
signal init_flag_b : std_logic := '0';               -- flag for the initialization of the module considering only the 1st 'b' input source. Initialized with '0'.
signal valid_process : std_logic;                    -- flag for indicating a potentially valid output.
signal valid_process_a : std_logic := '0';			 -- flag for indicating a potentially valid input from 'a'. Initialized with '0'.
signal valid_process_b : std_logic := '0';           -- flag for indicating a potentially valid input from 'b'. Initialized with '0'.
signal a_stable_valid : std_logic_vector(wordSize-1 downto 0) := (others => '0');  -- stabilized non-braking probability from the input 'a'. Initialized with '0'.
signal b_stable_valid : std_logic_vector(wordSize-1 downto 0) := (others => '0');  -- stabilized non-braking probability from the input 'b'. Initialized with '0'.
signal loss_comm_count_a: natural := 0;              -- flag for indicating an overly long period without receiving inputs from 'a'. Initialized with '0'.
signal loss_comm_count_b: natural := 0;				 -- flag for indicating an overly long period without receiving inputs from 'b'. Initialized with '0'.

begin
	process(clk_mean)
	begin
		if(clk_mean'event and clk_mean = '1') then
         -- Check if there is loss of sync between 'a' and 'b' and make outputs stuck at restrictive state
			-- in this scenario.
			if((loss_comm_count_a = (loss_comm - 1)) or (loss_comm_count_b = (loss_comm - 1))) then
				a_stable_valid <= (others => '0');
				b_stable_valid <= (others => '0');
				valid_process_a <= '0';
				valid_process_b <= '0';

			-- If there is no loss of sync between 'a' and 'b', resume the regular processing
			else
			   -- 1st Scenario: New input ready to be read from 'a'
				if(a_vld = '1') then
				    
					-- Retain initialized state
					init_flag_a <= '1';

					-- Sets that a stable input 'a' has been read
					valid_process_a <= '1';

					-- Reads the numeric content of 'a' onto a register
					a_stable_valid <= a;  
					
					-- Resets the loss of communication counter for 'a'
					loss_comm_count_a <= 0;

				-- 1st Complementary Scenario: No inputs from 'a' have been read
			   else 
				   
					-- Indicates that no new stable input from 'a' has been read yet   
					valid_process_a <= '0';

					-- Increments the loss of communication counter for 'a' in one unit.
					loss_comm_count_a <= loss_comm_count_a + 1;
			    
				end if; -- ends 'a_vld' if
				
				-- 2nd Scenario: New input ready to be read from 'b'
				if(b_vld = '1') then
				    
					-- Retain initialized state
					init_flag_b <= '1';

					-- Sets that a stable input 'b' has been read
					valid_process_b <= '1';

					-- Reads the numeric content of 'b' onto a register
					b_stable_valid <= b;

					-- Reset the loss of communication counter for 'b'
					loss_comm_count_b <= 0;
			    
				-- 2nd Complementary Scenario: No inputs from 'b' have been read
				else 
				    
					-- Indicates that no new stable input from 'b' has been read yet 
					valid_process_b <= '0';

					-- Increments the loss of communication counter for 'b' in one unit.
					loss_comm_count_b <= loss_comm_count_b + 1;
			   
				end if; -- ends 'b_vld' if
				
		    end if;  -- ends 'loss_sync' if
			 
        end if;  -- ends 'clk_rising_edge' if
		  
	end process;
	
	-- Updates the initialization flag with the 'and' combination of the corresponding 'a' and 'b' flags.
	-- This indicates that the comparator will only produce a potentially permissive output only after one
	-- valid input is read from each input ('a' and 'b').
	init_flag <= init_flag_a and init_flag_b;

	-- Updates the indication of active valid inputs as the 'or' combination of the corresponding 'a' and 'b' flags.
	-- This indicates that the comparator will only change its output while at least one input provider indicates that
	-- its current output is valid.	
	valid_process <= valid_process_a or valid_process_b;
	
	-- Sums the probabilities delivered by 'a' and 'b' in order to decide the actual probability for applying brakes
	sum <= std_logic_vector(unsigned(a_stable_valid) + unsigned(b_stable_valid));

	-- Final probability for applyin brakes: divides 'sum' by two
	c <= '0' & sum(wordSize-1 downto 1) when (sum(wordSize-1) = '0' and init_flag = '1') else 
		  '1' & sum(wordSize-1 downto 1) when (sum(wordSize-1) = '1' and init_flag = '1') else
		  (others => '0');
	
	-- Indicates that the output 'c' is valid if, and only if, one of the outputs remains valid and both have been
	-- received at least once.
	c_vld <= (valid_process) or (not(init_flag));

end rtl;