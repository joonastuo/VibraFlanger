/*
  ==============================================================================

    VibraFlange.cpp
    Created: 22 Mar 2019 11:32:52am
    Author:  Joonas

  ==============================================================================
*/

#include "VibraFlange.h"


//==============================================================================
VibraFlange::VibraFlange(AudioProcessorValueTreeState& state)
	: mState(state)
{
	// Empty constructor
}

//==============================================================================
VibraFlange::~VibraFlange()
{
	// Emtyp destructor
}

//==============================================================================
void VibraFlange::prepare(dsp::ProcessSpec spec)
{
	// Set specs to class variables
	mSampleRate      = spec.sampleRate;
	mSamplesPerBlock = spec.maximumBlockSize;
	mNumChannels     = spec.numChannels;

	// Prepare delay lines
	mDelayBufferLen  = 2 * (mSampleRate + mSamplesPerBlock);

	for (auto& dline : delayLines)
	{
		dline.resize(mDelayBufferLen);
		dline.clear();
	}

	// Set LFO values
	float lfoFreq   = getLfoFreq();
	int lfoWaveform = getLfoWaveform();
	float phase     = getLfoPhase();
	// Set phase shift to left channel
	mLFOs[0].setPhase(phase);

	for (auto& lfo : mLFOs)
	{
		lfo.prepare(spec);
		lfo.setWaveform(lfoWaveform);
		lfo.setUnipolar(true);
		lfo.setFreq(lfoFreq);
	}

	// Prepare smoothed values
	float FB = getFeedback();
	float W  = getWetness();
	float G  = 1 - W;

	for (int dline = 0; dline < 2; ++dline)
	{
		mSmoothFB[dline].reset(mSamplesPerBlock);
		mSmoothW[dline] .reset(mSamplesPerBlock);
		mSmoothG[dline] .reset(mSamplesPerBlock);

		mSmoothFB[dline].setCurrentAndTargetValue(FB);
		mSmoothW[dline] .setCurrentAndTargetValue(W);
		mSmoothG[dline] .setCurrentAndTargetValue(G);
	}
}

//==============================================================================
void VibraFlange::reset()
{
	// Empty reset function
}

//==============================================================================
void VibraFlange::process(AudioBuffer<float>& buffer)
{
	// Update parameters
	update();

	// Smooth transition between on and off states ===============
	bool effectOn = getEffectOn();

	if (!effectOn)
	{
		if (transitionToOnOff)
		{
			// Set target values
			for (auto dline = 0; dline < 2; ++dline)
			{
				mSmoothG[dline] .setTargetValue(1.f);
				mSmoothW[dline] .setTargetValue(0.f);
				mSmoothFB[dline].setTargetValue(0.f);
			}
			transitionToOnOff = false;
		}
		else
		{
			// Bypass effect
			for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
			{
				const float* input = buffer.getReadPointer(channel);
				buffer.copyFrom(channel, 0, input, buffer.getNumSamples());
			}
			return;
		}
	}
	else
	{
		transitionToOnOff = true;
	}

	const float* leftInput  = buffer.getReadPointer(0);
	const float* rightInput = buffer.getReadPointer(0);

	if (buffer.getNumChannels() == 2)
		rightInput = buffer.getReadPointer(1);
	else if (buffer.getNumChannels() > 2)
		return;

	float* leftOutput  = buffer.getWritePointer(0);
	float* rightOutput = buffer.getWritePointer(1);

	modDelay(leftInput,  leftOutput,  0);
	modDelay(rightInput, rightOutput, 1);
}

//==============================================================================
void VibraFlange::modDelay(const float * input, float * output, const int& dline)
{
	// Get channel LFO
	auto& lfo = mLFOs[dline];

	// Gains
	float FB = 0.f;
	float W  = 0.f;
	float G  = 0.f;

	// Iterate trough samples in a channel
	for (auto sample = 0; sample < mSamplesPerBlock; ++sample)
	{
		// Get smoothed gain values
		FB = mSmoothFB[dline].getNextValue();
		W  = mSmoothW[dline] .getNextValue();
		G  = mSmoothG[dline] .getNextValue();

		// Get delay amount
		float delayTime = mDelayTimeDepth * lfo.getValue();
		lfo.advanceSamples(1);
		float delayInSamplesFrac = mSampleRate * (delayTime / 1000.f);
		int delayInSamplesInt = static_cast<int> (delayInSamplesFrac);
		float delayFrac = delayInSamplesFrac - delayInSamplesInt;

		// Get delayed sample
		float delayedSample = 0.f;
		// Fractal delay with liner interpolation if neede
		if (delayFrac != 0)
		{
			float y0  = delayLines[dline].get(delayInSamplesInt);
			float ym1 = delayLines[dline].get(delayInSamplesInt + 1);
			delayedSample = linearInterp(y0, ym1, delayFrac);
		}
		// If no frac
		else
		{
			delayedSample = delayLines[dline].get(delayInSamplesInt);
		}

		auto inputSample = input[sample];

		// Add input and feedback to delayLine
		delayLines[dline].push(inputSample + delayedSample * FB);

		// Mix dry and wet input
		output[sample] = inputSample * G + delayedSample * W;
	}
}

//==============================================================================
void VibraFlange::update()
{
	float FB	  = getFeedback();
	float W		  = getWetness();
	float G		  = 1 - W;
	float time    = getTime();
	float lfoFreq = getLfoFreq();
	float phase   = getLfoPhase();
	int waveform  = getLfoWaveform();

	mDelayTimeDepth = time;
	mLFOs[0].setPhase(phase);
	// Set gain values ==============================
	for (int dline = 0; dline < 2; ++dline)
	{
		mSmoothFB[dline].setValue(FB);
		mSmoothW[dline] .setValue(W);
		mSmoothG[dline] .setValue(G);
		mLFOs[dline].setFreq(lfoFreq);
		mLFOs[dline].setWaveform(waveform);
	}
}

//==============================================================================
// Linear interpolation used with fractal delays
float VibraFlange::linearInterp(const float& y0, const float& yp1, const float& frac)
{
	return yp1 * frac + y0 * (1 - frac);
}

//==============================================================================
float VibraFlange::getFeedback()
{
	float feedbackPercentage = *mState.getRawParameterValue(IDs::feedback);
	return feedbackPercentage / 100.f;
}

//==============================================================================
float VibraFlange::getWetness()
{
	float wetnessPercentage = *mState.getRawParameterValue(IDs::wetness);
	return wetnessPercentage / 100.f;
}

//==============================================================================
float VibraFlange::getTime()
{
	return *mState.getRawParameterValue(IDs::time);
}

//==============================================================================
float VibraFlange::getLfoFreq()
{
	float lfoFreqPercentage = *mState.getRawParameterValue(IDs::lfoFreq);
	return 0.01f * exp(lfoFreqPercentage * 0.06908);
}

//==============================================================================
float VibraFlange::getLfoPhase()
{
	return *mState.getRawParameterValue(IDs::lfoPhase);
}

//==============================================================================
int VibraFlange::getLfoWaveform()
{
	return *mState.getRawParameterValue(IDs::lfoWaveform);
}

//==============================================================================
bool VibraFlange::getEffectOn()
{
	return *mState.getRawParameterValue(IDs::onOff);
}
