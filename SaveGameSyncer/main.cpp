#include "stdafx.h"
#include "SaveGameSyncer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SaveGameSyncer w;
	w.show();
	return a.exec();
}
