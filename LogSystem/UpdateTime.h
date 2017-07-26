#pragma once

#include <Windows.h>
#include <Process.h>
#include <iostream>
#include <time.h>

#pragma comment(lib, "Winmm.lib")


class CUpdateTime
{
private:
	CUpdateTime()
	{
		timeBeginPeriod(1);
		b_Exit = false;
	}

	~CUpdateTime()
	{
		timeEndPeriod(1);
	}


public:
	static CUpdateTime* GetInstance()
	{
		static CUpdateTime Instance;
		Instance.Run();
		return &Instance;
	}

	static SYSTEMTIME* GetSystemTime()
	{
		return &NowTime;
	}

	static ULONGLONG* GetTickCount()
	{
		return &TickCount;
	}

	void Run()
	{
		hTimeUpdateThread = (HANDLE)_beginthreadex(nullptr, 0, UpdateTime, this, FALSE, nullptr);
	}

	static UINT WINAPI UpdateTime(LPVOID arg)
	{
		CUpdateTime *pUpdateTime = (CUpdateTime *)arg;

		while (!pUpdateTime->b_Exit)
		{

			pUpdateTime->TickCount = GetTickCount64();
			GetLocalTime(&pUpdateTime->NowTime);

			Sleep(5);
		}

		return 1;
	}


	void CloseThread()
	{
		b_Exit = true;
	}

	static SYSTEMTIME NowTime;
	static ULONGLONG TickCount;
private:
	HANDLE hTimeUpdateThread;
	bool b_Exit;
};

SYSTEMTIME CUpdateTime::NowTime;
ULONGLONG CUpdateTime::TickCount;


