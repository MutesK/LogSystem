#include "CSystemLog.h"
#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;


int main()
{
//	pLog->SetLogDirectory(L"AllofLog");
	SYSLOG_DIRECTROYSET(L"AllofLog");
	SYSLOG_SET(LOG_DEBUG);

	while (1)
	{
		if (kbhit())
		{
			srand(time(NULL));
			ULONG64 Test = rand() % MAXULONG64;

			wcout << "Test For HexFunction :" << Test << endl;

		//	pLog->Log(L"Test", LOG_ERROR, L"TEST ERROR");
			SYSLOG(L"Test", LOG_DEBUG, L"TEST ERROR");
		//	pLog->LogHex(L"Test", LOG_DEBUG, L"Test for Hex", (BYTE *)&Test, sizeof(ULONG64));
			SYSLOGHEX(L"Test", LOG_DEBUG, L"TEST ERROR", (BYTE *)&Test, sizeof(ULONG64));
			getch();
		}
	}

	return 0;
}