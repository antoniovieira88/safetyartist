library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_textio.all;
use std.textio.all;
use std.env.finish;

entity testbench_voting is
	generic(
		FileNameOutput : string := "SimulationOutputs.txt"; -- file to write the simulation outputs
		FileNameInput : string := "SimulationInputs.txt";   -- file with the simulation inputs
		FilePath : string := "./";                          -- path for the files: same of the testbench
		wordSize : natural := 24;									 -- size of probabilities delivered by the input providers
		decimalSize : natural := 12;								 -- number of bits for the decimal part of the delivered probabilities
		loss_comm : natural := 30									 -- number of clock cycles for a loss of comunication with any input provider.
	);
end testbench_voting;

architecture behav of testbench_voting is
signal prob_1, prob_2, prob_mean  : std_logic_vector(wordSize-1 downto 0); -- probabilities for not braking the vehicle (two inputs and output, respectively)
signal prob_valid_1, prob_valid_2 : std_logic;								-- flags for indicating the validity of the input probabilities
signal prediction : std_logic;												-- 2oo2 decision on applying brakes ('1') or not ('0')

signal clk_read : std_logic := '0';											-- clock signal for simulation files (read and write)
signal clk_voting : std_logic := '0';										-- clock signal for the 2oo2 comparator under test ('voting')

constant clk_period_read : time := 2.5 ms;									-- period of clk_read
constant clk_period_voting : time := 1 ms;									-- period of clk_voting

-- Procedure to generate prob_valid_1 and prob_valid_2 with specific time patterns
-- Parameters:
-- clk: Clock for generating the validity of an output
-- valid: Output with the pattern of the validity signal
-- delay: Number of clock cycles to be waited before leading valid to '1' for the first time
-- hold: Number of clock cycles during which valid remains at '1'
-- rest: Number of clock cycles during which valid remains at '0' after 'hold' cycles are finished
-- invert: Boolean flag which inverts the valid signal profile throughout the delay, hold, and rest intervals
procedure TestValid(signal clk : in std_logic;
					signal valid : out std_logic;
					variable delay : in integer;
					variable hold : in integer;
					variable rest : in integer;
					variable invert : in boolean) is

-- Auxiliary counter to take into account the number of clock cycles up to reaching the limits of delay, hold, and rest.
variable counter : integer := 0; 

