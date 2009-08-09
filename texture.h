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
#ifndef TEXTURE_H
#define TEXTURE_H

#include <QtCore/QString>

#include "types.h"

namespace GL {

class TextureManager;

class Texture
{
public:
	Texture( const QString &pFileName = "" );
	virtual ~Texture();

	virtual QString &getBaseName( void );
	virtual QString &getFileName( void );

	virtual bool load( const QString &pFileName, bool pClamp = true );
	virtual bool load( bool pClamp = true );
	virtual bool free( void );

	virtual void enable( void );
	virtual void disable( void );

	virtual Texture *grab( void );
	virtual bool drop( void );

	virtual int getWidth( void ) const;
	virtual int getHeight( void ) const;
	virtual Vec2D getSize( void ) const;

	virtual bool isPortrait( void ) const;
	virtual bool isLandscape( void ) const;

	virtual unsigned int getTextureId( void ) const;

protected:
	friend class TextureManager;
	virtual int _getRefCount( void ) const;

protected:
	int mRefCount;

	int mWidth;
	int mHeight;
	Vec2D mSize;

	unsigned int mTextureId;

	QString mBaseName;
	QString mFileName;
};

/* GL */ }

#endif // TEXTURE_H
