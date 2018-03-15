#include "stdafx.h"
#include "CreateSaveGameConfigWindow.h"
#include "SaveGameConfig.h"

CreateSaveGameConfigWindow::CreateSaveGameConfigWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CreateSaveGameConfigWindow::~CreateSaveGameConfigWindow()
{
}


void CreateSaveGameConfigWindow::OkClicked()
{
	SaveGameConfig* Config = new SaveGameConfig();
	Config->Name = ui.nameLineEdit->text();
	Config->Executable = ui.executableLocationLineEdit->text();
	Config->LocalPath = ui.savegameLocationLineEdit->text();

	OnSaveGameConfigCreated(Config);
	done(1);
}

void CreateSaveGameConfigWindow::BrowseExecutable()
{
	ui.executableLocationLineEdit->setText(QFileDialog::getOpenFileName(this,
		tr("Browse Executable"),
		"",
		tr("Executable files (*.exe)")
	));
}

void CreateSaveGameConfigWindow::BrowseSavegameLocation()
{
	ui.savegameLocationLineEdit->setText(QFileDialog::getExistingDirectory(this,
		tr("Browse Save Game Location"),
		""
	));
}

