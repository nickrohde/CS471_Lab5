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
	cFSS(std::string s_fileName) : cFSS_Base(s_fileName) { /* Pass-along Constructor. */ }

	double Makespan(std::vector<Job>& schedule);

};

#endif
