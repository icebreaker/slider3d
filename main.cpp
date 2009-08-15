/*=============================================================================
 Copyright (c) 2009, Mihail Szabolcs
 All rights reserved.

 Redistribution and use in source and binary forms, with or
 without modification, are permitted provided that the following
 conditions are met:

   * 	Redistributions of source code must retain the above copyright
		notice, this list of conditions and the following disclaimer.

   * 	Redistributions in binary form must reproduce the above copyright
		notice, this list of conditions and the following disclaimer in
		the documentation and/or other materials provided with the
		distribution.

   * 	Neither the name of the Slider3D nor the names of its contributors
		may be used to endorse or promote products derived from this
		software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
	ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
	LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
	OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
	SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
	INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
	CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
	THE POSSIBILITY OF SUCH DAMAGE.

	This file is part of Slider3D.

==============================================================================*/
#include <QtGui/QApplication>
#include <QtOpenGL>

#include "mainwindow.h"
#include "texturemanager.h"
#include "types.h"
#include "startupdialog.h"
#include "settings.h"

using namespace GL;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Settings *lSettings = &Settings::getInstance();
	lSettings->load();

	bool lShowConfig = false;
	// PARSE COMMAND LINE ARGUMENTS
	{
		QStringList lArgs = a.arguments();
		// arguments?
		if( lArgs.size() > 1 )
		{
			// parse
			for(int i=0;i<lArgs.size();i++)
			{
				// FORCE CONFIGURATION DIALOG
				if( lArgs[i] == "--config" )
					lShowConfig = true;
			}
		}
	}

	//! SHOW STARTUP CONFIGURATION DIALOG
	if( lSettings->mDontShow == 0 || lShowConfig )
	{
		StartupDialog lDlg;
		lDlg.show();

		//! BAIL OUT ON CANCEL ...
		if( lDlg.exec() == QDialog::Rejected )
		{
			return 13;
		}
	}

	//! Setup Default Pixel Format for all QGL Widgets
	{
		QGLFormat lGLFrm = QGLFormat::defaultFormat();
		lGLFrm.setDoubleBuffer(true);
		lGLFrm.setDepth(true);
		if( lSettings->mFloor ) // Stencil Buffer
		{
			lGLFrm.setStencil(true);
			lGLFrm.setAlpha(true);
			lGLFrm.setAccum(true);
			lGLFrm.setRgba(true);
		}
		if( lSettings->mMSSA ) // Multi-Sampling
		{
			lGLFrm.setSampleBuffers(true);
			lGLFrm.setSamples(lSettings->mMSSA);
		}
		QGLFormat::setDefaultFormat(lGLFrm);
	}

	MainWindow w;

	//! Set Target Monitor
	if( lSettings->mMonitor > -1 && lSettings->mWindowed != 1 )
	{
		w.setGeometry(QApplication::desktop()->availableGeometry(lSettings->mMonitor));
	}

	//! Set FullScreen / Windowed Mode
	if( lSettings->mWindowed != 1 )
	{
		w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);
	}

	//! Show Main SlideShow Window
	w.show();

	//! Check the number of photos
	if( !TextureManager::getInstance().getCount() )
	{
		//! Minimize Main Window
		w.setWindowState(w.windowState() ^ Qt::WindowMinimized);

		//! Bring Message Box to Front
		QMessageBox lMsg;
		lMsg.setText("No photos found! Are you kidding me?");
		lMsg.setIcon(QMessageBox::Warning);
		lMsg.exec();

		//! Perform Clean-up and exit ...
		QApplication::quit();
		return 0;
	}

	return a.exec();
}
