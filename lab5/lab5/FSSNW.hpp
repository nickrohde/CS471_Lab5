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
	cFSSNW(std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }
    
	double Makespan(std::vector<Job>& schedule);

};

#endif
