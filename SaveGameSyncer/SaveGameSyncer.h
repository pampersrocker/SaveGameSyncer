#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SaveGameSyncer.h"

class SaveGameConfig;
class SaveGameSyncerConfig;

class SaveGameSyncer : public QMainWindow
{
	Q_OBJECT

public:
	SaveGameSyncer(QWidget *parent = Q_NULLPTR);

public slots:
	void CreateNewSync();
	void AddSaveGameConfig(SaveGameConfig* Config);
	void SaveConfig();

	QString GetConfigFile();

	void LoadConfig();

private:
	Ui::SaveGameSyncerClass ui;

	SaveGameSyncerConfig* Configuration;
};
