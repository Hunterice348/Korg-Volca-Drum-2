#include "PluginProcessor.h"
#include "PluginEditor.h"

VDrumLabAudioProcessor::VDrumLabAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

VDrumLabAudioProcessor::~VDrumLabAudioProcessor() {}

const juce::String VDrumLabAudioProcessor::getName() const { return JucePlugin_Name; }
bool VDrumLabAudioProcessor::acceptsMidi() const { return true; }
bool VDrumLabAudioProcessor::producesMidi() const { return false; }
bool VDrumLabAudioProcessor::isMidiEffect() const { return false; }
double VDrumLabAudioProcessor::getTailLengthSeconds() const { return 0.0; }
int VDrumLabAudioProcessor::getNumPrograms() { return 1; }
int VDrumLabAudioProcessor::getCurrentProgram() { return 0; }
void VDrumLabAudioProcessor::setCurrentProgram(int index) {}
const juce::String VDrumLabAudioProcessor::getProgramName(int index) { return {}; }
void VDrumLabAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

void VDrumLabAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}
void VDrumLabAudioProcessor::releaseResources() {}

bool VDrumLabAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void VDrumLabAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    for (auto i = getTotalNumInputChannels(); i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
}

void VDrumLabAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void VDrumLabAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

juce::AudioProcessorEditor* VDrumLabAudioProcessor::createEditor() {
    return new VDrumLabAudioProcessorEditor(*this);
}

bool VDrumLabAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new VDrumLabAudioProcessor();
}
