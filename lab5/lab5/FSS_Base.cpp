#include "FSS_Base.hpp"



cFSS_Base::cFSS_Base(std::string s_fileName)
{
	std::ifstream infile(s_fileName.c_str(), std::ios::in);

	if (!infile.is_open() || infile.bad())
	{
		std::cout << "Error Opening File.\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		infile >> m_Machines;
		infile >> m_Jobs;

		instantiate();
		Initialize();

		for (std::size_t i = 0; i < (m_Machines); i++)
		{
			for (std::size_t j = 0; j < m_Jobs; j++)
			{
				infile >> m_ProcessTime[i][j];
			}
		}
	}

	infile.close();
}


cFSS_Base::~cFSS_Base(void)
{
	for (std::size_t i = 0; i < m_Machines; i++)
	{
		delete[] m_ProcessTime[i];
	}
	delete[] m_ProcessTime;

	for (std::size_t i = 0; i < m_Machines; i++)
	{
		delete[] m_CompletionTime[i];
	}
	delete[] m_CompletionTime;
}


void cFSS_Base::Initialize(void)
{
	for (std::size_t i = 0; i < m_Machines; i++)
	{
		for (std::size_t j = 0; j < m_Jobs; j++)
		{
			m_CompletionTime[i][j] = 0;
		}
	}
}


void cFSS_Base::instantiate(void)
{
	m_ProcessTime = new double*[m_Machines];

	for (std::size_t i = 0; i < m_Machines; i++)
	{
		m_ProcessTime[i] = new double[m_Jobs];
	}

	m_CompletionTime = new double*[m_Machines];
	for (std::size_t i = 0; i < m_Machines; i++)
	{
		m_CompletionTime[i] = new double[m_Jobs];
	}
} // end method instantiate


std::vector<Job>* cFSS_Base::schedule(void)
{
	return NEH(jobs());
} // end method schedule


std::vector<Job>* cFSS_Base::jobs(void)
{
	auto jobs = new std::vector<Job>();

	for (std::size_t j = 0; j < m_Jobs; j++)
	{
		Job temp(0.0, j);

		for (std::size_t i = 0; i < m_Machines; i++)
		{
			temp.d_time += m_ProcessTime[i][j];
		} // end for j

		jobs->push_back(temp);
	} // end for i

	return jobs;
} // end method jobs


std::vector<Job>* cFSS_Base::NEH(std::vector<Job>* jobs)
{
	std::sort(jobs->begin(), jobs->end(), std::greater<Job>());

	auto schedule = new std::vector<Job>();
	schedule->reserve(jobs->size());

	schedule->push_back((*jobs)[0]);

	for (size_t i = 1; i < jobs->size(); i++)
	{
		insertJob(*schedule, (*jobs)[i]);
	} // end for

	delete jobs;

	return schedule;
} // end method NEH


void cFSS_Base::insertJob(std::vector<Job>& jobs, Job & job)
{
	double	d_bestTime = getDoubleMax(),
			d_tempTime = 0.0;
	std::size_t ui_best = 0;

	for (std::size_t i = 0; i <= jobs.size(); i++)
	{
		// try putting job into the ith spot
		jobs.insert(jobs.begin() + i, job);

		// calculate time for this permutation
		d_tempTime = Makespan(jobs);

		// remove job for next loop
		jobs.erase(jobs.begin() + i);

		// check if this was a better place to put it
		if (d_tempTime < d_bestTime)
		{
			ui_best = i;
			d_bestTime = d_tempTime;
		} // end if
	} // end for

	  // put job into the schedule at best location
	jobs.insert(jobs.begin() + ui_best, job);
} // end method insertJob