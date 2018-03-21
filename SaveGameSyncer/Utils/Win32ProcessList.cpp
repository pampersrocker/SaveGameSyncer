#include "stdafx.h"
#include "Win32ProcessList.h"



void WindowsProcessUtil::GetRunningProcesses(QVector<QFileInfo>& ProcessList)
{
	QVector<DWORD> ProcessIdList;
	ProcessIdList.resize(1024);

	DWORD bytesRead;
	bool ReadMaximumAmount = false;
	do
	{

		if (!EnumProcesses(ProcessIdList.data(), ProcessIdList.size() * sizeof(DWORD), &bytesRead))
		{
			return;
		}
		// Check if we possible exceeded our array and retry if we do so.
		ReadMaximumAmount = bytesRead == ProcessIdList.size() * sizeof(DWORD);
		if (ReadMaximumAmount)
		{
			ProcessIdList.resize(ProcessIdList.size() * 2);
		}
		else
		{
			ProcessIdList.resize(bytesRead / sizeof(DWORD));
		}
	} while (ReadMaximumAmount);
	// We expect to be able to read all processes we got.
	ProcessList.reserve(ProcessIdList.size());
	for (DWORD ProcessId : ProcessIdList)
	{
		HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, ProcessId);
		if (hProcess)
		{
			HMODULE hMod;
			DWORD cbNeeded;
			TCHAR szProcessName[2048];

			if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
				&cbNeeded))
			{
				if (GetModuleFileNameEx(hProcess, hMod, szProcessName,
					sizeof(szProcessName) / sizeof(TCHAR)))
				{
					ProcessList.append(QString::fromWCharArray(szProcessName));
				}
			}
		}
	}
}
