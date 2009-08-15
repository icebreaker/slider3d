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
#include "slider.h"

#include <QtCore/QDebug>
#include "canvas.h"
#include "types.h"
#include "defines.h"

using namespace GL;

Slider::Slider(const int pMax) :	mBegin(0),
									mEnd(0),
									mCurrent(0),
									mMaximum(pMax),
									mHalf(0),
									mWorking(false),
									mTexMan(0),
									mText(""),
									mSlideShow(false),
									mSettings(0)
{
	// Get and store the unique instance
	mTexMan = &TextureManager::getInstance();
	mSettings = &Settings::getInstance();

	// scan all directories --> MOVE THIS INTO A SEPARATE WORKER THREAD
	int lNumPaths = mSettings->mPaths.count();
	for(int i=0;i<lNumPaths;i++)
		mTexMan->scanDir(mSettings->mPaths[i],mSettings->mSubDirs);

	// compute half
	mHalf = static_cast<int>(mMaximum/2);

	// no photos
	if( !mTexMan->getCount() )
		return;

	int lCount = mTexMan->getCount();
	if( lCount < mHalf )
		mHalf = lCount;

	mBegin = mTexMan->getBegin();
	mEnd = mTexMan->getEnd();

	mCurrent = (mEnd - 1);

	// fill in the left stack
	for(int i=0;i<mHalf;i++)
	{
		mLeftStack.push_back(mCurrent);
		--mCurrent;
	}

	mCurrent = mEnd;

	mText = "";

#ifdef _DEBUG
	qDebug() << "Success: [Slider] Created ...";
#endif

	connect(&mNextTimer, SIGNAL(timeout()), this, SLOT(autoNext()));
	connect(&mPrevTimer, SIGNAL(timeout()), this, SLOT(autoPrev()));
}

Slider::~Slider()
{
#ifdef _DEBUG
	qDebug() << "Success: [Slider] Destroyed ...";
#endif

	mLeftStack.clear();
	mRightStack.clear();

	mTexMan->removeAll();
}

void Slider::test(bool i)
{
	glPushMatrix();
	if( i )
		glScalef(1.0f,-1.0f,1.0f);

	glTranslatef(0.0f,2.5f,-6.0f);
	static float r = 0.0f;
	glRotatef(r,1.0f,1.0f,1.0f);

	glBindTexture(GL_TEXTURE_2D,0);
	glBegin(GL_QUADS);							// Start Drawing Quads

	glNormal3f( 0.0f, 0.0f, 1.0f);					// Normal Pointing Towards Viewer
		glColor3f(1.0f,0.0f,0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 1 (Front)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 2 (Front)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Front)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 4 (Front)
		// Back Face
		glNormal3f( 0.0f, 0.0f,-1.0f);					// Normal Pointing Away From Viewer
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Back)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 2 (Back)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 3 (Back)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 4 (Back)
		// Top Face
		glNormal3f( 0.0f, 1.0f, 0.0f);					// Normal Pointing Up
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 1 (Top)
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 2 (Top)
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Top)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 4 (Top)
		// Bottom Face
		glNormal3f( 0.0f,-1.0f, 0.0f);					// Normal Pointing Down
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Bottom)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 2 (Bottom)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 3 (Bottom)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 4 (Bottom)
		// Right face
		glNormal3f( 1.0f, 0.0f, 0.0f);					// Normal Pointing Right
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Point 1 (Right)
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Point 2 (Right)
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Point 3 (Right)
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Point 4 (Right)
		// Left Face
		glNormal3f(-1.0f, 0.0f, 0.0f);					// Normal Pointing Left
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Point 1 (Left)
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Point 2 (Left)
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Point 3 (Left)
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Point 4 (Left)
	glEnd();

	r += 0.3f;

	glPopMatrix();
}

