#include "PluginProcessor.h"
#include "PluginEditor.h"

VDrumLabAudioProcessorEditor::VDrumLabAudioProcessorEditor(VDrumLabAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(800, 600);
}

VDrumLabAudioProcessorEditor::~VDrumLabAudioProcessorEditor() {}

void VDrumLabAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(30, 30, 35));
    
    g.setColour(juce::Colours::white);
    g.setFont(32.0f);
    g.drawText("V-DRUM LAB", getLocalBounds().removeFromTop(60).reduced(20), juce::Justification::centredLeft, true);
    
    g.setFont(14.0f);
    g.setColour(juce::Colours::grey);
    g.drawText("Advanced Digital Percussion Synthesizer", getLocalBounds().removeFromTop(100).removeFromTop(30).reduced(20), juce::Justification::centredLeft, true);
    
    g.setColour(juce::Colour::fromRGB(100, 200, 100));
    g.setFont(20.0f);
    g.drawText("CI Build Successful! Stage 1 Complete.", getLocalBounds().withTrimmedTop(200).withTrimmedBottom(200), juce::Justification::centred, true);
}

void VDrumLabAudioProcessorEditor::resized() {}