begin

	-- Generates valid <= '0' for 'delay' cycles. If 'invert' = true, valid <= '1' during this period.
	while (counter < delay) loop
		if invert = false then
			valid <= '0';
		else
			valid <= '1';
		end if;
		counter := counter + 1;
		wait until (clk'event and clk = '1');
	end loop;
	
	-- Resets counter
	counter := 0;
	
	-- Generates valid <= '1' for 'hold' cycles. If 'invert' = true, valid <= '0' during this period.
	while (counter < hold) loop
		if invert = false then
			valid <= '1';
		else
			valid <= '0';
		end if;
		counter := counter + 1;
		wait until (clk'event and clk = '1');
	end loop;

	-- Resets counter
	counter := 0;

	-- Generates valid <= '0' for 'rest' cycles. If 'invert' = true, valid <= '1' during this period.
	while (counter < rest) loop
		if invert = false then
			valid <= '0';
		else
			valid <= '1';
		end if;
		counter := counter + 1;
		wait until (clk'event and clk = '1');
	end loop;

end procedure;

begin
  
	-- Generates clock signals
	clk_read <= not(clk_read) after clk_period_read/2;
	clk_voting <= not(clk_voting) after clk_period_voting/2;

	-- Instantiates the device under test (voting) and maps its generics, inputs, and outputs to the needed interfaces
	vote: entity work.voting generic map(wordSize => wordSize, decimalSize => decimalSize, loss_comm => loss_comm)
	port map(prob_1 => prob_1,
				prob_2 => prob_2,
				prob_valid_1 => prob_valid_1,
				prob_valid_2 => prob_valid_2,
				clk_voting => clk_voting,
				prob_mean => prob_mean,
				prediction => prediction);  
      
	-- Process to coordinate the reading of simulation inputs and the generation of its outputs
	ReadAndWriteFile: process(clk_read)
    
	file f_in : text; 
	file f_out : text;
	variable file_line_in, file_line_out : line;
	variable fstatus_in, fstatus_out : file_open_status;
	variable space : character;
	variable prob_read_1, prob_read_2 : integer;
	 
	begin
	
		-- Opens simulation input and output files
		file_open(fstatus_in, f_in, FileNameInput, read_mode);
		file_open(fstatus_out, f_out, FileNameOutput, write_mode);
      
		-- At each clock rising edge, reads a line of the input file and writes the corresponding outputs
		if (clk_read'event and clk_read = '1') then
			if (not endfile(f_in)) then

				-- Reads the input file until its end
				readline(f_in, file_line_in);
				read(file_line_in, prob_read_1);
				read(file_line_in, space);
				read(file_line_in, prob_read_2);

				-- Converts the outputs to proper writing of the output simulation file
				prob_1 <= std_logic_vector(to_unsigned(prob_read_1, prob_1'length));
				prob_2 <= std_logic_vector(to_unsigned(prob_read_2, prob_2'length));

				-- Writes the corresponding outputs
				write(file_line_out, to_integer(signed(prob_mean)), left, 0);
				writeline(f_out, file_line_out);	
			
			-- If the input file has ended, closes the files and shuts down the simulation environment
			else
				file_close(f_in);
				file_close(f_out);
				std.env.finish;
			end if;
		end if;
	end process;

	-- Process to generate 'valid_1' signals using the procedure TestValid for all test scenarios
	GenerateValid1: process
	variable delay, hold, rest : integer;
	variable invert : boolean;

	begin
		-- Scenario 0: Initial settings 
		invert := false;
		wait until (clk_read'event and clk_read = '1');
		-- Waits for a clock cycle until starting the next test scenario

		-- Scenario 1: Check outputs when at least one input provider does not have a
		-- valid output, bu without triggering the loss of communication mitigation.
		-- Three subcenarios are needed:
		-- 1.1: Both input providers do not have a valid output
		-- 1.2: Only the input provider '1' / 'a' does not have a valid output
		-- 1.3: Only the input provider '2' / 'b' does not have a valid output
		-- The three subscenarios are reached by the proper choice of 'delay', 'hold', and 'rest'
		-- parameters for both input providers.
		wait until (clk_read'event and clk_read = '1');

		delay := 5;
		hold := 4;
		rest := 11;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 2: Check outputs in regular operation, i.e., 
		-- both random forests generating valid outputs without loss of communication.
		wait until (clk_read'event and clk_read = '1');

		delay := 3;
		hold := 3;
		rest := 4;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenarios 3.1 up to 3.4: Check short activations of at least one 'valid' to assess
		-- whether a valid output is generated.
		-- Scenario 3.1: Input provider '2' generates 'valid' for a single clock cycle.
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 3.2: Input provider '1' generates 'valid' for a single clock cycle.
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 1;
		rest := 5;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 3.3: Input provider '2' generates 'valid' for two clock cycles.
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 3.4: Input provider '1' generates 'valid' for two clock cycles.
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 2;
		rest := 4;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenarios 4.1 up to 4.4: Check short deactivations of at least one 'valid' to assess
		-- whether a valid output stops being generated.
		-- Scenario 4.1: Input provider '2' remains with 'valid' active except for a
		-- single clock cycle (i.e., generates an inverted 'valid' active for a single cycle).
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 4.2: Input provider '1' remains with 'valid' active except for a
		-- single clock cycle (i.e., generates an inverted 'valid' active for a single cycle).
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 1;
		rest := 5;
		invert := true;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);
		invert := false;

		-- Scenario 4.3: Input provider '2' remains with 'valid' active except for
		-- two clock cycles (i.e., generates an inverted 'valid' active for two cycles).
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

		-- Scenario 4.4: Input provider '1' remains with 'valid' active except for
		-- two clock cycles (i.e., generates an inverted 'valid' active for two cycles).
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 2;
		rest := 4;
		invert := true;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);
		invert := false;

		-- Scenario 5: Tests loss of communication due to no inputs from the input provider '1'
		wait until (clk_read'event and clk_read = '1');

		delay := 40;
		hold := 5;
		rest := 5;

		TestValid(clk_voting, prob_valid_1, delay, hold, rest, invert);

	end process;

	GenerateValid2: process
	variable delay, hold, rest : integer;
	variable invert : boolean;

	begin
		-- Scenario 0: Initial settings
		invert := false;
		wait until (clk_read'event and clk_read = '1');
		-- Waits for a clock cycle until starting the next test scenario

		-- Scenario 1: Check outputs when at least one input provider does not have a
		-- valid output, bu without triggering the loss of communication mitigation.
		-- Three subcenarios are needed:
		-- 1.1: Both input providers do not have a valid output
		-- 1.2: Only the input provider '1' / 'a' does not have a valid output
		-- 1.3: Only the input provider '2' / 'b' does not have a valid output
		-- The three subscenarios are reached by the proper choice of 'delay', 'hold', and 'rest'
		-- parameters for both input providers.
		wait until (clk_read'event and clk_read = '1');

		delay := 8;
		hold := 4;
		rest := 8;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 2: Check outputs in regular operation, i.e., 
		-- both random forests generating valid outputs without loss of communication.
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 3;
		rest := 5;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenarios 3.1 up to 3.4: Check short activations of at least one 'valid' to assess
		-- whether a valid output is generated.
		-- Scenario 3.1: Input provider '2' generates 'valid' for a single clock cycle.
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 1;
		rest := 5;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 3.2: Input provider '1' generates 'valid' for a single clock cycle.
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 3.3: Input provider '2' generates 'valid' for two clock cycles.
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 2;
		rest := 4;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 3.4: Input provider '1' generates 'valid' for two clock cycles.
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenarios 4.1 up to 4.4: Check short deactivations of at least one 'valid' to assess
		-- whether a valid output stops being generated.
		-- Scenario 4.1: Input provider '2' remains with 'valid' active except for a
		-- single clock cycle (i.e., generates an inverted 'valid' active for a single cycle).
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 1;
		rest := 5;
		invert := true;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		invert := false;

		-- Scenario 4.2: Input provider '1' remains with 'valid' active except for a
		-- single clock cycle (i.e., generates an inverted 'valid' active for a single cycle).
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 4.3: Input provider '2' remains with 'valid' active except for
		-- two clock cycles (i.e., generates an inverted 'valid' active for two cycles).
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 2;
		rest := 4;
		invert := true;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		invert := false;

		-- Scenario 4.4: Input provider '1' remains with 'valid' active except for
		-- two clock cycles (i.e., generates an inverted 'valid' active for two cycles).
		wait until (clk_read'event and clk_read = '1');

		delay := 2;
		hold := 6;
		rest := 2;

		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

		-- Scenario 5: Tests loss of communication due to no inputs from the input provider '1'
		wait until (clk_read'event and clk_read = '1');

		delay := 4;
		hold := 36;
		rest := 10;
		
		TestValid(clk_voting, prob_valid_2, delay, hold, rest, invert);

	end process;

end behav;