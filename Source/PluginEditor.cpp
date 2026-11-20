#include "PluginProcessor.h"
#include "PluginEditor.h"

VDrumLabAudioProcessorEditor::VDrumLabAudioProcessorEditor(VDrumLabAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(900, 650);
    
    // Master Volume Slider
    masterVolumeSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    masterVolumeSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    masterVolumeSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(100, 200, 255));
    masterVolumeSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromRGB(60, 60, 70));
    addAndMakeVisible(masterVolumeSlider);
    masterVolumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "master_volume", masterVolumeSlider);
    
    // Tempo Slider
    tempoSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    tempoSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    tempoSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour::fromRGB(255, 150, 100));
    tempoSlider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colour::fromRGB(60, 60, 70));
    addAndMakeVisible(tempoSlider);
    tempoAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "tempo", tempoSlider);
    
    // Drum Part Labels
    for (int i = 0; i < 6; ++i)
    {
        drumPartLabels[i].setText("PART " + juce::String(i + 1), juce::dontSendNotification);
        drumPartLabels[i].setJustificationType(juce::Justification::centred);
        drumPartLabels[i].setColour(juce::Label::textColourId, juce::Colours::white);
        drumPartLabels[i].setColour(juce::Label::backgroundColourId, juce::Colour::fromRGB(50, 50, 60));
        addAndMakeVisible(drumPartLabels[i]);
    }
}

VDrumLabAudioProcessorEditor::~VDrumLabAudioProcessorEditor() {}

void VDrumLabAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Тёмный industrial фон
    g.fillAll(juce::Colour::fromRGB(25, 25, 30));
    
    // Заголовок
    g.setColour(juce::Colours::white);
    g.setFont(36.0f);
    g.drawText("V-DRUM LAB", getLocalBounds().removeFromTop(70).reduced(20),
               juce::Justification::centredLeft, true);
    
    // Подзаголовок
    g.setFont(14.0f);
    g.setColour(juce::Colours::grey);
    g.drawText("Advanced Digital Percussion Synthesizer",
               getLocalBounds().removeFromTop(110).removeFromTop(30).reduced(20),
               juce::Justification::centredLeft, true);
    
    // Разделительная линия
    g.setColour(juce::Colour::fromRGB(80, 80, 90));
    g.drawHorizontalLine(120, 20.0f, getWidth() - 20.0f);
    
    // Секция Master Controls
    g.setColour(juce::Colour::fromRGB(150, 150, 160));
    g.setFont(16.0f);
    g.drawText("MASTER CONTROLS", juce::Rectangle<int>(20, 140, 200, 30),
               juce::Justification::centredLeft, true);
    
    // Секция Drum Parts
    g.drawText("DRUM PARTS", juce::Rectangle<int>(20, 320, 200, 30),
               juce::Justification::centredLeft, true);
}

void VDrumLabAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
    
    // Master Controls секция
    auto masterSection = bounds.removeFromTop(200).reduced(20);
    masterVolumeSlider.setBounds(masterSection.removeFromLeft(120));
    masterSection.removeFromLeft(20);
    tempoSlider.setBounds(masterSection.removeFromLeft(120));
    
    // Drum Parts секция
    auto drumSection = bounds.removeFromTop(250).reduced(20);
    int labelWidth = 100;
    int labelHeight = 60;
    int spacing = 20;
    
    for (int i = 0; i < 6; ++i)
    {
        int x = 20 + (i % 6) * (labelWidth + spacing);
        int y = 340 + (i / 6) * (labelHeight + spacing);
        drumPartLabels[i].setBounds(x, y, labelWidth, labelHeight);
    }
}
