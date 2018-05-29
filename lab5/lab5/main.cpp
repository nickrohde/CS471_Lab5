#include "MasterInclude.hpp"
#include "utility.hpp"
#include "FSS_Base.hpp"
#include "FSS.hpp"
#include "FSSB.hpp"
#include "FSSNW.hpp"

const std::string FILE_NAME = "results.csv";

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
void JobMakespanFSS(cFSS_Base* FSS, const std::string& s_jobNum)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	auto schedule = FSS->schedule();

	compute_end = highRes_Clock::now();

	auto result = FSS->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);
	
	if(file.is_open() && !file.bad())
	{
		file << time_to_compute.count();
	} // end if

	file.close();

    //! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;
	printSchedule(schedule);    

    //! Delete the schdule.
    delete schedule;
} // end method JobMakespanFSS


///<summary>Solves the FSSB on the given data set.</summary>
///<param name="FSSB">FSSB object with data set initialised.</param>
///<param name="s_jobNum">Number of the data set for output.</param>
void JobMakespanFSSB(cFSS_Base* FSSB, const std::string& s_jobNum)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	auto schedule = FSSB->schedule();

	compute_end = highRes_Clock::now();

	auto result = FSSB->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);
	
	if(file.is_open() && !file.bad())
	{
		file << ", " << time_to_compute.count();
	} // end if

	file.close();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop with blocking is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;
	printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
} // end method JobMakespanFSSB


///<summary>Solves the FSSNW on the given data set.</summary>
///<param name="FSSNW">FSSNW object with data set initialised.</param>
///<param name="s_jobNum">Number of the data set for output.</param>
void JobMakespanFSSNW(cFSS_Base* FSSNW, const std::string& s_jobNum)
{
	timePoint compute_end = highRes_Clock::now(),
			  compute_start = highRes_Clock::now();

	auto schedule = FSSNW->schedule();

	compute_end = highRes_Clock::now();

	auto result = FSSNW->Makespan(*schedule);
	duration time_to_compute = std::chrono::duration_cast<duration>(compute_end - compute_start);

	std::ofstream file(FILE_NAME, std::ios::out | std::ios::app);

	if(file.is_open() && !file.bad())
	{
		file << ", " << time_to_compute.count() << std::endl;
	} // end if

	file.close();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << std::endl << "The makespan for test-set " << s_jobNum << " in flowshop with no wait is: " << result << ". Time: " << time_to_compute.count() << " (s)" << std::endl;
	printSchedule(schedule);

	//! Delete the schdule.
	delete schedule;
} // end method JobMakespanFSSNW


///<summary>Program entry point.</summary>
///<param name="argc">Number of command line arguments.</param>
///<param name="argv">Command line arguments.</param>
///<returns>0 on successful execution, 1 otherwise.</returns>
int main(int argc, char** argv)
{
	std::stringstream fileName;

	if (argc < 2)
	{
		std::cout << "No parameters received" << std::endl;
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
	} // end else

	std::string s_file = fileName.str();

	//! Initialization of the FSS
	cFSS_Base* FSS = new cFSS(s_file);

	//! Initialization of the FSS with blocking
	cFSS_Base* FSSB = new cFSSB(s_file);

	//! Initialization of the FSS with no wait
	cFSS_Base* FSSNW = new cFSSNW(s_file);

	//! Calculate a schedule for flowshop
	JobMakespanFSS(FSS, argv[1]);

	//! Calculate a schedule for flowshop with blocking
	JobMakespanFSSB(FSSB, argv[1]);

	//! Calculate a schedule for flowshop with no wait
	JobMakespanFSSNW(FSSNW, argv[1]);

	delete FSS;
	delete FSSB;
	delete FSSNW;

	exit(EXIT_SUCCESS);
} // end Main
