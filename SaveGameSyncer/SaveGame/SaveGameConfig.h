#pragma once

#include <QObject>

class SaveGameConfig : public QObject
{
	Q_OBJECT

public:
	SaveGameConfig(QObject *parent = Q_NULLPTR);
	~SaveGameConfig();

	QString Name;
	QString LocalPath;
	QString Executable;

	void Serialize(QDataStream& Stream);
};

QDataStream& operator<<(QDataStream &Out, SaveGameConfig &Config);

QDataStream& operator>>(QDataStream &In, SaveGameConfig *&Config);
