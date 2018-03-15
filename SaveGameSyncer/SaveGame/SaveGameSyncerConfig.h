#pragma once

#include <QObject>
#include "SaveGame/SaveGameConfig.h"

class SaveGameSyncerConfig : public QObject
{
	Q_OBJECT

public:
	SaveGameSyncerConfig(QObject *parent = Q_NULLPTR);
	~SaveGameSyncerConfig();

	void Serialize(QDataStream& Stream);
	

	QList<SaveGameConfig*> Configurations;
};

QDataStream& operator <<(QDataStream& Out, SaveGameSyncerConfig* Item);
QDataStream& operator >>(QDataStream& In, SaveGameSyncerConfig* Item);
