#ifndef __FSSNW_H__
#define __FSSNW_H__

#include "FSS_Base.hpp"

class cFSSNW : public cFSS_Base
{
	
public:
    //! A constructor.
    /*!
     Pass-along Constructor.
     */
	cFSSNW(const std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }
    
	///<summary>Calculates the makespan of <paramref name="schedule"/> for FSSNW.</summary>
	///<param name="schedule">Schedule to use for calculation.</param>
	///<returns>The makespan of schedule <paramref name="schedule"/>.</returns>
	double Makespan(const std::vector<Job>& schedule);

}; // end Class cFSSNW

#endif
