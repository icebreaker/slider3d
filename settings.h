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
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore/QString>
#include <QtCore/QStringList>

//! Settings Class
/*!
	Handles saving/loading of settings
	in an simple & clean XML structure.

	All variables are public, so they can be
	easily accessed in other modules without
	much overhead.
*/
class Settings
{
public:
	//! Constructor
	Settings();
	//! Destructor
	virtual ~Settings();
	//! Load Settings XML
	/*!
		\param pFileName xml file to load the settings from
	*/
	virtual bool load(const QString &pFileName="");
	//! Save Settings XML
	/*!
		\param pFileName xml file to save the settings to
	*/
	virtual bool save(const QString &pFileName="");
	//! Get The Unique Settings Instance
	static Settings &getInstance( void )
	{
		static Settings lStaticSettings;
		return lStaticSettings;
	};

protected:
	QString mConfigFile;

public:
	//! Monitor Number (-1 == default
	int mMonitor;
	//! Slideshow Timeout
	int mTimeout;
	//! Windowed Mode
	bool mWindowed;
	//! Screen Width (in windowed mode)
	int mWidth;
	//! Screen Height (in windowed mode)
	int mHeight;
	//! Multi-Sampling (anti-aliasing, 0 == disabled, automatically disabled if not available)
	int mMSSA;
	//! Render floor or not (automatically disabled if no stencil buffer is available)
	bool mFloor;
	//! Render labels or not (file names)
	bool mLabels;
	//! Maximum Texture Size (0 == auto)
	int mMaxTexSize;
	//! Registered Photo Paths to Scan
	QStringList mPaths;
	//! Whetever to dive into sub directories or not
	bool mSubDirs;
	//! Show / Hide configuration dialog on start-up
	bool mDontShow;
};

#endif // SETTINGS_H
