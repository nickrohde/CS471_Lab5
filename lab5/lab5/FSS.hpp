#ifndef __FSS_H__
#define __FSS_H__

#include "FSS_Base.hpp"

class cFSS : public cFSS_Base
{	
public:
    //! A constructor.
    /*!
     Pass-along Constructor.
     */
	cFSS(const std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }


	///<summary>Calculates the makespan of <paramref name="schedule"/> for FSS.</summary>
	///<param name="schedule">Schedule to use for calculation.</param>
	///<returns>The makespan of schedule <paramref name="schedule"/>.</returns>
	double Makespan(const std::vector<Job>& schedule);

}; // end Class cFSS

#endif