void Slider::render(Canvas *pCanvas)
{
	if( mWorking )
		return;

	if( mSettings->mMSSA )
		glEnable(GL_MULTISAMPLE); // make sure it's ENABLED

	gluLookAt(0.0f,  2.0f, 0.8f,
			  0.0f,  2.0f,-2.0f,
			  0.0f,  1.0f, 0.0f);

	renderScene(pCanvas);
	//test(false);

	if( mSettings->mFloor )
	{
		glEnable(GL_STENCIL_TEST);
		glColorMask(0, 0, 0, 0);
		glDisable(GL_DEPTH_TEST);
		glStencilFunc(GL_ALWAYS, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		renderFloor(pCanvas);

		glColorMask(1, 1, 1, 1);
		glEnable(GL_DEPTH_TEST);
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		renderScene(pCanvas,true);
		//test(true);
		glDisable(GL_STENCIL_TEST);

		glEnable(GL_BLEND);
		renderFloor(pCanvas,0.7f);
		glDisable(GL_BLEND);
	}

	pCanvas->drawText(mText);
}

bool Slider::next(void)
{
	mWorking = true;

	if( mCurrent != mEnd )
	{
		mRightStack.push_front(mCurrent);
		mCurrent = mEnd;
		mText = "";

		if( mRightStack.size() > mHalf )
		{
			Texture *lTexture = mTexMan->getTexture(mRightStack.back());
			lTexture->free(); // free the GL texture

			mRightStack.pop_back();
		}
	}

	if( !mLeftStack.empty() )
	{
		mCurrent = mLeftStack.front();
		Texture *lTexture = mTexMan->getTexture(mCurrent);

		if( mSettings->mLabels )
			mText = lTexture->getBaseName();

		Photo lNext = mLeftStack.back();
		if( --lNext != mEnd )
			mLeftStack.push_back(lNext);

		mLeftStack.pop_front();
	}

	mWorking = false;

	return (mCurrent != mEnd);
}

bool Slider::prev(void)
{
	mWorking = true;

	if( mCurrent != mEnd )
	{
		mLeftStack.push_front(mCurrent);
		mCurrent = mEnd;
		mText = "";

		if( mLeftStack.size() > mHalf )
		{
			Texture *lTexture = mTexMan->getTexture(mLeftStack.back());
			lTexture->free(); // free the GL texture

			mLeftStack.pop_back();
		}
	}

	if( !mRightStack.empty() )
	{
		mCurrent = mRightStack.front();

		Texture *lTexture = mTexMan->getTexture(mCurrent);

		if( mSettings->mLabels )
			mText =	lTexture->getBaseName();

		Photo lPrev = mRightStack.back();
		if( ++lPrev != mEnd )
			mRightStack.push_back(lPrev);

		mRightStack.pop_front();
	}

	mWorking = false;

	return (mCurrent!=mEnd);
}

void Slider::autoNext(void)
{
	if( !next() )
	{
		mNextTimer.stop();
		mPrevTimer.start(mSettings->mTimeout*1000);
	}
}

void Slider::autoPrev(void)
{
	if( !prev() )
	{
		mPrevTimer.stop();
		mNextTimer.start(mSettings->mTimeout*1000);
	}
}

void Slider::slideShowOnOff(void)
{
	mSlideShow = !mSlideShow;

	if( mSlideShow )
	{
		mNextTimer.start(mSettings->mTimeout*1000);
	}
	else
	{
		mNextTimer.stop();
		mPrevTimer.stop();
	}

#ifdef _DEBUG
	qDebug() << "SlideShow: " << ((mSlideShow)?"on":"off");
	qDebug() << "SlideShow Timeout:" << mSettings->mTimeout << " seconds ...";
#endif
}

void Slider::renderStack(Canvas *pCanvas,
						 const PhotoArray &pStack,
						 const Vec3D &pPos,
						 const Vec3D &pRot,
						 const Vec3D &pInc,
						 const bool pInverted)
{
	PhotoArray::const_iterator lIt = pStack.begin();
	PhotoArray::const_iterator lEnd = pStack.end();

	Vec3D lPos = pPos;

	for(; lIt!=lEnd; ++lIt)
	{
		Texture *lTexture = mTexMan->getTexture((*lIt));
		lTexture->enable();

		pCanvas->drawQuad(lPos,pRot,lTexture->getSize(),
						  Quat(1.0f,1.0f,1.0f,1.0f),pInverted);

		lPos.mX += pInc.mX;
		lPos.mZ += pInc.mZ;
	}
}

void Slider::renderCurrent(Canvas *pCanvas,
						   const Vec3D &pPos,
						   const Vec3D &pRot,
						   const bool pInverted)
{
	//! Current Photo?
	if( mCurrent != mEnd )
	{
		Texture *lTexture  = mTexMan->getTexture(mCurrent);
		lTexture->enable();

		pCanvas->drawQuad(pPos,pRot,lTexture->getSize(),
						  Quat(1.0f,1.0f,1.0f),pInverted);
	}
}

void Slider::renderFloor(GL::Canvas *pCanvas, float pOpacity)
{
	Q_UNUSED(pCanvas);

	glBindTexture(GL_TEXTURE_2D,0);
		glPushMatrix();

		glColor4f(0.3f,0.3f,0.3f,pOpacity);

		glTranslatef(0.0f,-0.5f,-5.0f);

		glRotatef(90.0f,1.0f,0.0f,0.0f);
		//glRotatef(pRot.mY,0.0f,1.0f,0.0f);
		//glRotatef(pRot.mZ,0.0f,0.0f,1.0f);

		float lHWidth = static_cast<float>(25 / 2);
		float lHHeight= static_cast<float>(25 / 2);

		glBegin( GL_TRIANGLE_FAN );
			glNormal3f(0.0f,1.0f,0.0f);
			glTexCoord2f(0.0f,0.0f); glVertex2f( -lHWidth, -lHHeight );
			glTexCoord2f(1.0f,0.0f); glVertex2f(  lHWidth, -lHHeight );
			glTexCoord2f(1.0f,1.0f); glVertex2f(  lHWidth,  lHHeight );
			glTexCoord2f(0.0f,1.0f); glVertex2f( -lHWidth,  lHHeight );
		glEnd();

	glPopMatrix();
}

void Slider::renderScene(Canvas *pCanvas, const bool pInverted)
{
	Vec3D lPos(-2.5f, 2.0f,-8.5f);
	Vec3D lRot( 0.0f,30.0f, 0.0f);

	renderStack(pCanvas,mLeftStack,lPos,lRot,Vec3D(-2.5f,0.0f,-2.5f),pInverted);

	lPos = Vec3D(0.0f,2.0f,-6.0f);
	lRot.mY = 0.0f;

	renderCurrent(pCanvas,lPos,lRot,pInverted);

	lRot.mY = -30.0f;
	lPos.mX += 2.5f;
	lPos.mZ -= 2.5f;

	renderStack(pCanvas,mRightStack,lPos,lRot,Vec3D(2.5f,0.0f,-2.5f),pInverted);
}
