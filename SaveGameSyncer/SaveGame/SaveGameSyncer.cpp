#include "stdafx.h"
#include "SaveGameSyncer.h"
#include "SaveGameConfig.h"



void SaveGameSyncer::PerformSync(SaveGameConfig* Config)
{
	qDebug() << "Performing sync for " << Config->Name << " in directory " << Config->LocalPath;
}
