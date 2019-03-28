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
	void modDelay(const float* input, float* output, const int& channel);
	void update();
	float linearInterp(const float& y0, const float& yp1, const float& frac);
	float getFeedback();
	float getWetness();
	float getTime();
	float getLfoFreq();
	float getLfoPhase();
	int   getLfoWaveform();
	bool  getEffectOn();

	// Variables
	AudioProcessorValueTreeState& mState;
	// Initialise values for two delay lines
	std::array<DelayLine<float>, 2> delayLines;
	std::array<LFO, 2> mLFOs;
	std::array<SmoothedValue<float>, 2> mSmoothG;
	std::array<SmoothedValue<float>, 2> mSmoothW;
	std::array<SmoothedValue<float>, 2> mSmoothFB;

	double mSampleRate = 44100.f;
	int mSamplesPerBlock = 512;
	int mDelayBufferLen = 0;
	int mNumChannels = 2;
	float mDelayTimeDepth = 0.f;
	bool transitionToOnOff = true;
	bool transitionToOffOn = false;
};