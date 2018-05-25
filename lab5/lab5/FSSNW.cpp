#include "FSSNW.hpp"

using namespace std;


double cFSSNW::Makespan(const std::vector<Job>& schedule)
{
	double	offset = 0.0,
			sum = 0.0;
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
			}
			else 
			{
				if (m_CompletionTime[j - 1][i] < m_CompletionTime[j][i - 1]) 
				{
					offset = m_CompletionTime[j][i - 1] - m_CompletionTime[j - 1][i];
					for (int k = static_cast<int>(j - 1); k >= 0; k--) 
					{
						m_CompletionTime[k][i] = m_CompletionTime[k][i] + offset;
					} // end for
				} // end if

				m_CompletionTime[j][i] = m_CompletionTime[j - 1][i] + m_ProcessTime[j][schedule[i].ui_index];
			} // end else
		} // end for j
	} // end for i

	// Calculate the flowtime.
	for (std::size_t i = 0; i < schedule.size(); i++) 
	{
		sum += m_CompletionTime[m_Machines - 1][i];
	} // end for

	return sum;
} // end method Makespan
