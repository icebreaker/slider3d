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
#ifndef TYPES_H
#define TYPES_H

class Vec3D
{
public:
	Vec3D(float pX=0.0f, float pY=0.0f, float pZ=0.0f) : mX(pX),mY(pY),mZ(pZ) {};
	virtual ~Vec3D(){};

	Vec3D operator=(Vec3D pVec)
	{
		mX = pVec.mX;
		mY = pVec.mY;
		mZ = pVec.mZ;

		return *this;
	}

	virtual void set(float pX, float pY, float pZ)
	{
		mX = pX;
		mY = pY;
		mZ = pZ;
	}

	float mX;
	float mY;
	float mZ;
};

class Quat
{
public:
	Quat(float pX=0.0f, float pY=0.0f, float pZ=0.0f, float pW=0.0f) :
		mX(pX),mY(pY),mZ(pZ),mW(pW) {};
	virtual ~Quat(){};

	Quat operator=(Quat pQuat)
	{
		mX = pQuat.mX;
		mY = pQuat.mY;
		mZ = pQuat.mZ;
		mW = pQuat.mW;

		return *this;
	}

	virtual void set(float pX, float pY, float pZ, float pW)
	{
		mX = pX;
		mY = pY;
		mZ = pZ;
		mW = pW;
	}

	float mX;
	float mY;
	float mZ;
	float mW;
};

class Vec2D
{
public:
	Vec2D(float pX=0.0f, float pY=0.0f) : mX(pX),mY(pY) {};
	virtual ~Vec2D(){};

	Vec2D operator=(Vec2D pVec)
	{
		mX = pVec.mX;
		mY = pVec.mY;

		return *this;
	}

	virtual void set(float pX, float pY)
	{
		mX = pX;
		mY = pY;
	}

	float mX;
	float mY;
};

#endif // TYPES_H
