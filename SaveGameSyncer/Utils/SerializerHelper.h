#pragma once
#include "QDataStream"


class SerializerHelper
{
public:

	SerializerHelper(QDataStream& Stream);

	template<typename T>
	SerializerHelper& operator <<(T& Data);

protected:
private:

	QDataStream& Stream;
};

template<typename T>
SerializerHelper& SerializerHelper::operator<<(T& Data)
{
	if (Stream.device()->openMode() == QIODevice::ReadOnly)
	{
		Stream >> Data;
	}
	else
	{
		Stream << Data;
	}
	return *this;
}
