#pragma once

#include "ICloudProvider.h"
#include <QDir>

class LocalCloudProvider : 
	public ICloudProvider
{
public:

	LocalCloudProvider(const QString& LocalPath);

	// Inherited via ICloudProvider
	virtual void StoreFile(const QString & Path, const QByteArray & Bytes) override;
	virtual void ReadFile(const QString & Path, QByteArray & OutBytes) override;

private:

	QDir LocalPath;
};