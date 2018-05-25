*********************************************************************************************************************************************
*													Programmer:	Nick Rohde																	*
*													Assignment:	CS471 Project 5																*
*													   	 Topic:	FSS, FSSB, FSSNW															*
*													Instructor:	Dr. Donald Davendra															*
*								      					  Date:	1st June 2018																*
*																																			*
*********************************************************************************************************************************************

Compiling the software:

	Compilation: 
					- on Unix-based OS: Please use the included python script for compilation on Unix-based systems.

					- on Windows: Please use Visual Studio 2017 with the following project settings:
						- Mode			 : 64-bit Release
						- Optimization	 : /O2, /Ob2, /Oi, /Ot
						- Code Generation: /Gy, /arch:SSE2 (if available on your machine), /fp:fast
						- Language		 : /std:c++13 OR /std:c++17


*********************************************************************************************************************************************

How to use software:

Run: 	
		- on Unix-based OS: open a terminal, navigate to the src folder, then execute "python run.py". This script will build the program,
							and prompt the user for any additional input that is required to run. 
			- Menu: 
				 1: Run all - run all 120 tests in the data set.
				 2: Run specific - run only a specified test.
					Sub-menu:
						Enter a number in the range [1,120] to specify which test set to run the program on.
				 Q: Quit - quits without cleaning (executable will still be present)
				QQ: Quit and Clean - removes the executable and any build files from the working directory and then exits  

		- on Windows: 	after compiling, execute the .exe file that was generated and provided the test set number as command line parameter
						to the program.

Output: All output will be placed in the data.txt file. This file is formatted as follows:

                        FSS        |       FSSB         |        FSSNW
                Makespan, Time,  # , Makespan, Time,  # , Makespan, Time,  #
                _____________________________________________________________
    data set 1  |  m_1  , t_1 , #_1,   m_1   , t_1 , #_1,   m_1   , t_1 , #_1  
    data set 2  |  m_2  , t_2 , #_2,   m_2   , t_2 , #_2,   m_2   , t_2 , #_2 
        ...     | . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 
    data set n  |  m_n  , t_n , #_n,   m_n   , t_n , #_n,   m_n   , t_n , #_n 


*********************************************************************************************************************************************

Ini parameters:


*********************************************************************************************************************************************

Benchmarking: 	All benchmarking was done on a 3.2 GHz 8C/16T processor with 16GB of memory. 
















