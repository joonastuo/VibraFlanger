/*
  ==============================================================================

    LFO.cpp
    Created: 21 Mar 2019 12:02:50pm
    Author:  Joonas

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LFO.h"
#define _USE_MATH_DEFINES
#include <math.h>

//==============================================================================
LFO::LFO()
{
	// Triangle wave
	// Functions calculated from coefficients m and b
	// y = mx + b
	// Rising edge 1
	float mt1 = 1.f / 256.f;
	float bt1 = 0.f;

	// Rising edge 2
	float mt2 =  1.f / 256.f;
	float bt2 = -1.f;

	// Falling edge
	float mtf2 = -2.f / 512.f;
	float btf2  = 1.f;


	for (auto i = 0; i < 1024; ++i)
	{
		// Sin
		mSinArray[i] = static_cast<float>(sin((static_cast<double> (i) / 1024.0) * (2.0 * M_PI)));

		// Triangle
		if (i < 256)
			mTriangleArray[i] = mt1 * i + bt1;
		else if (i >= 256 && i < 768)
			mTriangleArray[i] = mtf2 * (i - 256) + btf2;
		else
			mTriangleArray[i] = mt2 * (i - 768) + bt2;

		// Sawtooth
		mSquareArray[i] = 0.f;
		mSawtoothArray[i] = 0.f;

		for (int g = 1; g <= 30; ++g)
		{
			double n = static_cast<double> (g);
			mSawtoothArray[i] += static_cast<float>(pow(-1.0, static_cast<float>(g + 1.0)) * (1.0 / n) * sin(2.0 * M_PI * i * n / 1024.0));
		}

		for (int g = 1; g <= 29; g+=2)
		{
			double n = static_cast<double> (g);
			mSquareArray[i] += static_cast<float>((1.0 / n) * sin(2.0 * M_PI * i * n / 1024.0));
		}
		if (i == 0)
		{
			mMaxSqr = mSquareArray[i];
			mMaxSaw = mSawtoothArray[i];
		}
		else
		{
			if (mSquareArray[i] > mMaxSqr)
				mMaxSqr = mSquareArray[i];

			if (mSawtoothArray[i] > mMaxSaw)
				mMaxSaw = mSawtoothArray[i];
		}

	}
	for (int i = 0; i < 1024; ++i)
	{
		mSquareArray[i] /= mMaxSqr;
		mSawtoothArray[i] /= mMaxSaw;
	}
}

//==============================================================================
LFO::~LFO()
{
	// Empty destructor
}

//==============================================================================
void LFO::prepare(dsp::ProcessSpec spec)
{
	mSampleRate = static_cast<float>(spec.sampleRate);
	mSamplesPerBlock = static_cast<float>(spec.maximumBlockSize);
}

//==============================================================================
float LFO::getValue()
{
	float readIndex = mReadIndex + 1024.f * (mPhase / 360.f);
	if (readIndex > 1024)
		readIndex = readIndex - 1024.f;

	float LFOVal = 0.f;
	int readIndexInt = static_cast<int>(readIndex);
	float frac = readIndex - readIndexInt;
	int readIndexNext = readIndexInt + 1 > 1023 ? 0 : readIndexInt + 1;

	switch (mWaveform)
	{
	case Waveforms::sine:
		LFOVal = linearInterp(mSinArray[readIndexInt], mSinArray[readIndexNext], frac);
		break;
	case Waveforms::saw:
		LFOVal = linearInterp(mSawtoothArray[readIndexInt], mSawtoothArray[readIndexNext], frac);
		break;
	case Waveforms::tri:
		LFOVal = linearInterp(mTriangleArray[readIndexInt], mTriangleArray[readIndexNext], frac);
		break;
	case Waveforms::square:
		LFOVal = linearInterp(mSquareArray[readIndexInt], mSquareArray[readIndexNext], frac);
		break;
	default:
		LFOVal = linearInterp(mSinArray[readIndexInt], mSinArray[readIndexNext], frac);
		break;
	}

	if (mUnipolar)
	{
		LFOVal /= 2;
		LFOVal += 0.5;

		if (LFOVal < 0 || LFOVal > 1)
			return 0.f;
	}

	return LFOVal;
}

//==============================================================================
float LFO::getValueAndAdvance()
{
	float value = getValue();
	advanceSamples(1);
	return value;
}

//==============================================================================
void LFO::setFreq(const float & freq)
{
	mInc = 1024.f * (freq / mSampleRate);
}

//==============================================================================
void LFO::setUnipolar(const bool & isUnipolar)
{
	mUnipolar = isUnipolar;
}

//==============================================================================
void LFO::setWaveform(const int & waveform)
{
	mWaveform = waveform;
}

//==============================================================================
void LFO::advanceSamples(const int & numSamples)
{
	mReadIndex += (mInc * numSamples);
	if (mReadIndex > 1024)
		mReadIndex = mReadIndex - 1024;
}

//==============================================================================
void LFO::advanceBlock()
{
	mReadIndex += (mInc * mSamplesPerBlock);
	if (mReadIndex > 1024)
		mReadIndex = mReadIndex - 1024;
}

//==============================================================================
float LFO::linearInterp(const float & y0, const float & yp1, const float & frac)
{
	return y0 * (1 - frac) + yp1  * frac;
}

//==============================================================================
void LFO::setPhase(const float & phase)
{
	mPhase = phase;
}

