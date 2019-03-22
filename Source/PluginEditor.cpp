/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FlangerVibratoAudioProcessorEditor::FlangerVibratoAudioProcessorEditor (FlangerVibratoAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), mState(p.getState())
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (320, 260);
	initialiseGUI();
}

FlangerVibratoAudioProcessorEditor::~FlangerVibratoAudioProcessorEditor()
{
	// Empty destructor
}

//==============================================================================
void FlangerVibratoAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
	g.setColour(Colours::white);
	g.drawRoundedRectangle(10.f, 10.f, getWidth() - 20.f, getHeight() / 2.f - 15.f, 10.f, 2.f);
	g.setColour(mLFOColour);
	g.drawRoundedRectangle(10.f, getHeight() / 2.f + 5.f, getWidth() - 20.f, getHeight() / 2.f - 15.f, 10.f, 2.f);
}

void FlangerVibratoAudioProcessorEditor::resized()
{
	// DELAY TIME ========================
	FlexBox delayBox;
	delayBox.alignContent = FlexBox::AlignContent::center;
	delayBox.justifyContent = FlexBox::JustifyContent::center;
	delayBox.flexDirection = FlexBox::Direction::column;
	delayBox.items.addArray(
		{
		FlexItem(mDelayLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mDelaySlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// WETNESS ===========================
	FlexBox wetBox;
	wetBox.alignContent = FlexBox::AlignContent::center;
	wetBox.justifyContent = FlexBox::JustifyContent::center;
	wetBox.flexDirection = FlexBox::Direction::column;
	wetBox.items.addArray(
		{
		FlexItem(mMixLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mMixSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// FEEDBACK ===========================
	FlexBox feedbackBox;
	feedbackBox.alignContent = FlexBox::AlignContent::center;
	feedbackBox.justifyContent = FlexBox::JustifyContent::center;
	feedbackBox.flexDirection = FlexBox::Direction::column;
	feedbackBox.items.addArray(
		{
		FlexItem(mFBLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mFBSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});
	
	// LFO FREQUENCY ======================
	FlexBox lfoFreqBox;
	lfoFreqBox.alignContent = FlexBox::AlignContent::center;
	lfoFreqBox.justifyContent = FlexBox::JustifyContent::center;
	lfoFreqBox.flexDirection = FlexBox::Direction::column;
	lfoFreqBox.items.addArray(
		{
		FlexItem(mLFOFreqLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mLFOFreqSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// LFO FREQUENCY ======================
	FlexBox lfoPhaseBox;
	lfoPhaseBox.alignContent = FlexBox::AlignContent::center;
	lfoPhaseBox.justifyContent = FlexBox::JustifyContent::center;
	lfoPhaseBox.flexDirection = FlexBox::Direction::column;
	lfoPhaseBox.items.addArray(
		{
		FlexItem(mLFOPhaseLabel).withWidth(mSliderSize).withHeight(mLabelHeight),
		FlexItem(mLFOPhaseSlider).withWidth(mSliderSize).withHeight(mSliderSize)
		});

	// LFO WAVEFORM =======================
	FlexBox lfoSelectBox;
	lfoSelectBox.alignContent = FlexBox::AlignContent::spaceAround;
	lfoSelectBox.justifyContent = FlexBox::JustifyContent::spaceAround;
	lfoSelectBox.flexDirection = FlexBox::Direction::column;
	lfoSelectBox.items.addArray(
		{
		FlexItem(mLFOWaveformBox).withWidth(mSliderSize).withHeight(mLabelHeight)
		});

	FlexBox lfoWaveformBox;
	lfoWaveformBox.alignContent = FlexBox::AlignContent::spaceBetween;
	lfoWaveformBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	lfoWaveformBox.flexDirection = FlexBox::Direction::column;
	lfoWaveformBox.items.addArray(
		{
		FlexItem(mLFOWaveformLabel).withWidth(mSliderSize).withHeight(mLabelHeight + 10.f),
		FlexItem(lfoSelectBox).withWidth(mSliderSize).withHeight(mSliderSize - 10.f)
		});

	// First row of parameters in the plugin
	FlexBox firstRowBox;
	firstRowBox.alignContent = FlexBox::AlignContent::spaceBetween;
	firstRowBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	firstRowBox.flexDirection = FlexBox::Direction::row;
	firstRowBox.items.addArray(
		{
			FlexItem(feedbackBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(wetBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(delayBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight)
		});

	// Second row (LFO) parameters of plugin
	FlexBox secondRowBox;
	secondRowBox.alignContent = FlexBox::AlignContent::spaceBetween;
	secondRowBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	secondRowBox.flexDirection = FlexBox::Direction::row;
	secondRowBox.items.addArray(
		{
			FlexItem(lfoWaveformBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(lfoFreqBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(lfoPhaseBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight)
		});

	// MASTER =============================
	FlexBox masterBox;
	masterBox.alignContent = FlexBox::AlignContent::spaceBetween;
	masterBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	masterBox.flexDirection = FlexBox::Direction::column;
	masterBox.items.addArray({
			FlexItem(firstRowBox).withWidth(getWidth() - 2 * mReductionSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(secondRowBox).withWidth(getWidth() - 2 * mReductionSize).withHeight(mSliderSize + mLabelHeight)
		});

	masterBox.performLayout(getLocalBounds().reduced(mReductionSize, mReductionSize).toFloat());
}

void FlangerVibratoAudioProcessorEditor::initialiseGUI()
{
	// MIX =====================================
	//Slider
	mMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mMixSlider.setSize(mSliderSize, mSliderSize);
	mMixSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mMixSliderAttachment.reset(new SliderAttachment(mState, IDs::wetness, mMixSlider));
	addAndMakeVisible(mMixSlider);
	//mMixSlider.setLookAndFeel(&mKnobLookAndFeel);
	mMixSlider.setTextValueSuffix(" %");

	// Label
	mMixLabel.setText("Mix", dontSendNotification);
	mMixLabel.setSize(mSliderSize, mLabelHeight);
	mMixLabel.setFont(mLabelHeight);
	mMixLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mMixLabel);

	// FEEDBACK===================================
	// Slider
	mFBSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mFBSlider.setSize(mSliderSize, mSliderSize);
	mFBSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mFBSliderAttachment.reset(new SliderAttachment(mState, IDs::feedback, mFBSlider));
	addAndMakeVisible(mFBSlider);
	//mFBSlider.setLookAndFeel(&mKnobLookAndFeel);
	mFBSlider.setTextValueSuffix(" %");

	// Label
	mFBLabel.setText("Feedback", dontSendNotification);
	mFBLabel.setSize(mSliderSize, mLabelHeight);
	mFBLabel.setFont(mLabelHeight);
	mFBLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mFBLabel);

	// DELAY TIME ==============================
	// Slider
	mDelaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mDelaySlider.setSize(mSliderSize, mSliderSize);
	mDelaySlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mTimeSliderAttachment.reset(new SliderAttachment(mState, IDs::time, mDelaySlider));
	addAndMakeVisible(mDelaySlider);
	//mDelaySlider.setLookAndFeel(&mKnobLookAndFeel);
	mDelaySlider.setTextValueSuffix(" ms");

	// Label
	mDelayLabel.setText("Delay", dontSendNotification);
	mDelayLabel.setSize(mSliderSize, mLabelHeight);
	mDelayLabel.setFont(mLabelHeight);
	mDelayLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mDelayLabel);

	// LFO FREQUENCY ============================
	// Slider
	mLFOFreqSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mLFOFreqSlider.setSize(mSliderSize, mSliderSize);
	mLFOFreqSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	float skew = std::sqrt(((0.01 * 0.01) * 10) / 0.01);
	mLFOFreqSliderAttachment.reset(new SliderAttachment(mState, IDs::lfoFreq, mLFOFreqSlider));
	addAndMakeVisible(mLFOFreqSlider);
	mLFOFreqSlider.setSkewFactorFromMidPoint(skew);
	//mDelaySlider.setLookAndFeel(&mKnobLookAndFeel);

	// Label
	mLFOFreqLabel.setText("Freq", dontSendNotification);
	mLFOFreqLabel.setSize(mSliderSize, mLabelHeight);
	mLFOFreqLabel.setFont(mLabelHeight);
	mLFOFreqLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOFreqLabel);

	// LFO PHASE ================================
	// Slider
	mLFOPhaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mLFOPhaseSlider.setSize(mSliderSize, mSliderSize);
	mLFOPhaseSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mLFOPhaseSliderAttachment.reset(new SliderAttachment(mState, IDs::lfoPhase, mLFOPhaseSlider));
	addAndMakeVisible(mLFOPhaseSlider);
	//mDelaySlider.setLookAndFeel(&mKnobLookAndFeel);

	// Label
	mLFOPhaseLabel.setText("Phase", dontSendNotification);
	mLFOPhaseLabel.setSize(mSliderSize, mLabelHeight);
	mLFOPhaseLabel.setFont(mLabelHeight);
	mLFOPhaseLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOPhaseLabel);

	// LFO WAVEFORM =============================
	// Combo box
	mLFOWaveformBox.setSize(mSliderSize, mLabelHeight);
	mLFOWaveformBox.addItem("Sine", 1);
	mLFOWaveformBox.addItem("Saw", 2);
	mLFOWaveformBox.addItem("Tri", 3);
	mLFOWaveformBox.addItem("Sqare", 4);
	int waveform = *mState.getRawParameterValue(IDs::lfoWaveform);
	mLFOWaveformBox.setSelectedId(waveform + 1);
	mLFOWaveformAttachment.reset(new ComboBoxAttachment(mState, IDs::lfoWaveform, mLFOWaveformBox));
	addAndMakeVisible(mLFOWaveformBox);

	// Label
	mLFOWaveformLabel.setText("LFO", dontSendNotification);
	mLFOWaveformLabel.setColour(Label::ColourIds::textColourId, mLFOColour);
	mLFOWaveformLabel.setSize(mSliderSize, mLabelHeight);
	mLFOWaveformLabel.setFont(mLabelHeight + 5.f);
	mLFOWaveformLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOWaveformLabel);
}
