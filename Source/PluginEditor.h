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
#include "LookAndFeel/CustomLookAndFeel.h"
#include "LookAndFeel/VibraFlangeSliderLookAndFeel.h"
#include "LookAndFeel/OnOffButtonLookAndFeel.h"

//==============================================================================
/**
*/
class FlangerVibratoAudioProcessorEditor  : public AudioProcessorEditor, TextButton::Listener
{
public:
    FlangerVibratoAudioProcessorEditor (FlangerVibratoAudioProcessor&);
    ~FlangerVibratoAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
	void paintFrontPanel(Graphics& g);
    void resized() override;

private:
    //==============================================================================
	void initialiseGUI();
	void buttonClicked(Button* b) override;

    //==============================================================================
    FlangerVibratoAudioProcessor& processor;
	AudioProcessorValueTreeState& mState;

	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
	typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
	typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

	// Comopnent look and size parameters
	const int mSliderSize = 80;
	const int mLabelHeight = 24;
	const int mTextBoxHeight = 22;
	const int mReductionSize = 20;
	const int mTitlePanel = 50.f;
	const int mOnOffSize = 18.f;
	const int mVibraFlangeDialWidth = 120;

	Font mLabelFont = Font("Pacifico", mLabelHeight, Font::plain);
	Colour mLFOColour = Colours::lightblue;

	// LookAndFeel
	CustomLookAndFeel mCustomLookAndFeel;
	VibraFlangeSliderLookAndFeel mVibraFlangeLookAndFeel;
	OnOffButtonLookAndFeel mOnOffLookAndFeel;

	// On / off button
	TextButton mOnOffButton;
	std::unique_ptr<ButtonAttachment> mOnOffAttachment;

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

	// LFO waveform
	ComboBox mLFOWaveformBox;
	Label mLFOWaveformLabel;
	std::unique_ptr<ComboBoxAttachment> mLFOWaveformAttachment;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FlangerVibratoAudioProcessorEditor)
};
