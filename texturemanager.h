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
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QHash>
#include <QtCore/QMap>

#include "texture.h"

namespace GL {

//! Array Definition
/*!
	QMap is preferred over QHash because it is
	sorted by key, in this case the actual
	filenames, this is important because the
	order must match the order from the actual
	directory listing ...

	If the order is not important, it can be
	switched to QHash without too much hassle.
*/
typedef QMap<QString,Texture *> TextureArray;

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();

	virtual void setBaseDir(const QString &pDir, bool pScan=false);
	virtual QString &getBaseDir(void);

	virtual int getCount( void ) const;

	virtual TextureArray::const_iterator getBegin(void) const;
	virtual TextureArray::const_iterator getEnd(void) const;

	virtual TextureArray::const_iterator find( const QString &pFileName ) const;
	virtual Texture *findTexture( const QString &pFileName ) const;

	virtual Texture *getTexture(const TextureArray::const_iterator &pTexture) const;
	//virtual Texture *getDefaultTexture( void ) const;

	virtual bool remove( const QString &pFileName );
	virtual void removeAll( void );

	static TextureManager &getInstance( void )
	{
		static TextureManager staticTextureManager;
		return staticTextureManager;
	}

protected:
	Texture *mEmptyTexture;
	TextureArray mTextures;

	QString mBaseDir;
	int mNumTextures;
};

/*GL*/ }

#endif // TEXTUREMANAGER_H
