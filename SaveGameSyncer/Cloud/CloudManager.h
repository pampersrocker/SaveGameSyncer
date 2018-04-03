#pragma once

#include <QVector>

class ICloudProvider;

class CloudManager
{
public:

	static CloudManager& Get();

	void RegisterCloudProvider(ICloudProvider* Provider);
	void RemoveCloudProvider(ICloudProvider* Provider);

	/// Marks this cloud as primary cloud when fetching data, other clouds will be treated as additional backups
	void SetPrimaryCloud(ICloudProvider* Provider);

	void StoreFile(const QString& Path, const QByteArray& Data);
	void ReadFile (const QString& Path, QByteArray& OutData);

	const QVector<ICloudProvider*>& GetProviders() const;

private:

	CloudManager();
	CloudManager(const CloudManager&) = delete;

	int PrimaryIndex;
	QVector<ICloudProvider*> CloudProviders;
};
