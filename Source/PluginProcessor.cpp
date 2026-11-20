#include "PluginProcessor.h"
#include "PluginEditor.h"

VDrumLabAudioProcessor::VDrumLabAudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true)),
      apvts(*this, nullptr, "Parameters", createParameterLayout())
{
}

VDrumLabAudioProcessor::~VDrumLabAudioProcessor() {}

juce::AudioProcessorValueTreeState::ParameterLayout VDrumLabAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Master Volume: от -60 dB до 0 dB
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "master_volume", "Master Volume",
        juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f),
        0.0f));
    
    // Tempo: от 60 до 200 BPM
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
        "tempo", "Tempo",
        juce::NormalisableRange<float>(60.0f, 200.0f, 1.0f),
        120.0f));
    
    return { params.begin(), params.end() };
}

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

void VDrumLabAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    this->sampleRate = sampleRate;
}

void VDrumLabAudioProcessor::releaseResources() {}

bool VDrumLabAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo();
}

void VDrumLabAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    // Получаем текущие значения параметров
    masterVolume = juce::Decibels::decibelsToGain(apvts.getRawParameterValue("master_volume")->load());
    currentTempo = apvts.getRawParameterValue("tempo")->load();
    
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // Применяем мастер-громкость ко всем сэмплам
    for (int channel = 0; channel < totalNumOutputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] *= masterVolume;
        }
    }
}

void VDrumLabAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void VDrumLabAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(apvts.state.getType()))
            apvts.replaceState(juce::ValueTree::fromXml(*xmlState));
}

juce::AudioProcessorEditor* VDrumLabAudioProcessor::createEditor() {
    return new VDrumLabAudioProcessorEditor(*this);
}

bool VDrumLabAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new VDrumLabAudioProcessor();
}
