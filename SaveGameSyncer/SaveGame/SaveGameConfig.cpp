#include "stdafx.h"
#include "SaveGame/SaveGameConfig.h"
#include "Utils/SerializerHelper.h"

SaveGameConfig::SaveGameConfig(QObject *parent)
	: QObject(parent)
	, Name()
	, LocalPath()
	, Executable()

{
}

SaveGameConfig::~SaveGameConfig()
{
}



void SaveGameConfig::Serialize(QDataStream& Stream)
{
	SerializerHelper Ar(Stream);

	Ar << Name;
	Ar << LocalPath;
	Ar << Executable;
}

QDataStream& operator<<(QDataStream &Out, SaveGameConfig &Config)
{
	Config.Serialize(Out);
	return Out;
}

QDataStream& operator>>(QDataStream &In, SaveGameConfig *&Config)
{
	Config = new SaveGameConfig();
	Config->Serialize(In);
	return In;
}
