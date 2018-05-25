#include "FSS.hpp"
#include "utility.hpp"

using namespace std;


double cFSS::Makespan(const std::vector<Job>& schedule)
{
	double max = 0.0;

	initialize();

	// Calculate processing time for all jobs on first machine
	m_CompletionTime[0][0] = m_ProcessTime[0][schedule[0].ui_index];

	for (std::size_t i = 1; i < schedule.size(); i++)
	{
		m_CompletionTime[0][i] = (m_CompletionTime[0][i - 1] + m_ProcessTime[0][schedule[i].ui_index]);
	} // end for

	// Calculate the processing time for first job on all machines
	for (std::size_t i = 1; i < m_Machines; i++)
	{
		m_CompletionTime[i][0] = (m_CompletionTime[i - 1][0] + m_ProcessTime[i][schedule[0].ui_index]);
	} // end for

	// Calculate the rest of the processing time
	for (std::size_t i = 1; i < m_Machines; i++) 
	{
		for (std::size_t j = 1; j < schedule.size(); j++)
		{
			max = *Max(&(m_CompletionTime[i][j - 1]), &(m_CompletionTime[i - 1][j]));
			m_CompletionTime[i][j] = m_ProcessTime[i][schedule[j].ui_index] + max;
		} // end for j
	} // end for i

	// Return the makespan.
	return m_CompletionTime[m_Machines - 1][schedule.size() - 1];
} // end method Makespan