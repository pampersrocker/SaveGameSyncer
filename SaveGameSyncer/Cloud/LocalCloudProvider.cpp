#include "stdafx.h"
#include "LocalCloudProvider.h"

LocalCloudProvider::LocalCloudProvider(const QString& InLocalPath)
	: LocalPath(InLocalPath)
{

}

void LocalCloudProvider::StoreFile(const QString& Path, const QByteArray& Bytes)
{
	QFile File = LocalPath.absoluteFilePath(Path);
	File.open(QIODevice::WriteOnly);

	File.write(Bytes);

	File.close();
}

void LocalCloudProvider::ReadFile(const QString& Path, QByteArray& OutBytes)
{
	QFile File = LocalPath.absoluteFilePath(Path);
	
	File.open(QIODevice::ReadOnly);

	OutBytes.append(File.readAll());

	File.close();
}
