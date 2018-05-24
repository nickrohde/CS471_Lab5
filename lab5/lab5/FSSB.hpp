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
	cFSSB(std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }

	double Makespan(std::vector<Job>& schedule);

};

#endif
