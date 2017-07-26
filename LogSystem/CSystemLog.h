#pragma once

/*
Mute>

	CSystemLog

	�ý��� �α� Ŭ����

	1. GetInstance �ϸ� �����ȴ�.
	2. �⺻������ �α׷����� LOG_DEBUG
	3. �ν��Ͻ� �����ߴٸ� ���丮 ������ �ʼ������� �ؾߵȴ�.

Tip)
	���� ������ �ɰ�� ���ڿ� �ʰ��� �ǽɵȴٸ� ��ũ�� ������ �ٲ��ش�.
*/

#include <Windows.h>
#include <iostream>
#include <strsafe.h>

enum en_LOG_LEVEL
{
	LOG_DEBUG = 0,
	LOG_WARNING,
	LOG_ERROR,
	LOG_SYSTEM,
};

#define dfLOGMSGLEN_MAX 256


class CSystemLog
{
private:
	CSystemLog(en_LOG_LEVEL LogLevel);
	~CSystemLog();
	

public:

	//------------------------------------------------------
	// �̱��� Ŭ����, 
	//------------------------------------------------------
	static CSystemLog *GetInstance(en_LOG_LEVEL LogLevel = LOG_DEBUG)
	{
		static CSystemLog Log(LogLevel);
		return &Log;
	}

	//------------------------------------------------------
	// �ܺο��� �α׷��� ����
	//------------------------------------------------------
	void SetLogLevel(en_LOG_LEVEL LogLevel) { _SaveLogLevel = LogLevel; }

	//------------------------------------------------------
	// �α� ��� ����.
	//------------------------------------------------------
	void SetLogDirectory(WCHAR *szDirectory)
	{
		_wmkdir(szDirectory);
		wsprintf(_SaveDirectory, L"%s\\", szDirectory);
	}

	//------------------------------------------------------
	// ���� �α� ����� �Լ�.
	// szStringFormat�� �ð� �� ���� �ǹ̴� �������� ����� �޼��� �������� �ִ´�.
	// ex) Log(L"ERROR", LOG_ERROR, L"LOG ERROR BUFFER SIZE OVER \n");
	//------------------------------------------------------
	void Log(WCHAR *szType, en_LOG_LEVEL LogLevel, WCHAR *szStringFormat, ...);

	//------------------------------------------------------
	// BYTE ���̳ʸ��� ���� �α� ���
	// ����׿��� �޸� ���°Ͱ� ����ϰ� ������ִ� ��
	//------------------------------------------------------
	void LogHex(WCHAR *szType, en_LOG_LEVEL LogLevel, WCHAR *szLog, BYTE *pByte, int iByteLen);



private:

	unsigned long	_LogNo;
	SRWLOCK			_srwLock;

	en_LOG_LEVEL	_SaveLogLevel;
	WCHAR			_SaveDirectory[25];
};

