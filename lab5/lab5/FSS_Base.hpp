#ifndef __FSS_Base_H
#define __FSS_Base_H

#include "MasterInclude.hpp"
#include "utility.hpp"

///<summary>Storage struct for a Job's total time and index in <see cref="cFSS_Base"/>'s data structures.</summary>
struct Job
{
	double d_time;

	std::size_t ui_index;

	Job(void) { d_time = 0; ui_index = 0; }

	Job(double a, std::size_t b) { d_time = a; ui_index = b; }

	bool operator>(const Job& OTHER) const
	{
		return d_time > OTHER.d_time;
	} // end operator >	
}; // end Struct Job


///<summary>Stores the data for <see cref="cFSS"/>, <see cref="cFSSB"/>, and <see cref="cFSSNW"/> classes, and has common methods of all three.</summary>
class cFSS_Base
{
	#pragma region Public:
	public:

		#pragma region Constructor:
			///<summary>Constructs the FSS_Base class, and assigns the values.</summary>
			///<param name="s_fileName">Filename of dataset.</param>
			cFSS_Base(const std::string s_fileName);

		#pragma endregion

		#pragma region Destructor:
			///<summary>Class Destructor.</summary>
			~cFSS_Base(void) { release(); }

		#pragma endregion

		#pragma region Operations:
			///<summary>Finds a schedule for the given data set using <see cref="NEH"/> algorithm.</summary>
			///<remarks>Public wrapper for call to private functions.
			///			The caller of this function takes ownership of the schedule pointer and associated memory.
			///</remarks>
			inline std::vector<Job>* schedule(void) { return NEH(jobs()); }


			///<summary>Calculates the makespan of <paramref name="schedule"/>.</summary>
			///<param name="schedule">Schedule to use for calculation.</param>
			///<returns>The makespan of schedule <paramref name="schedule"/>.</returns>
			///<remarks>Pure virtual function, must be overloaded by child-classes.</remarks>
			virtual double Makespan(const std::vector<Job>& schedule) = 0;

		#pragma endregion

	#pragma endregion

	#pragma region Protected:
	protected:

		#pragma region Data Members:

			//! The processing time matrix.
			double** m_ProcessTime;
			//! The completion time matrix.
			double** m_CompletionTime;

			//! The number of jobs.
			std::size_t m_Jobs;
			//! The number of machines.
			std::size_t m_Machines;
		#pragma endregion

		#pragma region Operations:

			///<summary>Initialiser for <see cref="m_CompletionTime"/> matrix.</summary>
			void initialize(void);
		#pragma endregion

	#pragma endregion

	#pragma region Private:
	private:

		#pragma region Memory Management:
			///<summary>Instantiates dynamic memory of this class.</summary>
			void instantiate(void);


			///<summary>Releases dynamic memory of this class.</summary>
			void release(void) noexcept;
		#pragma endregion

		#pragma region Operations:

			///<summary>Parses <paramref name="file"/> and puts the job info into a the data structures.</summary>
			///<param name="file">File to parse.</param>
			void parse(std::ifstream& file);
		#pragma endregion

		#pragma region NEH Algorithm:
			///<summary>Processes the <see cref="m_ProcessTime"/> matrix into a vector of jobs to be completed.</summary>
			///<returns>A pointer to a vector containing the jobs that must be completed.</returns>
			///<remarks>The caller of this function takes ownership of the jobs pointer and associated memory.</remarks>
			std::vector<Job>* jobs(void) const;


			///<summary>Finds a schedule for <paramref name="jobs"/> using NEH algorithm.</summary>
			///<param name="jobs">Pointer to a vector containing all jobs that must be scheduled.</param>
			///<returns>The schedule for all jobs passed in <paramref name="jobs"/>.</returns>
			///<remarks>The caller of this function takes ownership of the schedule pointer and associated memory.</remarks>
			std::vector<Job>* NEH(std::vector<Job>* jobs);


			///<summary>Finds the best location to insert <paramref name="job"/> into <paramref name="schedule"/>.</summary>
			///<param name="schedule">Schedule to insert <paramref name="job"/> into.</param>
			///<param name="job">Job to insert.</param>
			///<remarks>The parameter <paramref name="schedule"/> will be altered by this function.</remarks>
			void insertJob(std::vector<Job>& schedule, Job& job);
		#pragma endregion

	#pragma endregion

}; // end Class cFSS_Base


#endif

