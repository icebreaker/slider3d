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
#include "texturemanager.h"
#include "texture.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include "defines.h"

using namespace GL;

TextureManager::TextureManager() :	mEmptyTexture(new Texture),
									mBaseDir(""),
									mNumTextures(0)
{
}

TextureManager::~TextureManager()
{
	if( !mEmptyTexture->drop() )
	{
#ifdef _DEBUG
		qDebug() << "Warning: [Texture] EmptyTexture was not released properly";
#endif
	}
	else
	{
#ifdef _DEBUG
		qDebug() << "Success: [Texture] EmptyTexture dropped";
#endif
	}
	mEmptyTexture = 0;
}

void TextureManager::scanDir(const QString &pDir, const bool pRecursive)
{
	Q_UNUSED(pRecursive);

	QString lPath = pDir;

	// append trailing slash ...
	if( !lPath.endsWith(QDir::separator()) )
		lPath += QDir::separator();

	QStringList lFilters;
	lFilters.append("*.png");
	lFilters.append("*.jpg");
	lFilters.append("*.jpeg");

	QDir lDir(lPath);
	lDir.setNameFilters(lFilters);
	lDir.setSorting(QDir::Name);

	QStringList lFiles = lDir.entryList();

	QStringList::const_iterator lIt		= lFiles.begin();
	QStringList::const_iterator lEnd	= lFiles.end();

	// insert into HASH map
	for( ; lIt != lEnd; ++lIt )
	{
		const QString lFileName = lPath + (*lIt);
		mTextures.insert(lFileName,new Texture(lFileName));
	}

	//
	mNumTextures += lFiles.size();
}

int TextureManager::getCount( void ) const
{
	return mNumTextures;
}

TextureArray::const_iterator TextureManager::getBegin(void) const
{
	return mTextures.begin();
}

TextureArray::const_iterator TextureManager::getEnd(void) const
{
	return mTextures.end();
}

TextureArray::const_iterator TextureManager::find( const QString &pFileName ) const
{
	const QString lFileName = mBaseDir + pFileName;
	return mTextures.find(lFileName);
}

Texture *TextureManager::findTexture( const QString &pFileName ) const
{
	// try to locate it inside our hash map
	TextureArray::const_iterator lIt = find(pFileName);
	if( lIt != mTextures.end() )
		return getTexture(lIt);

	// return empty texture
	return mEmptyTexture;
}

Texture *TextureManager::getTexture(const TextureArray::const_iterator &pTexture) const
{
	//
	Texture *lTexture = pTexture.value();

	// pre-loaded?
	if( lTexture->getTextureId() )
		return lTexture;

	// load
	if( lTexture->load() )
		return lTexture;

	return mEmptyTexture;
}

bool TextureManager::remove( const QString &pFileName )
{
	if( mTextures.empty() )
		return false;

	const QString lFileName = mBaseDir + pFileName;

	TextureArray::iterator lIt = mTextures.find(lFileName);
	if( lIt == mTextures.end() )
		return false;

	Texture *lTexture = lIt.value();

#ifdef _DEBUG
	if( !lTexture->drop() ) // WARNING
		qDebug() << "Warning: [Texture] " << lIt.key() << " is begin used.";
	else
		qDebug() << "Success: [Texture] " << lIt.key() << " dropped";
#else
	lTexture->drop();
#endif

	// remove it anyway
	mTextures.erase(lIt);

	return true;
}

void TextureManager::removeAll( void )
{
	if( mTextures.empty() )
		return;

	TextureArray::iterator lIt	= mTextures.begin();
	TextureArray::iterator lEnd	= mTextures.end();

	for( ; lIt!=lEnd; ++lIt )
	{
		// TODO: just spit warning, but we should
		// really clean it up ...
#ifdef _DEBUG
		if( !lIt.value()->drop() )
		{
			qDebug() << "Warning: [Texture] " << lIt.key() << " was not released properly";
		}
		else
		{
			qDebug() << "Success: [Texture] " << lIt.key() << " dropped";
		}
#else
		lIt.value()->drop();
#endif
	}

	mTextures.clear();
}
