#include "CustomAudioEditor.h"

// ===== SliderBinding implementation (5-arg) =====
CustomAudioEditor::SliderBinding::SliderBinding(juce::AudioProcessor& proc,
                                                const juce::String& idOrName,
                                                const juce::String& labelText,
                                                const juce::String& suffixText,
                                                juce::ValueTree parentToAppendTo)
    : suffix(suffixText)
{
    // find parameter by id OR by visible name
    for (auto* p : proc.getParameters())
        if (auto* rp = dynamic_cast<juce::RangedAudioParameter*>(p))
            if (rp->paramID == idOrName || rp->getName(64) == idOrName)
            { param = rp; break; }

    jassert(param != nullptr);

    const auto range = param->getNormalisableRange();

    row = juce::ValueTree{ "Component", { { "flex-direction","row" }, { "gap",12 }, { "align-items","centre" } }, {} };
    labelNode  = juce::ValueTree{ "Text", { { "text", labelText }, { "min-width", 110 } }, {} };
    sliderNode = juce::ValueTree{ "Slider",
        { { "min", (double) range.start }, { "max", (double) range.end },
          { "value", (double) param->getValue() }, { "width", 290 } }, {} };
    valueNode  = juce::ValueTree{ "Text",
        { { "text", param->getCurrentValueAsText() + (suffix.isEmpty() ? "" : " " + suffix) },
          { "min-width", 96 } }, {} };

    row.appendChild(labelNode,  nullptr);
    row.appendChild(sliderNode, nullptr);
    row.appendChild(valueNode,  nullptr);
    parentToAppendTo.appendChild(row, nullptr);

    // Param -> UI
    attachment = std::make_unique<juce::ParameterAttachment>(
        *param,
        [this](float newVal)
        {
            sliderNode.setProperty("value", (double) newVal, nullptr);
            valueNode.setProperty("text",
                param->getCurrentValueAsText() + (suffix.isEmpty() ? "" : " " + suffix),
                nullptr);
        });

    // UI -> Param
    sliderNode.addListener(this);
}

CustomAudioEditor::SliderBinding::~SliderBinding()
{
    sliderNode.removeListener(this);
}

void CustomAudioEditor::SliderBinding::valueTreePropertyChanged(juce::ValueTree& t,
                                                                const juce::Identifier& prop)
{
    if (t != sliderNode || prop != juce::Identifier("value") || param == nullptr) return;
    const auto v = (float) (double) sliderNode.getProperty("value");
    attachment->setValueAsCompleteGesture(v);
}

