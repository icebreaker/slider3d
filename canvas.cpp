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
#include "canvas.h"

#include <QGLWidget>
#include <QtOpenGL>
#include <QtGui/QApplication>

#include "slider.h"
#include "settings.h"
#include "defines.h"

using namespace GL;

Canvas::Canvas(QWidget *pParent) :  QGLWidget(pParent),
									mTimer(new QTimer(this)),
									mQuads(0),
									mSlider(0)
{
	// MOUSE
	setMouseTracking(true);
	// HIDE
	setCursor(Qt::BlankCursor);
	// KEYBOARD
	setFocusPolicy(Qt::StrongFocus);
	// RESIZE
	setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
	// CONNECT THE GL UPDATE
	connect(mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
	mTimer->start(33); // ~30 fps
}

Canvas::~Canvas()
{
	// SHUTDOWN UPDATE TIMER
	if( mTimer )
		delete mTimer;

	if( mSlider )
		delete mSlider;
}

void Canvas::initializeGL(void)
{
	Settings *lSettings = &Settings::getInstance();

	glShadeModel(GL_SMOOTH);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[] = {2.0f, 2.0f, 4.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	// set a visually pleasant background color
	glClearColor(0.0, 0.0, 0.0, 1.0f);

	glEnable(GL_TEXTURE_2D);  // we always want textures

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);

	if( lSettings->mMSSA )
	{
		glEnable(GL_MULTISAMPLE);

		{
			int lBufs;
			int lSamples;
			glGetIntegerv(GL_SAMPLE_BUFFERS, &lBufs);
			glGetIntegerv(GL_SAMPLES, &lSamples);
#ifdef _DEBUG
			qDebug("Success: [Canvas] %d buffers and %d samples", lBufs, lSamples);
#endif

			if( !lBufs || !lSamples ) // not available?
				lSettings->mMSSA = 0;
		}
	}

	if( lSettings->mFloor )
	{
		int lStencil;
		glGetIntegerv(GL_STENCIL_BITS,&lStencil);
#ifdef _DEBUG
		qDebug("Success: [Canvas] %d stencil bits", lStencil);
#endif

		if( !lStencil ) // not available?
			lSettings->mFloor = 0;
	}

	{
		int lTexSize;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &lTexSize);
#ifdef _DEBUG
		qDebug("Success: [Canvas] Maximum texture size is %dx%d",lTexSize,lTexSize);
#endif

		if( !lSettings->mMaxTexSize ||
			lSettings->mMaxTexSize > lTexSize ) // auto OR bigger than available?

			lSettings->mMaxTexSize = lTexSize;
	}

	mSlider = new Slider(10);
}

void Canvas::resizeGL(int pWidth, int pHeight)
{
	if (pHeight==0)
	{
		pHeight=1;
	}

	glViewport(0, 0, pWidth, pHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,static_cast<float>(pWidth)/static_cast<float>(pHeight),0.1f,200.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Canvas::paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glLoadIdentity();

	mSlider->render(this);
}

#define DESIRED_WIDTH	400
#define DESIRED_HEIGHT	300
#define DESIRED_SCALE	100
void Canvas::drawQuad(const Vec3D &pPos, const Vec3D &pRot,
					  const Vec2D &pSize,const Quat &pColor,
					  const bool pInverted)
{
	glPushMatrix();
		glColor4f(pColor.mX,pColor.mY,pColor.mZ,pColor.mW);

		if( pInverted )
			glScalef(1,-1,1);

		glTranslatef(pPos.mX,pPos.mY,pPos.mZ);

		glRotatef(pRot.mX,1.0f,0.0f,0.0f);
		glRotatef(pRot.mY,0.0f,1.0f,0.0f);
		glRotatef(pRot.mZ,0.0f,0.0f,1.0f);

		float lWidth = DESIRED_WIDTH;
		float lHeight = DESIRED_HEIGHT;

		if( pSize.mX >= pSize.mY ) // landscape
		{
			// Aspect Ration Formula (DESIRED_WIDTH * HEIGHT) / WIDTH
			lHeight= ( DESIRED_WIDTH * pSize.mY ) / pSize.mX;
		}
		else // portrait
		{
			// Aspect Ration Formula (DESIRED_HEIGHT * WIDTH) / HEIGHT
			lWidth	= ( DESIRED_HEIGHT * pSize.mX ) / pSize.mY;
		}

		lWidth /= DESIRED_SCALE;
		lHeight/= DESIRED_SCALE;

		float lHWidth = static_cast<float>(lWidth  / 2);
		float lHHeight= static_cast<float>(lHeight / 2);

		glBegin( GL_TRIANGLE_FAN );
			glNormal3f(0.0f,0.0f,1.0f);
			glTexCoord2f(0.0f,0.0f); glVertex2f( -lHWidth, -lHHeight );
			glTexCoord2f(1.0f,0.0f); glVertex2f(  lHWidth, -lHHeight );
			glTexCoord2f(1.0f,1.0f); glVertex2f(  lHWidth,  lHHeight );
			glTexCoord2f(0.0f,1.0f); glVertex2f( -lHWidth,  lHHeight );
		glEnd();

	glPopMatrix();
}

void Canvas::drawText(const QString &pText)
{
	if( pText.isEmpty() )
		return;

	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

		float lPosX = ( (width()  - (pText.length()*14)) / 2 );
		float lPosY = ( (height() - 100) );

		QFont lFont;
		lFont.setBold(true);
		lFont.setItalic(true);
		lFont.setPixelSize(20);

		glColor3f(1.0f,1.0f,1.0f);
		renderText(lPosX,lPosY,pText,lFont);

	glPopAttrib();
	glPopMatrix();
}

void Canvas::mouseMoveEvent(QMouseEvent *pEvent)
{
	QGLWidget::mouseMoveEvent( pEvent ); // HANDLE UN-HANDLED EVENTS
}

void Canvas::mousePressEvent(QMouseEvent *pEvent)
{
	QGLWidget::mousePressEvent(pEvent); // HANDLE UN-HANDLED EVENTS
}

void Canvas::mouseReleaseEvent(QMouseEvent *pEvent)
{
	QGLWidget::mouseReleaseEvent(pEvent); // HANDLE UN-HANDLED EVENTS
}

void Canvas::keyPressEvent(QKeyEvent *pEvent)
{
	switch( pEvent->key() )
	{
		case Qt::Key_Escape:
			QApplication::quit();
			break;

		case Qt::Key_Right:
			mSlider->next();
			break;

		case Qt::Key_Left:
			mSlider->prev();
			break;

		case Qt::Key_Space:
			mSlider->slideShowOnOff();
			break;

		default:
			QGLWidget::keyPressEvent(pEvent); // HANDLE UN-HANDLED KEYS
	}
}

void Canvas::keyReleaseEvent(QKeyEvent *pEvent)
{
	QGLWidget::keyReleaseEvent(pEvent); // HANDLE UN-HANDLED KEYS
}
