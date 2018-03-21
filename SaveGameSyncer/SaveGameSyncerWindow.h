#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SaveGameSyncerWindow.h"

class SaveGameConfig;
class SaveGameSyncerConfig;

class SaveGameSyncerWindow : public QMainWindow
{
	Q_OBJECT

public:
	SaveGameSyncerWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void CreateNewSync();
	void AddSaveGameConfig(SaveGameConfig* Config);
	void SaveConfig();
	void UpdateSaveGames();

	QString GetConfigFile();

	void LoadConfig();

private:
	Ui::SaveGameSyncerClass ui;

	SaveGameSyncerConfig* Configuration;

	QTimer* UpdateSaveGamesTimer;
};