//------------- Editor -------------
CustomAudioEditor::CustomAudioEditor(RNBO::JuceAudioProcessor* const p,
                                     RNBO::CoreObject& rnboObject)
    : juce::AudioProcessorEditor(p),
      _audioProcessor(p),
      _rnboObject(rnboObject)
{
    jassert(_audioProcessor != nullptr);
    static_cast<juce::AudioProcessor*>(_audioProcessor)->addListener(this);

#if JUCE_DEBUG
    // Print parameter IDs/names/ranges once (handy for binding)
    juce::Timer::callAfterDelay(0, [this] {
        DBG("=== Parameters exposed by processor ===");
        auto* proc = static_cast<juce::AudioProcessor*>(_audioProcessor);
        for (auto* p : proc->getParameters())
            if (auto* rp = dynamic_cast<juce::RangedAudioParameter*>(p))
            {
                const auto r = rp->getNormalisableRange();
                DBG("paramID='" << rp->paramID
                    << "'  name='" << rp->getName(64)
                    << "'  range=" << r.start << "…" << r.end);
            }
    });
#endif

    setSize(600, 400);

    // 1) Build the ValueTree (root + theme)
    view = topLevel("Stratocumulus_test");
    view.setProperty("style", new jive::Object{
        {"background", "#101010"},
        {"foreground", "#999999"},
        {"font-size", 15},
        {"font-family", "Georgia"},
        {"color", "#EEEEEE"}
    }, nullptr);

    setWantsKeyboardFocus(true); // we'll use the 't' key to toggle

    // A status line we can update to see changes immediately
    statusTextNode = juce::ValueTree{
        "Text", { { "id", "status" }, { "text", "Status: default theme" }, { "margin", "8 0 0 0" } }, {}
    };
    view.appendChild(statusTextNode, nullptr);

    // === Root container that everything sits inside ===
auto root = juce::ValueTree{
    "Component",
    {
        { "position", "relative" },   // so Dry/Wet can be absolutely positioned
        { "flex", "1" },
        { "padding", 16 },
        { "gap", 24 },
        { "flex-direction", "column" }
    },
    {}
};
view.appendChild(root, nullptr);

// Row for the two vertical columns (Left + Middle)
auto columnsRow = juce::ValueTree{
    "Component",
    {
        { "display", "flex" },
        { "flex-direction", "row" },
        { "gap", 32 },
        { "align-items", "start" }
    },
    {}
};
root.appendChild(columnsRow, nullptr);

// Left column: Density, Grain Size, Spread, Stereo
auto leftCol = juce::ValueTree{
    "Component",
    {
        { "display", "flex" },
        { "flex-direction", "column" },
        { "gap", 14 },
        { "min-width", 280 },         // keep value text from running into the next column
        { "max-width", 340 }
    },
    {}
};
columnsRow.appendChild(leftCol, nullptr);

// Middle column: Attack, Decay, Sustain, Release
auto midCol = juce::ValueTree{
    "Component",
    {
        { "display", "flex" },
        { "flex-direction", "column" },
        { "gap", 14 },
        { "min-width", 280 },
        { "max-width", 340 }
    },
    {}
};
columnsRow.appendChild(midCol, nullptr);

// Flexible spacer to fill remaining horizontal space
columnsRow.appendChild(juce::ValueTree{
    "Component",
    { { "flex", 1 } }, {} }, nullptr);

// Bottom-right dock for Dry/Wet (absolute pin)
auto dryWetDock = juce::ValueTree{
    "Component",
    {
        { "position", "absolute" },
        { "right", 24 },
        { "bottom", 24 },
        { "display", "flex" },
        { "flex-direction", "column" },
        { "align-items", "end" },
        { "min-width", 260 }
    },
    {}
};
root.appendChild(dryWetDock, nullptr);

// Helper to bind sliders into a specific container
auto addTo = [this](juce::ValueTree& parent,
                    const juce::String& paramID,
                    const juce::String& unit)
{
    jiveParamBindings_.push_back(std::make_unique<SliderBinding>(
        *static_cast<juce::AudioProcessor*>(_audioProcessor),
        paramID, paramID, unit, parent));
};

// ---- Left column (vertical) ----
addTo(leftCol, "Density",    "Hz");
addTo(leftCol, "Grain_Size", "ms");
addTo(leftCol, "Spread",     "%");
addTo(leftCol, "Stereo",     "%");

// ---- Middle column (vertical) ----
addTo(midCol, "Attack",  "ms");
addTo(midCol, "Decay",   "ms");
addTo(midCol, "Sustain", "%");
addTo(midCol, "Release", "ms");

// ---- Bottom-right ----
addTo(dryWetDock, "Dry/Wet", "%");

    // 2) Interpret & mount once
    editor = viewInterpreter.interpret(view);
    if (editor)
    {
        auto comp = editor->getComponent();
        jassert(comp != nullptr);
        addAndMakeVisible(*comp);
        viewInterpreter.listenTo(*editor);

        // Find the actual JUCE Button created for our JIVE node and wire a click handler
        if (auto* root = comp.get())
            if (auto* btn = dynamic_cast<juce::Button*>(root->findChildWithID("jive-btn")))
                btn->onClick = [this]{ toggleTheme(); };
    }
}

CustomAudioEditor::~CustomAudioEditor()
{
    if (_audioProcessor)
        static_cast<juce::AudioProcessor*>(_audioProcessor)->removeListener(this);
}

juce::ValueTree CustomAudioEditor::topLevel(const juce::String& greeting)
{
    return juce::ValueTree{
        "Component",
        {
            {"width", 640},
            {"height", 400},
            {"justify-content", "centre"},
            {"align-items", "centre"},
            {"gap", 12},
            {"padding", 16},
        },
        {
            juce::ValueTree{
                "Text",
                { {"text", greeting}, {"font-size", 18} },
                {}
            },
        }
    };
}

void CustomAudioEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void CustomAudioEditor::resized()
{
    if (editor)
        if (auto comp = editor->getComponent())
            comp->setBounds(getLocalBounds().reduced(10));
}

void CustomAudioEditor::openSettingsWindow()
{
    juce::DialogWindow::LaunchOptions o;
    o.dialogTitle = "Settings";
    o.dialogBackgroundColour = juce::Colours::darkgrey;
    o.escapeKeyTriggersCloseButton = true;
    o.useNativeTitleBar = true;
    o.resizable = true;
    o.content.setOwned(new juce::Label({}, "Settings window placeholder"));
    o.componentToCentreAround = this;
    o.launchAsync();
}

void CustomAudioEditor::toggleTheme()
{
    static bool dark = true;
    dark = !dark;

    // Change the theme by replacing the root "style" object
    view.setProperty("style", new jive::Object{
        { "background", dark ? "#101010" : "#999999" },
        { "foreground", dark ? "#EDEFF2" : "#111111" },
        { "font-size", 15 },
        { "font-family", "Georgia"},
        {"color", dark ? "#EEEEEE" : "#222222" }
    }, nullptr);

    // Update a piece of text so you can see the ValueTree change immediately
    if (statusTextNode.isValid())
        statusTextNode.setProperty("text",
            juce::String("Status: ") + (dark ? "dark theme" : "light theme"),
            nullptr);
}

bool CustomAudioEditor::keyPressed(const juce::KeyPress& kp)
{
    if (kp.getTextCharacter() == 't' || kp.getTextCharacter() == 'T')
    {
        toggleTheme();
        return true;
    }
    return false;
}
