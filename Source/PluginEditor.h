/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "Helper/Identifiers.h"

//==============================================================================
/**
*/
class FlangerVibratoAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    FlangerVibratoAudioProcessorEditor (FlangerVibratoAudioProcessor&);
    ~FlangerVibratoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
	void initialiseGUI();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FlangerVibratoAudioProcessor& processor;
	AudioProcessorValueTreeState& mState;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

	// Slider parameters
	const int mSliderSize = 80;
	const int mLabelHeight = 20;
	const int mTextBoxHeight = 12;
	const int mReductionSize = 20;

	// Mix (wetness)
	Slider mMixSlider;
	Label  mMixLabel;
	std::unique_ptr<SliderAttachment> mMixSliderAttachment;

	// Feedback (gain)
	Slider mFBSlider;
	Label  mFBLabel;
	std::unique_ptr<SliderAttachment> mFBSliderAttachment;

	// Delay time
	Slider mDelaySlider;
	Label  mDelayLabel;
	std::unique_ptr<SliderAttachment> mTimeSliderAttachment;
	
	// LFO freq
	Slider mLFOFreqSlider;
	Label mLFOFreqLabel;
	std::unique_ptr<SliderAttachment> mLFOFreqSliderAttachment;

	// LFO phase
	Slider mLFOPhaseSlider;
	Label mLFOPhaseLabel;
	std::unique_ptr<SliderAttachment> mLFOPhaseSliderAttachment;

	ComboBox mLFOWaveformBox;
	Label mLFOWaveformLabel;
	Colour mLFOColour = Colours::lightblue;
	std::unique_ptr<ComboBoxAttachment> mLFOWaveformAttachment;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerVibratoAudioProcessorEditor)
};
