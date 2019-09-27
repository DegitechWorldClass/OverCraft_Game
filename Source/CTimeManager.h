#pragma once
#include "CSingleton.h"
#include "CTimer.h"

class CTimeManager :
	public CSingleton<CTimeManager>
{
public:
	CTimeManager();
	~CTimeManager();
public:
	FLOAT DeltaTime;
private:
	map<string, CTimer *> m_Timers;
public:
	CTimer * AddTimer(CRString _Key, CTimer * _pTimer);
	CTimer * FindTimer(CRString _Key);
	void RemoveTimer(CRString _Key);


	void Update();
};

#define TIME (*CTimeManager::GetInstance())
#define GetNowTimepoint chrono::system_clock::now()
