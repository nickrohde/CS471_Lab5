#ifndef __FSSB_H__
#define __FSSB_H__

#include "FSS_Base.hpp"


class cFSSB : public cFSS_Base
{
	
public:
    //! A constructor.
    /*!
	Pass-along Constructor.
     */
	cFSSB(const std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }

	///<summary>Calculates the makespan of <paramref name="schedule"/> for FSSB.</summary>
	///<param name="schedule">Schedule to use for calculation.</param>
	///<returns>The makespan of schedule <paramref name="schedule"/>.</returns>
	double Makespan(const std::vector<Job>& schedule);

}; // end Class cFSSB

#endif
