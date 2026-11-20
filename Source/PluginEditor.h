#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class VDrumLabAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    VDrumLabAudioProcessorEditor(VDrumLabAudioProcessor&);
    ~VDrumLabAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    VDrumLabAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VDrumLabAudioProcessorEditor)
};
