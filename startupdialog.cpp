#include "startupdialog.h"
#include "ui_startupdialog.h"
#include "settings.h"

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QFileDialog>
#include <QtCore/QDebug>

StartupDialog::StartupDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::StartupDialog)
{
	ui->setupUi(this);

	// No Resize / Maximize
	setMinimumSize(width(),height());
	setMaximumSize(width(),height());

	//
	setWindowTitle("Slider3D -- Configuration");

	// load all settings into the UI
	Settings *lSettings = &Settings::getInstance();

	// SETUP monitor combo box
	{
		QString lCurrScreen = "(default)";

		if( lSettings->mMonitor > -1 )
			lCurrScreen = "Monitor "+QString::number(lSettings->mMonitor);

		ui->monitor->addItem("(default)",-1);

		int lNumScreens = QApplication::desktop()->numScreens();
		for(int i=0;i<lNumScreens;i++)
		{
			QString lScreen = "Monitor "+QString::number(i);
			ui->monitor->addItem(lScreen,i);

			if( lScreen == lCurrScreen ) // select it; +1 because the 1st one is default!
				ui->monitor->setCurrentIndex(i+1);
		}
	}

	// SETUP RESOLUTION BOX
	if( lSettings->mWindowed == 1 )
	{
		QString lCurrRes = QString::number(lSettings->mWidth);
				lCurrRes+= "x";
				lCurrRes+= QString::number(lSettings->mHeight);

		bool lFound = false;

		int lNumRes = ui->res->count();
		for(int i=0;i<lNumRes;i++)
		{
			if( ui->res->itemText(i) == lCurrRes )
			{
				ui->res->setCurrentIndex(i);
				lFound = true;
				break;
			}
		}

		//! Add & Select Custom Resolution
		if( !lFound )
		{
			ui->res->addItem(lCurrRes);
			ui->res->setCurrentIndex(ui->res->count()-1);
		}

		ui->windowed->setChecked(true);
	}

	//! SETUP TIMEOUT VALUE
	ui->timeout->setValue(lSettings->mTimeout);

	if( lSettings->mMSSA > 0 )
	{
		QString lCurrMSSA = QString::number(lSettings->mMSSA) + "x";

		bool lFound = false;

		int lNumMSSA = ui->mssa->count();
		for(int i=0;i<lNumMSSA;i++)
		{
			if( ui->mssa->itemText(i) == lCurrMSSA )
			{
				ui->mssa->setCurrentIndex(i);
				lFound = true;
				break;
			}
		}

		//! Add & Select Custom Multi-Sampling
		if( !lFound )
		{
			ui->res->addItem(lCurrMSSA);
			ui->res->setCurrentIndex(ui->mssa->count()-1);
		}
	}

	//! Floor On/Off
	ui->floor->setChecked(lSettings->mFloor);
	//! Labels On/Off
	ui->labels->setChecked(lSettings->mLabels);
	//! Add Paths
	ui->paths->addItems(lSettings->mPaths);
	//! Dive Into Sub Dirs Or Not
	ui->subdirs->setChecked(lSettings->mSubDirs);
	//! Don't Show
	ui->dontshow->setChecked(lSettings->mDontShow);

	//! SETUP CONNECTIONS
	connect(ui->addfolder,SIGNAL(clicked()),this,SLOT(addPath()));
	connect(ui->removefolder,SIGNAL(clicked()),this,SLOT(removePath()));
	connect(ui->moveup,SIGNAL(clicked()),this,SLOT(movePathUp()));
	connect(ui->movedown,SIGNAL(clicked()),this,SLOT(movePathDown()));
}

StartupDialog::~StartupDialog()
{
	delete ui;
}

void StartupDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type())
	{
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void StartupDialog::accept(void)
{
	Settings *lSettings = &Settings::getInstance();

	lSettings->mDontShow	= ui->dontshow->isChecked();
	lSettings->mSubDirs		= ui->subdirs->isChecked();

	//! Clear Old Values
	lSettings->mPaths.clear();

	//! Copy over the new values
	int lNumPaths = ui->paths->count();
	for(int i=0;i<lNumPaths;i++)
		lSettings->mPaths << ui->paths->item(i)->text();

	lSettings->mFloor	= ui->floor->isChecked();
	lSettings->mLabels	= ui->labels->isChecked();

	QString lMSSA = ui->mssa->currentText();
	if( lMSSA == "(none)" )
		lSettings->mMSSA = 0;
	else
		lSettings->mMSSA = lMSSA.replace("x","").toInt();

	lSettings->mTimeout		= ui->timeout->value();
	lSettings->mWindowed	= ui->windowed->isChecked();

	if( lSettings->mWindowed == 1 )
	{
		QString lRes = ui->res->currentText();
		QStringList lTmp = lRes.split("x");
		if( lTmp.count() == 2 )
		{
			lSettings->mWidth = lTmp[0].toInt();
			lSettings->mHeight= lTmp[1].toInt();
		}
	}

	QString lMonitor = ui->monitor->currentText();
	if( lMonitor == "(default)" )
		lSettings->mMonitor = -1;
	else
		lSettings->mMonitor = lMonitor.replace("Monitor ","").toInt();

	lSettings->save();
	QDialog::accept();
}

void StartupDialog::addPath(void)
{
	QFileDialog lDialog(this);
	lDialog.setFileMode(QFileDialog::DirectoryOnly);

	QString lPath = lDialog.getExistingDirectory();

	if( lPath.isEmpty() )
		return;

	//! Make sure it has a trailing slash
	if( !lPath.endsWith(QDir::separator()) )
		lPath += QDir::separator();

	ui->paths->addItem(lPath);

	Settings *lSettings = &Settings::getInstance();
	lSettings->mPaths << lPath;
}

void StartupDialog::removePath(void)
{
	int lRow = ui->paths->currentRow();
	if( lRow >= 0 )
	{
		QListWidgetItem *lItem = ui->paths->takeItem(lRow);
		delete lItem;
	}
}

void StartupDialog::movePathUp(void)
{
	int lRow = ui->paths->currentRow();
	if( lRow > 0 )
	{
		QListWidgetItem *lItem = ui->paths->takeItem(lRow);

		ui->paths->insertItem(lRow-1,lItem);
		ui->paths->setCurrentRow(lRow-1);
	}
}

void StartupDialog::movePathDown(void)
{
	int lRow = ui->paths->currentRow();
	if( lRow < (ui->paths->count() - 1) )
	{
		QListWidgetItem *lItem = ui->paths->takeItem(lRow);

		ui->paths->insertItem(lRow+1,lItem);
		ui->paths->setCurrentRow(lRow+1);
	}
}
