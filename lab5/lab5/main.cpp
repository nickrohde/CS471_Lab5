#include "MasterInclude.hpp"
#include "utility.hpp"
#include "FSS_Base.hpp"
#include "FSS.hpp"
#include "FSSB.hpp"
#include "FSSNW.hpp"

//! dedfault file name for output
std::string FILE_NAME = "results.csv";

//! thread synchronization for writing results to file
std::mutex threadLock;

//! thread synchronization for writing results to file in order
int turn = 0;

///<summary>Prints out the job schedule to std::out.</summary>
///<param name="schedule">Schedule to print.</param>
void printSchedule(std::vector<Job>* schedule)
{
	std::cout << "Schedule: " << (*schedule)[0].ui_index;
	for (auto i = 1; i < schedule->size(); i++)
	{
		std::cout << ", " << ((*schedule)[i].ui_index + 1); // convert base0 -> base1
	} // end for
	std::cout << "\n";
} // end method printSchedule


///<summary>Solves the FSS on the given data set.</summary>
///<param name="FSS">FSS object with data set initialised.</param>
///<param name="s_jobNum">Number of the data set for output.</param>
void JobMakespanFSS(cFSS_Base* FSS, const std::string& s_jobNum, const std::string& s_print, const std::string& s_store)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	//! Find schedule
	auto schedule = FSS->schedule();

	compute_end = highRes_Clock::now();

	//! Find makespan of schedule
	auto result = FSS->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	//! Store results 
	if(s_store == "1")
	{
		std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);
		
		if(file.is_open() && !file.bad())
		{
			file << result << ", " << time_to_compute.count() << ", " << FSS->callsMade();
		} // end if

		file.close();

		threadLock.lock();
		turn = 1;
		threadLock.unlock();
	} // end if

    //! Display result in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;

	//! Print schedule if user requested it
	if(s_print == "1")
		printSchedule(schedule);    

    //! Delete the schdule.
    delete schedule;
} // end method JobMakespanFSS


///<summary>Solves the FSSB on the given data set.</summary>
///<param name="FSSB">FSSB object with data set initialised.</param>
///<param name="s_jobNum">Number of the data set for output.</param>
void JobMakespanFSSB(cFSS_Base* FSSB, const std::string& s_jobNum, const std::string& s_print, const std::string& s_store)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	auto schedule = FSSB->schedule();

	compute_end = highRes_Clock::now();

	auto result = FSSB->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	if(s_store == "1")
	{
		//! wait for previous thread to finish writing results
		while(true)
		{
			threadLock.lock();
			if(turn == 1)
			{
				threadLock.unlock();
				break;
			} // end if
			else
				threadLock.unlock();
		} // end while

		std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);
		
		if(file.is_open() && !file.bad())
		{
			file << ", " << result << ", " << time_to_compute.count() << ", " << FSSB->callsMade();
		} // end if

		file.close();

		threadLock.lock();
		turn = 2;
		threadLock.unlock();
	} // end if

    //! Display result in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop with blocking is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;

	//! Print schedule if user requested it
	if(s_print == "1")
		printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
} // end method JobMakespanFSSB


///<summary>Solves the FSSNW on the given data set.</summary>
///<param name="FSSNW">FSSNW object with data set initialised.</param>
///<param name="s_jobNum">Number of the data set for output.</param>
void JobMakespanFSSNW(cFSS_Base* FSSNW, const std::string& s_jobNum, const std::string& s_print, const std::string& s_store)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	auto schedule = FSSNW->schedule();

	compute_end = highRes_Clock::now();

	auto result = FSSNW->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	if(s_store == "1")
	{
		//! wait for previous thread to finish writing results
		while(true)
		{
			threadLock.lock();
			if(turn == 2)
			{
				threadLock.unlock();
				break;
			} // end if
			else
				threadLock.unlock();
		} // end while

		std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);

		if(file.is_open() && !file.bad())
		{
			file << ", " << result << ", " << time_to_compute.count() << ", " << FSSNW->callsMade() << std::endl;
		} // end if

		file.close();
	} // end if

    //! Display result in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop with no wait is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;

	//! Print schedule if user requested it
	if(s_print == "1")
		printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
} // end method JobMakespanFSSNW


///<summary>Program entry point.</summary>
///<param name="argc">Number of command line arguments.</param>
///<param name="argv">Command line arguments. [0]: executable; [1]: test-set #; [2]: Use Threads (1/0); [3]: Print Schedule (1/0); [4]: Store Results; [5] Filename iff [4] == 1.</param>
///<returns>0 on successful execution, 1 otherwise.</returns>
int main(int argc, char** argv)
{
	std::stringstream fileName;
	std::string s_threads = "0";

	if (argc < 5 || (argc < 6 && argv[4] == "1"))
	{
		std::cout << "Too few parameters received!" << std::endl;
		std::cout << "Usage: " << argv[0] << "[Problem set # (1-120)] [Use Threads (0 | 1)] [Print Schedule (0 | 1)] [Store Results (0 | 1)] [Output File Name]" << std::endl;
		exit(EXIT_FAILURE);
	} // end if
	else
	{
		// determine file system structure
		#if defined(_WIN64) || defined(_WIN32) // windows filesystem
			fileName << "test\\" << std::string(argv[1]) << ".txt";
		#elif defined(__APPLE__) || defined(__linux) || defined(__unix) || defined(__posix) // unix-like filesystem
			fileName << "test/" << std::string(argv[1]) << ".txt";
		#else // something else 
			#error Unsupported filesystem!
		#endif

		std::string tempStore = argv[4];
		s_threads = argv[2];

		if(tempStore == "1")
		{
			FILE_NAME = std::string(argv[5]);
		} // end if
	} // end else

	//! create filename
	std::string s_file = fileName.str();

	//! Initialization of the FSS
	cFSS_Base* FSS = new cFSS(s_file);

	//! Initialization of the FSS with blocking
	cFSS_Base* FSSB = new cFSSB(s_file);

	//! Initialization of the FSS with no wait
	cFSS_Base* FSSNW = new cFSSNW(s_file);

	//! check if multiple threads should be used
	if(s_threads == "1")
	{
		//! initialize threads
		auto threads = std::vector<std::thread>(3);

		//! Calculate a schedule for flowshop
		threads[0] = std::thread(JobMakespanFSS, FSS, argv[1], argv[3], argv[4]);

		//! Calculate a schedule for flowshop with blocking
		threads[1] = std::thread(JobMakespanFSSB, FSSB, argv[1], argv[3], argv[4]);

		//! Calculate a schedule for flowshop with no wait
		threads[2] = std::thread(JobMakespanFSSNW, FSSNW, argv[1], argv[3], argv[4]);

		//! wait for all threads to finish
		for(auto i = 0; i < threads.size(); i++)
		{
			threads[i].join();
		} // end for
	} // end if
	else
	{
		//! do scheduling sequentially
		JobMakespanFSS(FSS, argv[1], argv[3], argv[4]);
		JobMakespanFSSB(FSSB, argv[1], argv[3], argv[4]);
		JobMakespanFSSNW(FSSNW, argv[1], argv[3], argv[4]);
	} // end else

	//! free memory
	delete FSS;
	delete FSSB;
	delete FSSNW;

	exit(EXIT_SUCCESS);
} // end Main
