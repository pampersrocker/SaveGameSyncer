#include "stdafx.h"
#include "SaveGameSyncer.h"
#include "SaveGameConfig.h"
#include "Cloud\CloudManager.h"
#include "quazip.h"



void SaveGameSyncer::PerformSync(SaveGameConfig* Config)
{
	qDebug() << "Performing sync for " << Config->Name << " in directory " << Config->LocalPath;

	QString MetaDataPath = Config->Name + "/Meta.dat";

	QByteArray RawMetaData;
	CloudManager::Get().ReadFile(MetaDataPath, RawMetaData);

	bool CreateBackup = false;

	if (RawMetaData.size() == 0)
	{
		qDebug() << "Found no stored meta data for " << Config->Name << ". Treating as new save";
		CreateBackup = true;
	}
	else
	{
		// TODO: Parse MetaData
	}

	if (CreateBackup)
	{
		QBuffer DataBuffer;
		QuaZip ZipFile(&DataBuffer);

		if (!ZipFile.open(QuaZip::mdCreate))
		{
			qCritical() << "Failed to open zip file!";
			return;
		}

		ZipFile.close();
	}

}
