#include "stdafx.h"
#include "CloudManager.h"
#include "ICloudProvider.h"



CloudManager& CloudManager::Get()
{
	static CloudManager Instance;

	return Instance;
}

void CloudManager::RegisterCloudProvider(ICloudProvider* Provider)
{
	if (!CloudProviders.contains(Provider))
	{
		CloudProviders.push_back(Provider);
	}
}

void CloudManager::RemoveCloudProvider(ICloudProvider* Provider)
{
	ICloudProvider* PrimaryCloudProvider = PrimaryIndex >= 0 ? CloudProviders[PrimaryIndex] : nullptr;
	CloudProviders.removeAll(Provider);
	PrimaryIndex = CloudProviders.indexOf(PrimaryCloudProvider);
}

void CloudManager::SetPrimaryCloud(ICloudProvider* Provider)
{
	PrimaryIndex = CloudProviders.indexOf(Provider);
}

void CloudManager::StoreFile(const QString& Path, const QByteArray& Data)
{
	for (ICloudProvider* Provider : CloudProviders)
	{
		Provider->StoreFile(Path, Data);
	}
}

void CloudManager::ReadFile(const QString& Path, QByteArray& OutData)
{
	if (CloudProviders.size() == 0)
	{
		qCritical() << "No cloud providers registered, cannot read file!";
		return;
	}
	if (PrimaryIndex >= 0)
	{
		CloudProviders[PrimaryIndex]->ReadFile(Path, OutData);
	}
	else
	{
		qWarning() << "No primary cloud provider set, using the first registered one as primary!";
		CloudProviders[0]->ReadFile(Path, OutData);
	}
}

const QVector<ICloudProvider*>& CloudManager::GetProviders() const
{
	return CloudProviders;
}

CloudManager::CloudManager()
	: CloudProviders()
	, PrimaryIndex(-1)
{

}
