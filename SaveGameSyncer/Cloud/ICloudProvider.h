#pragma once

#include <QString>
#include <QByteArray>

class ICloudProvider
{
public:
	virtual void StoreFile(const QString& Path, const QByteArray& Bytes) = 0;
	virtual void ReadFile(const QString& Path, QByteArray& OutBytes) = 0;
};