#include "stdafx.h"
#include "SaveGameSyncer.h"
#include "CreateSaveGameConfigWindow.h"
#include "SaveGameSyncerConfig.h"

SaveGameSyncer::SaveGameSyncer(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Configuration = new SaveGameSyncerConfig();
	LoadConfig();
}

void SaveGameSyncer::CreateNewSync()
{
	CreateSaveGameConfigWindow* CreateConfigWindow = new CreateSaveGameConfigWindow(this);

	connect(CreateConfigWindow, SIGNAL(OnSaveGameConfigCreated(SaveGameConfig*)), this, SLOT(AddSaveGameConfig(SaveGameConfig*)));
	CreateConfigWindow->setWindowModality(Qt::WindowModal);
	CreateConfigWindow->setAttribute(Qt::WA_DeleteOnClose);
	CreateConfigWindow->exec();
}

void SaveGameSyncer::AddSaveGameConfig(SaveGameConfig* Config)
{
	Configuration->Configurations.append(Config);
	SaveConfig();
}

void SaveGameSyncer::SaveConfig()
{
	QFile file = GetConfigFile();
	file.open(QIODevice::WriteOnly);

	QDataStream stream(&file);

	stream << Configuration;

	file.close();
}

QString SaveGameSyncer::GetConfigFile()
{
	QDir Path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	if (!Path.exists())
	{
		Path.mkpath(".");
	}
	return Path.filePath("config.dat");
}

void SaveGameSyncer::LoadConfig()
{
	QFile file = GetConfigFile();
	if (!file.exists())
	{
		return;
	}

	file.open(QIODevice::ReadOnly);

	QDataStream stream(&file);

	stream >> Configuration;

	file.close();

}
