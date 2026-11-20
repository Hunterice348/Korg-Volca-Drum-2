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
    
    // Регуляторы
    juce::Slider masterVolumeSlider;
    juce::Slider tempoSlider;
    
    // Привязки к параметрам
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> masterVolumeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> tempoAttachment;
    
    // Индикаторы Drum Parts
    juce::Label drumPartLabels[6];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VDrumLabAudioProcessorEditor)
};
