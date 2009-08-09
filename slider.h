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
#ifndef SLIDER_H
#define SLIDER_H

#include "texturemanager.h"
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QTimer>
#include <QtCore/QObject>

namespace GL
{
	class Canvas;
}

typedef GL::TextureArray::const_iterator Photo;

//! ITunes 'like' 3D Photo (viewer) Slider Class
class Slider : public QObject
{
	Q_OBJECT

public:
	//! Constructor
	Slider(const QString &pDir, const int pMax = 10);
	//! Destructor
	virtual ~Slider();

	//! Render the whole scene
	virtual void render(GL::Canvas *pCanvas);

	//! Slide to right
	virtual bool next(void);
	//! Slide to left
	virtual bool prev(void);

public slots:
	void autoNext(void);
	void autoPrev(void);

public:
	void slideShowOnOff(void);

protected:
	//! Typedef for convenience
	typedef QList<Photo> PhotoArray;

	virtual void renderStack(GL::Canvas *pCanvas,
							 const PhotoArray &pStack,
							 const Vec3D &pPos,
							 const Vec3D &pRot,
							 const Vec3D &pInc,
							 const bool pInverted);

	virtual void renderCurrent(GL::Canvas *pCanvas,
							   const Vec3D &pPos,
							   const Vec3D &pRot,
							   const bool pInverted);

	virtual void renderFloor(GL::Canvas *pCanvas,float pOpacity=1.0f);

	virtual void renderScene(GL::Canvas *pCanvas,const bool pInverted=false);

	virtual void test(bool i);

protected:
	//! Left Stack Of Photos
	PhotoArray mLeftStack;
	//! Right Stack of Photos
	PhotoArray mRightStack;
	//!
	Photo mBegin;
	//!
	Photo mEnd;
	//! Currently viewed photo
	Photo mCurrent;
	/*! Maximum number of photos in both stacks
		at any given time.

		This is equal to the number of textures
		in memory at any given time.
	*/
	int mMaximum;
	//! Size of the stacks
	int mHalf;
	//! Working (e.g moving to the next photo) or Idle
	bool mWorking;
	//! Points to the singleton texture manager instance
	GL::TextureManager *mTexMan;
	//! Text to be drawn
	QString mText;
	//! Slideshow timer
	QTimer mNextTimer;
	//! Slideshow timer
	QTimer mPrevTimer;
	//! Slideshow On/Off flag
	bool mSlideShow;
};

#endif // SLIDER_H
