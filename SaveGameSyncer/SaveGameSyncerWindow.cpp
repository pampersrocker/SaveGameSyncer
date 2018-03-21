#include "stdafx.h"
#include "SaveGameSyncerWindow.h"
#include "CreateSaveGameConfigWindow.h"
#include "SaveGameSyncerConfig.h"
#include "Utils/ProcessUtil.h"
#include "SavegameSyncer.h"

SaveGameSyncerWindow::SaveGameSyncerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Configuration = new SaveGameSyncerConfig();
	LoadConfig();

	UpdateSaveGamesTimer = new QTimer(this);
	connect(UpdateSaveGamesTimer, SIGNAL(timeout()), this, SLOT(UpdateSaveGames()));
	UpdateSaveGamesTimer->start(std::chrono::minutes(1));
}

void SaveGameSyncerWindow::CreateNewSync()
{
	CreateSaveGameConfigWindow* CreateConfigWindow = new CreateSaveGameConfigWindow(this);

	connect(CreateConfigWindow, SIGNAL(OnSaveGameConfigCreated(SaveGameConfig*)), this, SLOT(AddSaveGameConfig(SaveGameConfig*)));
	CreateConfigWindow->setWindowModality(Qt::WindowModal);
	CreateConfigWindow->setAttribute(Qt::WA_DeleteOnClose);
	CreateConfigWindow->exec();
}

void SaveGameSyncerWindow::AddSaveGameConfig(SaveGameConfig* Config)
{
	Configuration->Configurations.append(Config);
	SaveConfig();
}

void SaveGameSyncerWindow::SaveConfig()
{
	QFile file = GetConfigFile();
	file.open(QIODevice::WriteOnly);

	QDataStream stream(&file);

	stream << Configuration;

	file.close();
}

void SaveGameSyncerWindow::UpdateSaveGames()
{
	qDebug() << "Checking for save games changes";
	QVector<QFileInfo> ProcessList;
	ProcessUtil::GetRunningProcesses(ProcessList);
	qDebug() << "Found " << ProcessList.size() << " running processes";

	for (SaveGameConfig* Config : Configuration->Configurations)
	{
		QFileInfo ConfigFileInfo(Config->Executable);
		if (ProcessList.contains(ConfigFileInfo))
		{
			qDebug() << "Skipping " << Config->Name << " because it is running";
			continue;
		}
		SaveGameSyncer Syncer;
		Syncer.PerformSync(Config);
	}
}

QString SaveGameSyncerWindow::GetConfigFile()
{
	QDir Path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	if (!Path.exists())
	{
		Path.mkpath(".");
	}
	return Path.filePath("config.dat");
}

void SaveGameSyncerWindow::LoadConfig()
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
