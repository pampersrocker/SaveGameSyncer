#pragma once

#include <QWidget>
#include "ui_CreateSaveGameConfigWindow.h"

class SaveGameConfig;

class CreateSaveGameConfigWindow : public QDialog
{
	Q_OBJECT

public:
	CreateSaveGameConfigWindow(QWidget *parent = Q_NULLPTR);
	~CreateSaveGameConfigWindow();

public slots:
	void OkClicked();
	void BrowseExecutable();
	void BrowseSavegameLocation();

signals:
	void OnSaveGameConfigCreated(SaveGameConfig* Config);

private:
	Ui::CreateSaveGameConfigWindow ui;
};
