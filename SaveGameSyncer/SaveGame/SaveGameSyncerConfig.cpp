#include "stdafx.h"
#include "SaveGameSyncerConfig.h"
#include "Utils/SerializerHelper.h"

SaveGameSyncerConfig::SaveGameSyncerConfig(QObject *parent)
	: QObject(parent)
{
}

SaveGameSyncerConfig::~SaveGameSyncerConfig()
{
}

void SaveGameSyncerConfig::Serialize(QDataStream& Stream)
{
	SerializerHelper Ar(Stream);
	Ar << Configurations;
}

QDataStream& operator<<(QDataStream& Out, SaveGameSyncerConfig* Item)
{
	Item->Serialize(Out);
	return Out;
}

QDataStream& operator>>(QDataStream& In, SaveGameSyncerConfig* Item)
{
	Item->Serialize(In);
	return In;
}
