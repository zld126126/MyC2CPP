#pragma once

#ifdef WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif //WIN32

class CLock
{
#ifdef WIN32
public:
	explicit CLock(LPCRITICAL_SECTION lpcs) :m_lpCS(lpcs)
	{
		EnterCriticalSection(m_lpCS);
	}
	~CLock()
	{
		LeaveCriticalSection(m_lpCS);
	}
private:
	LPCRITICAL_SECTION m_lpCS;
#else
public:
	explicit CLock(pthread_mutex_t *pmt) :m_pMt(pmt)
	{
		pthread_mutex_lock(m_pMt);
	}
	~CLock()
	{
		pthread_mutex_unlock(m_pMt);
	}
private:
	pthread_mutex_t * m_pMt;
#endif //WIN32
};


