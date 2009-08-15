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
#include "settings.h"
#include "defines.h"
#include <QtGui/QApplication>
#include <QtXml>

Settings::Settings() : mConfigFile("")
{
	//! Defaults

	mMonitor	= -1	;	// default monitor
	mTimeout	= 3		;	// seconds
	mWindowed	= false	;	// fulscreen
	mWidth		= 1280	;	// HD wide
	mHeight		= 720	;	// HD wide
	mMSSA		= 4		;	// 4x multi-sampling
	mFloor		= true	;	// reflective floor ON
	mLabels		= true	;	// file names ON
	mMaxTexSize = 0		;	// detect automatically
	mSubDirs	= false ;	// don"t dive into sub directories
	mDontShow	= false	;	// show by default

	// PROTECTED
	mConfigFile	= QApplication::applicationDirPath() + QDir::separator();
	mConfigFile+= QFileInfo(QApplication::applicationFilePath()).baseName()+".xml";
}

Settings::~Settings()
{
}

#define GET_VALUE(node,key) (node.firstChildElement(key).toElement().text())
#define GET_INTVALUE(node,key) (GET_VALUE(node,key).toInt())
bool Settings::load(const QString &pFileName)
{
	//! Config File
	QString lFileName = (!pFileName.isEmpty())?pFileName:mConfigFile;

	//! Check for the existence of the config file
	if( !QFile::exists(lFileName) )
		return false;

#ifdef _DEBUG
	qDebug() << "Success : [Settings] Loading config from " << lFileName << " ...";
#endif

	QFile lFile(lFileName);
	QDomDocument lDoc("settings");

	if( lDoc.setContent(&lFile) ) // LOAD
	{
		// ROOT SETTINGS NODE
		QDomNode lSettings = lDoc.namedItem("settings");

		// LOAD ALL VALUES FROM THE XML
		mMonitor	= GET_INTVALUE(lSettings,"monitor");
		mTimeout	= GET_INTVALUE(lSettings,"timeout");
		mWindowed	= GET_INTVALUE(lSettings,"windowed");
		mWidth		= GET_INTVALUE(lSettings,"width");
		mHeight		= GET_INTVALUE(lSettings,"height");
		mMSSA		= GET_INTVALUE(lSettings,"mssa");
		mFloor		= GET_INTVALUE(lSettings,"floor");
		mLabels		= GET_INTVALUE(lSettings,"labels");
		mMaxTexSize	= GET_INTVALUE(lSettings,"maxtexsize");
		mSubDirs	= GET_INTVALUE(lSettings,"subdirs");
		mDontShow	= GET_INTVALUE(lSettings,"dontshow");

		// GET ALL PATHS
		QDomNodeList lPaths = lSettings.namedItem("paths").childNodes();

		int lNumPaths = lPaths.count();
		for(int i=0;i<lNumPaths;i++)
		{
			QString lPath = lPaths.item(i).toElement().text();

			//! Add it only if valid and exists
			if( QFile::exists(lPath) )
			{
				//! Make sure it has a trailing slash
				if( !lPath.endsWith(QDir::separator()) )
					lPath += QDir::separator();

				mPaths << lPath;
			}
		}

		return true;
	}

	return false;
}
#undef GET_VALUE
#undef GET_INTVALUE

bool Settings::save(const QString &pFileName)
{
	QString lFileName = (!pFileName.isEmpty())?pFileName:mConfigFile;

	QFile lFile( lFileName );

	if( lFile.open(QIODevice::WriteOnly) )
	{
		QString lXml = "<?xml version='1.0' encoding='utf-8'?>";
		lXml += "<settings>";
		lXml += "<monitor>"+QString::number(mMonitor)+"</monitor>";
		lXml += "<timeout>"+QString::number(mTimeout)+"</timeout>";
		lXml += "<windowed>"+QString::number(mWindowed)+"</windowed>";
		lXml += "<width>"+QString::number(mWidth)+"</width>";
		lXml += "<height>"+QString::number(mHeight)+"</height>";
		lXml += "<mssa>"+QString::number(mMSSA)+"</mssa>";
		lXml += "<floor>"+QString::number(mFloor)+"</floor>";
		lXml += "<labels>"+QString::number(mLabels)+"</labels>";
		lXml += "<maxtexsize>"+QString::number(mMaxTexSize)+"</maxtexsize>";
		lXml += "<subdirs>"+QString::number(mSubDirs)+"</subdirs>";
		lXml += "<dontshow>"+QString::number(mDontShow)+"</dontshow>";

		int lNumPaths = mPaths.count();
		if( lNumPaths > 0 )
		{
			lXml += "<paths>";
			for(int i=0;i<lNumPaths;i++)
				lXml += "<path>"+mPaths[i]+"</path>";
			lXml += "</paths>";
		}

		lXml += "</settings>";

		QDomDocument lDoc("settings");

		if( lDoc.setContent(lXml) ) // LOAD CONTENT FROM STRING
		{
#ifdef _DEBUG
			qDebug() << "Success : [Settings] Saving config to " << lFileName << " ...";
#endif

			// WRITE IT OUT
			QTextStream lStream(&lFile);
			lStream << lDoc.toString();

			return true;
		}
	}

	return false;
}
