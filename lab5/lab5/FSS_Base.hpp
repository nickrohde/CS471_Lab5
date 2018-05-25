#ifndef __FSS_Base_H
#define __FSS_Base_H

#include "MasterInclude.hpp"
#include "utility.hpp"

struct Job
{
	double d_time;

	std::size_t ui_index;

	Job(void) { d_time = 0; ui_index = 0; }

	Job(double a, std::size_t b) { d_time = a; ui_index = b; }

	bool operator>(const Job& OTHER) const
	{
		return d_time > OTHER.d_time;
	} // end operator <

	
}; // end Struct Job

class cFSS_Base
{
public:
	///<summary>Constructs the FSS_Base class, and assigns the values.</summary>
	///<param name="a">Filename of data.</param>
	cFSS_Base(std::string s_fileName);

	//! A destructor.
	/*!
	Clears the memory.
	*/
	~cFSS_Base(void);

	//! A normal member taking in the schedule and returning the makespan.
	/*!
	\param the schedule
	\return The cost of the tours
	*/
	inline std::size_t GetMachines(void) { return m_Machines; }

	//! Returns the number of jobs.
	/*!
	\param no parameters
	\return The number of jobs
	*/
	inline std::size_t GetJobs(void) { return m_Jobs; }

	//! Returns the number of machines.
	/*!
	\param no parameters
	\return The number of machines
	*/
	void Initialize(void);


	std::vector<Job>* schedule(void);


	///<summary>Calculates the makespan.</summary>
	///<param name="uip_schedule">Schedule to use for calculation.</param>
	///<returns>The makespan of schedule <paramref name"uip_schedule"/>.</returns>
	virtual double Makespan(std::vector<Job>& schedule) = 0;


protected:
	//! The processing time matrix.
	double** m_ProcessTime;
	//! The completion time matrix.
	double** m_CompletionTime;

	//! The number of jobs.
	std::size_t m_Jobs;
	//! The number of machines.
	std::size_t m_Machines;

private:
	void instantiate(void);

	std::vector<Job>* jobs(void);

	std::vector<Job>* NEH(std::vector<Job>* jobs);

	void insertJob(std::vector<Job>& jobs, Job& job);
};


#endif

