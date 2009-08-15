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
#include "texture.h"

#include <QtOpenGL>
#include <QtGui/QImage>
#include <QtCore/QDebug>

#include "settings.h"
#include "defines.h"

using namespace GL;

Texture::Texture(const QString &pFileName) :	mRefCount(1),
												mTextureId(0),
												mBaseName(""),
												mFileName("")
{
	if( !pFileName.isEmpty() )
		mFileName = pFileName;
}

Texture::~Texture()
{
	free();
}

QString &Texture::getBaseName(void)
{
	return mBaseName;
}

QString &Texture::getFileName(void)
{
	return mFileName;
}

bool Texture::load( const QString &pFileName, bool pClamp )
{
#ifdef _DEBUG
	qDebug() << "Loading: [Texture] " << pFileName;
#endif

	if( pFileName.isEmpty() )
		return false;

	QImage lImage, lImageTemp;

	if( !lImage.load( pFileName ) )
		return false;

	// get the filename
	mBaseName = QFileInfo(pFileName).fileName();
	mFileName = pFileName;

	// store these for later
	mWidth = lImage.width();
	mHeight = lImage.height();
	mSize = Vec2D(mWidth,mHeight);

	int lMaxTexSize = Settings::getInstance().mMaxTexSize;
	if( lMaxTexSize >= 1024 )
	{
		if( mWidth >= 1024 || mHeight >= 1024 )
		{
#ifdef _DEBUG
			qDebug() << "Resizing to 1024x1024 ...";
#endif
			lImage.scaled(1024,1024);
		}
		else
		{
#ifdef _DEBUG
			qDebug() << "Resizing to 512x512 ...";
#endif
			lImage.scaled(512,512);
		}
	}
	else
	{
#ifdef _DEBUG
		qDebug() << "Resizing to " << lMaxTexSize << "," << lMaxTexSize << " ...";
#endif
		lImage.scaled(lMaxTexSize,lMaxTexSize);
	}

	lImageTemp = QGLWidget::convertToGLFormat( lImage );

	glGenTextures(1, &mTextureId);

	enable();

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	//glTexParameterf(GL_TEXTURE_2D, 0x84FE, 8);

	if( pClamp )
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, 4, mWidth, mHeight, 0, GL_RGBA,
				 GL_UNSIGNED_BYTE, lImageTemp.bits() );

	disable();

	return true;
}

bool Texture::load( bool pClamp )
{
	return load(mFileName,pClamp);
}

bool Texture::free( void )
{
	if(mTextureId)
	{
		glDeleteTextures(1,&mTextureId);
		mTextureId = 0;

#ifdef _DEBUG
		qDebug() << "Freeing: [Texture] " << mFileName;
#endif

		return true;
	}

	return false;
}

void Texture::enable( void )
{
	glBindTexture(GL_TEXTURE_2D,mTextureId);
}

void Texture::disable( void )
{
	glBindTexture(GL_TEXTURE_2D,0);
}

Texture *Texture::grab( void )
{
	mRefCount++;
	return this;
}

bool Texture::drop( void )
{
	if( --mRefCount == 0 )
	{

		delete this;
		return true;
	}

	return false;
}

bool Texture::isPortrait( void ) const
{
	return (mHeight>mWidth);
}

bool Texture::isLandscape( void ) const
{
	return (mHeight<=mWidth);
}

int Texture::getWidth( void ) const
{
	return mWidth;
}

int Texture::getHeight( void ) const
{
	return mHeight;
}

Vec2D Texture::getSize( void ) const
{
	return mSize;
}

unsigned int Texture::getTextureId( void ) const
{
	return mTextureId;
}

int Texture::_getRefCount( void ) const
{
	return mRefCount;
}
