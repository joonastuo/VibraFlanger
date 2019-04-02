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
    setSize (320, 320);
	Colour backgroundColour = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
	mLFOColour = backgroundColour.darker(.8f);
	initialiseGUI();
}

//==============================================================================
FlangerVibratoAudioProcessorEditor::~FlangerVibratoAudioProcessorEditor()
{
	 mOnOffButton.setLookAndFeel(nullptr);
}

//==============================================================================
void FlangerVibratoAudioProcessorEditor::paint (Graphics& g)
{
	// Fill background
	Colour backgroundColour = getLookAndFeel().findColour(ResizableWindow::backgroundColourId);
    g.fillAll (backgroundColour);

	auto area = getLocalBounds();
	auto titleArea = area.removeFromBottom(mTitleHeight);
	// Set on / off button bounds
	mOnOffButton.setBounds(getWidth() / 2.f - 60.f, titleArea.getCentreY() - 30.f, 120.f, 40.f);
}

//==============================================================================
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
		FlexItem(mMixSlider).withWidth(mVibraFlangeDialWidth).withHeight(mSliderSize - 5.f)
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
	lfoWaveformBox.alignContent = FlexBox::AlignContent::center;
	lfoWaveformBox.justifyContent = FlexBox::JustifyContent::flexStart;
	lfoWaveformBox.flexDirection = FlexBox::Direction::column;
	lfoWaveformBox.items.addArray(
		{
		FlexItem(mLFOWaveformLabel).withWidth(mSliderSize).withHeight(25.f),
		FlexItem(lfoSelectBox).withWidth(mSliderSize).withHeight(40.f)
		});

	// First row of parameters in the plugin
	FlexBox firstRowBox;
	firstRowBox.alignContent = FlexBox::AlignContent::center;
	firstRowBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	firstRowBox.flexDirection = FlexBox::Direction::row;
	firstRowBox.items.addArray(
		{
			FlexItem(feedbackBox).withWidth(mSliderSize).withHeight(mSliderSize + 12.f),
			FlexItem(wetBox).withWidth(mSliderSize+15.f).withHeight(mSliderSize + mLabelHeight),
			FlexItem(delayBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight)
		});

	// Second row (LFO) parameters of plugin
	FlexBox secondRowBox;
	secondRowBox.alignContent = FlexBox::AlignContent::center;
	secondRowBox.justifyContent = FlexBox::JustifyContent::spaceBetween;
	secondRowBox.flexDirection = FlexBox::Direction::row;
	secondRowBox.items.addArray(
		{
			FlexItem(lfoFreqBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
			FlexItem(lfoWaveformBox).withWidth(mSliderSize).withHeight(mSliderSize + mLabelHeight),
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
	
	auto area = getLocalBounds().reduced(mReductionSize, mReductionSize);
	area.removeFromBottom(mTitleHeight);
	masterBox.performLayout(area.toFloat());
}

//==============================================================================
void FlangerVibratoAudioProcessorEditor::initialiseGUI()
{
	// ON / OFF ================================
	mOnOffButton.setLookAndFeel(&mOnOffLookAndFeel);
	mOnOffButton.setSize(100.f, 30.f);
	mOnOffButton.setColour(TextButton::textColourOffId, Colours::white.darker(1));
	mOnOffButton.setButtonText("VibraFlange");
	mOnOffButton.addListener(this);
	bool on = *mState.getRawParameterValue(IDs::onOff);
	mOnOffButton.setToggleState(on, false);
	addAndMakeVisible(mOnOffButton);
	mOnOffAttachment.reset(new ButtonAttachment(mState, IDs::onOff, mOnOffButton));

	// MIX =====================================
	//Slider
	mMixSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mMixSlider.setSize(mVibraFlangeDialWidth, mSliderSize);
	mMixSlider.setTextBoxStyle(Slider::NoTextBox, true, mSliderSize, mTextBoxHeight);
	mMixSliderAttachment.reset(new SliderAttachment(mState, IDs::wetness, mMixSlider));
	addAndMakeVisible(mMixSlider);
	mMixSlider.setLookAndFeel(&mVibraFlangeLookAndFeel);
	mMixSlider.setTextValueSuffix(" %");

	// FEEDBACK===================================
	// Slider
	mFBSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mFBSlider.setSize(mSliderSize, mSliderSize);
	mFBSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
	mFBSliderAttachment.reset(new SliderAttachment(mState, IDs::feedback, mFBSlider));
	addAndMakeVisible(mFBSlider);
	mFBSlider.setLookAndFeel(&mCustomLookAndFeel);
	mFBSlider.setTextValueSuffix(" %");

	// Label
	mFBLabel.setText("Feedback", dontSendNotification);
	mFBLabel.setSize(mSliderSize, mLabelHeight);
	mFBLabel.setFont(mLabelFont);
	mFBLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mFBLabel);

	// DELAY TIME ==============================
	// Slider
	mDelaySlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mDelaySlider.setSize(mSliderSize, mSliderSize);
	mDelaySlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
	mTimeSliderAttachment.reset(new SliderAttachment(mState, IDs::time, mDelaySlider));
	addAndMakeVisible(mDelaySlider);
	mDelaySlider.setLookAndFeel(&mCustomLookAndFeel);
	mDelaySlider.setTextValueSuffix(" ms");

	// Label
	mDelayLabel.setText("Delay", dontSendNotification);
	mDelayLabel.setSize(mSliderSize, mLabelHeight);
	mDelayLabel.setFont(mLabelFont);
	mDelayLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mDelayLabel);

	// LFO FREQUENCY ============================
	// Slider
	mLFOFreqSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mLFOFreqSlider.setSize(mSliderSize, mSliderSize);
	mLFOFreqSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
	mLFOFreqSliderAttachment.reset(new SliderAttachment(mState, IDs::lfoFreq, mLFOFreqSlider));
	addAndMakeVisible(mLFOFreqSlider);
	mLFOFreqSlider.setLookAndFeel(&mCustomLookAndFeel);
	mLFOFreqSlider.setTextValueSuffix(" Hz");

	// Label
	mLFOFreqLabel.setText("Freq", dontSendNotification);
	mLFOFreqLabel.setSize(mSliderSize, mLabelHeight);
	mLFOFreqLabel.setFont(mLabelFont);
	mLFOFreqLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOFreqLabel);

	// LFO PHASE ================================
	// Slider
	mLFOPhaseSlider.setSliderStyle(Slider::SliderStyle::Rotary);
	mLFOPhaseSlider.setSize(mSliderSize, mSliderSize);
	mLFOPhaseSlider.setTextBoxStyle(Slider::TextBoxBelow, false, mSliderSize, mTextBoxHeight);
	mLFOPhaseSliderAttachment.reset(new SliderAttachment(mState, IDs::lfoPhase, mLFOPhaseSlider));
	addAndMakeVisible(mLFOPhaseSlider);
	mLFOPhaseSlider.setLookAndFeel(&mCustomLookAndFeel);
	String degreeSign = CharPointer_UTF8("\xc2\xb0");
	mLFOPhaseSlider.setTextValueSuffix(degreeSign);

	// Label
	mLFOPhaseLabel.setText("Phase", dontSendNotification);
	mLFOPhaseLabel.setSize(mSliderSize, mLabelHeight);
	mLFOPhaseLabel.setFont(mLabelFont);
	mLFOPhaseLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOPhaseLabel);

	// LFO WAVEFORM =============================
	// Combo box
	mLFOWaveformBox.setSize(mSliderSize, 25.f);
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
	mLFOWaveformLabel.setSize(mSliderSize, 20.f);
	mLFOWaveformLabel.setFont(mLabelFont);
	mLFOWaveformLabel.setJustificationType(Justification::centred);
	addAndMakeVisible(mLFOWaveformLabel);
}

//==============================================================================
// Toggle button when clicked
void FlangerVibratoAudioProcessorEditor::buttonClicked(Button * b)
{
	if (b == &mOnOffButton)
	{
		bool on = *mState.getRawParameterValue(IDs::onOff);
		float* value = mState.getRawParameterValue(IDs::onOff);
		mOnOffButton.setToggleState((on ? false : true), false);
		*value = (on ? false : true);
		repaint();
	}
}
