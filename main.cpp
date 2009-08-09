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

using namespace GL;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QStringList lArgs = a.arguments();

	// TODO: implemenent serializable SETTINGS!!!
	int lMonitor = 0;

	// arguments?
	if( lArgs.size() > 1 )
	{
		// parse
		for(int i=0;i<lArgs.size()-1;i++)
		{
			if( lArgs[i] == "--monitor" )
				lMonitor = lArgs[i+1].toInt();
		}
	}

	// ask for 4x multi-sampling ... real nice edges :)
	QGLFormat lGLFrm = QGLFormat::defaultFormat();
	lGLFrm.setStencil(true);
	lGLFrm.setAlpha(true);
	lGLFrm.setDoubleBuffer(true);
	lGLFrm.setDepth(true);
	lGLFrm.setAccum(true);
	lGLFrm.setRgba(true);
	lGLFrm.setSampleBuffers(true);
	lGLFrm.setSamples(4);
	QGLFormat::setDefaultFormat(lGLFrm);

	MainWindow w;

	if( lMonitor )
		w.setGeometry(QApplication::desktop()->availableGeometry(lMonitor));

	w.setWindowState(w.windowState() ^ Qt::WindowFullScreen);
	w.show();

	if( !TextureManager::getInstance().getCount() )
	{
		QMessageBox lMsg;
		lMsg.setText("No photos found!");
		lMsg.setIcon(QMessageBox::Warning);
		lMsg.exec();

		// clean-up
		QApplication::quit();
		return 0;
	}

	return a.exec();
}
