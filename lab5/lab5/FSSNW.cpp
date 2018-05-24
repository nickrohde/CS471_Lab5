#include "FSSNW.h"

using namespace std;


double cFSSNW::Makespan(std::vector<Job>& schedule)
{
	std::size_t offset;
	double sum = 0.0;
	Initialize();

	// Calculate processing time for all jobs on first machine
	m_CompletionTime[0][0] = m_ProcessTime[0][schedule[0].ui_index];

	for (std::size_t i = 1; i < m_Machines; i++)
	{
		m_CompletionTime[i][0] = (m_CompletionTime[i - 1][0] + m_ProcessTime[i][schedule[0].ui_index]);
	}

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
					for (int k = j - 1; k >= 0; k--) 
					{
						m_CompletionTime[k][i] = m_CompletionTime[k][i] + offset;
					}
				}

				m_CompletionTime[j][i] = m_CompletionTime[j - 1][i] + m_ProcessTime[j][schedule[i].ui_index];
			}
		}
	}

	// Calculate the flowtime.
	for (std::size_t i = 0; i < schedule.size(); i++) 
	{
		sum += m_CompletionTime[m_Machines - 1][i];
	}

	return sum;
}
