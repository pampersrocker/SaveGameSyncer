#pragma once

#include <QVector>
#include <QFileInfo>
#include <windows.h>
#include <psapi.h>

class WindowsProcessUtil
{
public:
	static void GetRunningProcesses(QVector<QFileInfo>& ProcessList);
};
