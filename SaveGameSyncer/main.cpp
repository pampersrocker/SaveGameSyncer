#include "stdafx.h"
#include "SaveGameSyncer.h"
#include <QtWidgets/QApplication>

QFile* LogFile = nullptr;

void LogMessageHandler(QtMsgType Type, const QMessageLogContext& Context, const QString& Message)
{
	if (!LogFile)
	{
		return;
	}

	QString TypeString;
	switch (Type)
	{
	case QtDebugMsg:
		TypeString = "Debg";
		break;
	case QtWarningMsg:
		TypeString = "Warn";
		break;
	case QtCriticalMsg:
		TypeString = "Crit";
		break;
	case QtFatalMsg:
		TypeString = "Fata";
		break;
	case QtInfoMsg:
		TypeString = "Info";
		break;
	default:
		break;
	}

	QTextStream Stream(LogFile);

	Stream << "[" << QDateTime::currentDateTime().toString(Qt::ISODate) << "][" << TypeString << "]: " << Message
		<< "(" << Context.file << "(" << Context.line << "), " << Context.function << ")" << endl;
	Stream.flush();
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogFile = new QFile(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/log.txt");
	LogFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
	qInstallMessageHandler(LogMessageHandler);

	qDebug() << "####";
	qDebug() << "Starting application";
	SaveGameSyncer w;
	w.show();
	int Result = a.exec();

	LogFile->close();
	delete LogFile;
	LogFile = nullptr;

	return Result;
}
