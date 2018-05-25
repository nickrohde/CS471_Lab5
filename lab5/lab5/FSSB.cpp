#include "FSSB.hpp"

using namespace std;

double cFSSB::Makespan(const std::vector<Job>& schedule)
{
	initialize();

	// Calculate processing time for all jobs on first machine
	m_CompletionTime[0][0] = m_ProcessTime[0][schedule[0].ui_index];

	for (std::size_t i = 1; i < m_Machines; i++) 
	{
		m_CompletionTime[i][0] = (m_CompletionTime[i - 1][0] + m_ProcessTime[i][schedule[0].ui_index]);
	} // end for

	// Calculate for each subsequent job
	for (std::size_t i = 1; i < schedule.size(); i++)
	{
		for (std::size_t j = 0; j < m_Machines; j++) 
		{
			if (j == 0)
			{
				m_CompletionTime[j][i] = m_CompletionTime[j][i - 1] + m_ProcessTime[j][schedule[i].ui_index];
			} // end if
			else 
			{
				if (m_CompletionTime[j - 1][i] < m_CompletionTime[j][i - 1]) 
				{
					m_CompletionTime[j - 1][i] = m_CompletionTime[j][i - 1];
				} // end if

				m_CompletionTime[j][i] = m_CompletionTime[j - 1][i] + m_ProcessTime[j][schedule[i].ui_index];
			} // end else
		} // end for j
	} // end for i

	// Return the makespan.
	return m_CompletionTime[m_Machines - 1][schedule.size() - 1];
} // end method Makespan

