library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_misc.all;
use ieee.numeric_std.all;

use ieee.std_logic_textio.all;
use std.textio.all;
use std.env.finish;

library work;
use work.Constants.all;
use work.Types.all;


entity stimuli_explainable_braking is
    generic(
		FileNameInput : string := "SimulationInputs.txt";   -- file with the simulation inputs
		FilePath : string := "./../";  -- path for the files: at the root of the project directory
		wordSize : natural := 24; -- size of probabilities delivered by the input providers
		decimalSize : natural := 12 -- number of bits for the decimal part of the delivered probabilities
	);
	port(
		--- clocks
		clk_random_forest_1 : out std_logic;  -- clock used in florest 1 
		clk_random_forest_2 : out std_logic;  -- clock used in florest 1 
		clk_voting : out std_logic; -- clock used for averaging and prediction 
		-- features
		distance : out std_logic_vector(wordSize-1 downto 0); 
		speed : out std_logic_vector(wordSize-1 downto 0);
		deceleration : out std_logic_vector(wordSize-1 downto 0);
		-- valid inputs
		input_valid : out std_logic := '0' -- input valid
	);
end stimuli_explainable_braking;

architecture rtl of stimuli_explainable_braking is
    --- This signal is not real, it serves for simulation purposes only
    --- Set the period of inputs updates (period to read a new set of values)
    signal clk_read : std_logic := '0';
    -- read period must be at least 15 times bigger than the random forests clock period
    constant clk_period_read : time := 50 ms;	
    
    --- Clocks generation
    signal clk_random_forest_1_signal : std_logic := '0';
    signal clk_random_forest_2_signal : std_logic := '0';
    signal clk_voting_signal : std_logic := '0';

    -- Clocks periods
    constant clk_period_random_forest_1 : time := 2.5 ms; -- period of clk_random_forest_1
    constant clk_period_random_forest_2 : time := 2.5 ms; -- period of clk_random_forest_2
    constant clk_period_voting : time := 1 ms; -- period of clk_voting

    procedure ValidGenerator(signal clk : in std_logic; 
                            variable delay : in integer; 
                            variable hold : in integer;
                            variable rest : in integer;
                            signal valid : out std_logic;
                            variable invert : in boolean) is 

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
    clk_read <= not(clk_read) after clk_period_read/2;
    -- Generates clock signals
	clk_random_forest_1_signal <= not(clk_random_forest_1_signal) after clk_period_random_forest_1/2;
	clk_random_forest_2_signal <= not(clk_random_forest_2_signal) after clk_period_random_forest_2/2;
    clk_voting_signal <= not(clk_voting_signal) after clk_period_voting/2;

    ReadInputs: process(clk_read)
    -- File
    file f_in : text; 
	variable file_line_in : line;
	variable fstatus_in : file_open_status;
	variable space : character;

    -- Features
	variable distance_read : integer; 
    variable speed_read  : integer; 
    variable deceleration_read  : integer;
	 
	begin
	
		-- Opens simulation input and output files
		file_open(fstatus_in, f_in, FilePath & FileNameInput, read_mode);
      
		-- At each clock rising edge, reads a line of the input file and writes the corresponding outputs
		if (clk_read'event and clk_read = '1') then
			if (not endfile(f_in)) then

				-- Reads the input file until its end
				readline(f_in, file_line_in);
				read(file_line_in, distance_read);

				read(file_line_in, space);
				read(file_line_in, speed_read);

                read(file_line_in, space);
                read(file_line_in, deceleration_read);

				-- Converts the outputs to proper writing of the output simulation file
				distance <= std_logic_vector(to_unsigned(distance_read, distance'length));
				speed <= std_logic_vector(to_unsigned(speed_read, speed'length));
                deceleration <= std_logic_vector(to_unsigned(deceleration_read, deceleration'length));
			
			-- If the input file has ended, closes the files and shuts down the simulation environment
			else
				file_close(f_in);
                std.env.finish;
			end if;
		end if;
	end process;
    
    GenerateValid: process
    variable delay : integer;
    variable hold : integer;
    variable rest : integer;
	variable invert : boolean;         
    begin
        invert := false;
        delay := 2;
        hold := 15;
        rest := 8;

        wait until (clk_read'event and clk_read = '1');
        ValidGenerator(clk_random_forest_1_signal, delay, hold, rest, input_valid, invert);
    end process;

    clk_random_forest_1 <= clk_random_forest_1_signal;
    clk_random_forest_2 <= clk_random_forest_2_signal;
    clk_voting <= clk_voting_signal;
end architecture;