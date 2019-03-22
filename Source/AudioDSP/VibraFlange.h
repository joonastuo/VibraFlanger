/*
  ==============================================================================

    VibraFlange.h
    Created: 22 Mar 2019 11:32:52am
    Author:  Joonas

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "../Helper/Identifiers.h"
#include "LFO.h"
#include "DelayLine.h"


class VibraFlange
{
public:
	VibraFlange(AudioProcessorValueTreeState& state);
	~VibraFlange();
	void prepare(dsp::ProcessSpec spec);
	void reset();
	void process(AudioBuffer<float>& buffer);
private:
	// Methods
	float linearInterp(const float& y0, const float& yp1, const float& frac);

	// Variables
	AudioProcessorValueTreeState& mState;

	std::array<DelayLine<float>, 2> delayLines;
	std::array<LFO, 2> mLFOs;
	std::array<SmoothedValue<float>, 2> mSmoothG;
	std::array<SmoothedValue<float>, 2> mSmoothW;
	std::array<SmoothedValue<float>, 2> mSmoothFB;

	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;
	int mDelayBufferLen = 0;
	int mNumChannels = 2;
};