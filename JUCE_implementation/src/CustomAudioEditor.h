#pragma once

#include <JuceHeader.h>
#include "RNBO.h"
#include "RNBO_JuceAudioProcessor.h"
#include <jive_layouts/jive_layouts.h>

class CustomAudioEditor : public juce::AudioProcessorEditor,
                          private juce::AudioProcessorListener
{
public:
    CustomAudioEditor(RNBO::JuceAudioProcessor* const p, RNBO::CoreObject& rnboObject);
    ~CustomAudioEditor() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    // ===== Binding a JUCE parameter to a JIVE slider row =====
    struct SliderBinding : juce::ValueTree::Listener
    {
        juce::RangedAudioParameter* param = nullptr;
        std::unique_ptr<juce::ParameterAttachment> attachment;

        juce::ValueTree row, labelNode, sliderNode, valueNode;
        juce::String suffix;

        SliderBinding(juce::AudioProcessor& proc,
                      const juce::String& idOrName,   // paramID or visible name
                      const juce::String& labelText,  // left label text
                      const juce::String& suffixText, // unit text on the right
                      juce::ValueTree parentToAppendTo);

        ~SliderBinding() override;
        void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override;
    };

    // ===== AudioProcessorListener stubs =====
    void audioProcessorParameterChanged(juce::AudioProcessor*, int, float) override {}
    void audioProcessorChanged(juce::AudioProcessor*, const juce::AudioProcessorListener::ChangeDetails&) override {}

    // ===== Helpers =====
    juce::ValueTree topLevel(const juce::String& greeting);
    void openSettingsWindow();

    // ===== JIVE state =====
    juce::ValueTree                         view;
    jive::Interpreter                       viewInterpreter;
    std::unique_ptr<jive::GuiItem>          editor;
    std::vector<std::unique_ptr<SliderBinding>> jiveParamBindings_;

    // ===== Back-refs =====
    juce::AudioProcessor*                   _audioProcessor = nullptr;
    RNBO::CoreObject&                       _rnboObject;

    // Keep handles to nodes we want to mutate live
    juce::ValueTree statusTextNode;     // "Status: …" label
    juce::ValueTree jiveButtonNode;     // the JIVE button node (so we can find the JUCE Button)

    /** Toggle theme + update status text. */
    void toggleTheme();

    // Let this editor react to keyboard presses (press 't' to toggle)
    bool keyPressed(const juce::KeyPress& kp) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CustomAudioEditor)
};