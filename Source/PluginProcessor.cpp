/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <functional>

//==============================================================================
FlangerVibratoAudioProcessor::FlangerVibratoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
		#if ! JucePlugin_IsMidiEffect
		#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
		#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
		#endif
	),
	mState(*this, nullptr, Identifier("VibraFlange"),
		{
			  std::make_unique<AudioParameterFloat>(IDs::time,
													 "Time",
													 0.0,
													 7.0,
													 1.0
													),
			  std::make_unique<AudioParameterFloat>(IDs::wetness,
													 "Mix",
													 0.0,
													 100.0,
													 100.0
													),
			  std::make_unique<AudioParameterFloat>(IDs::feedback,
													 "Feedback",
													 -99.0,
													 99.0,
													 0.0
													),
			 std::make_unique<AudioParameterFloat>(IDs::lfoFreq,
												   "LFO Freq",
												   NormalisableRange<float> (0.0, 100.0),
												   40.0,
												   String(),
												   AudioProcessorParameter::genericParameter,
												   [](float value, int maxStringLength) {return static_cast<String>(round(0.01f * exp(0.06908f * value) * 100.f) / 100.f); },
												   [](const String& text) {return log(100 * text.getFloatValue()) / 0.06908; }
												   ),
			 std::make_unique<AudioParameterFloat>(IDs::lfoPhase,
													 "LFO Phase",
													 0.0,
													 360.0,
													 180.0
													),
			 std::make_unique<AudioParameterInt>(IDs::lfoWaveform,
													 "LFO Waveform",
													 0,
													 3,
													 0
												 ),
			 std::make_unique<AudioParameterBool>(IDs::onOff,
													 "On/Off",
													 true
												  )
		}),
	mVibraFlange(mState)
#endif
{
	// Empty constructor
}

FlangerVibratoAudioProcessor::~FlangerVibratoAudioProcessor()
{
	// Emty destructor
}

//==============================================================================
const String FlangerVibratoAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FlangerVibratoAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FlangerVibratoAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FlangerVibratoAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FlangerVibratoAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FlangerVibratoAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FlangerVibratoAudioProcessor::getCurrentProgram()
{
    return 0;
}

void FlangerVibratoAudioProcessor::setCurrentProgram (int index)
{
}

const String FlangerVibratoAudioProcessor::getProgramName (int index)
{
    return {};
}

void FlangerVibratoAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void FlangerVibratoAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = getNumOutputChannels();
	mVibraFlange.prepare(spec);
}

void FlangerVibratoAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FlangerVibratoAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FlangerVibratoAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	mVibraFlange.process(buffer);
}

//==============================================================================
bool FlangerVibratoAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* FlangerVibratoAudioProcessor::createEditor()
{
    return new FlangerVibratoAudioProcessorEditor (*this);
}

//==============================================================================
void FlangerVibratoAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	auto state = mState.copyState();
	std::unique_ptr<XmlElement> xml(state.createXml());
	copyXmlToBinary(*xml, destData);
}

void FlangerVibratoAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(mState.state.getType()))
			mState.replaceState(ValueTree::fromXml(*xmlState));
}

AudioProcessorValueTreeState & FlangerVibratoAudioProcessor::getState()
{
	return mState;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FlangerVibratoAudioProcessor();
}
