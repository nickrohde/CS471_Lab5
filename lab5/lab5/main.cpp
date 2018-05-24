#include "MasterInclude.hpp"
#include "FSS_Base.hpp"
#include "FSS.h"
#include "FSSB.h"
#include "FSSNW.h"


void JobMakespanFSS(cFSS_Base *FSS, std::string s_jobNum);
void JobMakespanFSSB(cFSS_Base *FSSB, std::string s_jobNum);
void JobMakespanFSSNW(cFSS_Base *FSSNW, std::string s_jobNum);


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
		fileName << "test\\" << std::string(argv[1]) << ".txt";
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

void JobMakespanFSS(cFSS_Base *FSS, std::string s_jobNum)
{
	auto schedule = FSS->schedule();

    //! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << "The makespan for job " << s_jobNum << " in flowshop is: " << FSS->Makespan(*schedule) << std::endl;
    
    //! Delete the schdule.
    delete schedule;
}

void JobMakespanFSSB(cFSS_Base *FSSB, std::string s_jobNum)
{
	auto schedule = FSSB->schedule();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << "The makespan for job " << s_jobNum << " in flowshop with blocking is: " << FSSB->Makespan(*schedule) << std::endl;

	//! Delete the schdule.
	delete schedule;
}

void JobMakespanFSSNW(cFSS_Base *FSSNW, std::string s_jobNum)
{
	auto schedule = FSSNW->schedule();

	//! Calculate the makespan of the simple schedule and display it in standard output
	std::cout << "The makespan for job " << s_jobNum << " in flowshop with no wait is: " << FSSNW->Makespan(*schedule) << std::endl;

	//! Delete the schdule.
	delete schedule;
}

