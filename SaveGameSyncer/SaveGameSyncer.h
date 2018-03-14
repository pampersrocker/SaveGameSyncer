#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SaveGameSyncer.h"

class SaveGameSyncer : public QMainWindow
{
	Q_OBJECT

public:
	SaveGameSyncer(QWidget *parent = Q_NULLPTR);

private:
	Ui::SaveGameSyncerClass ui;
};
