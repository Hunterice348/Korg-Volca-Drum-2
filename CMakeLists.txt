cmake_minimum_required(VERSION 3.15)
project(V-DRUM-LAB VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для отключения копирования в системную папку на CI-сервере
option(VDRUM_COPY_PLUGIN_AFTER_BUILD "Copy VST3 to system folder after build" ON)

# Добавляем JUCE (должен лежать в папке JUCE в корне проекта)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/JUCE/CMakeLists.txt")
    add_subdirectory(JUCE)
else()
    message(FATAL_ERROR "JUCE not found. Please run: git submodule update --init --recursive")
endif()

juce_add_plugin(VDrumLab
    COMPANY_NAME "VDrumLab"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD ${VDRUM_COPY_PLUGIN_AFTER_BUILD}
    PLUGIN_MANUFACTURER_CODE Vdrl
    PLUGIN_CODE Vdlb
    FORMATS VST3 Standalone
    PRODUCT_NAME "V-DRUM LAB"
)

juce_generate_juce_header(VDrumLab)

target_sources(VDrumLab
    PRIVATE
        Source/PluginProcessor.cpp
        Source/PluginEditor.cpp
)

target_compile_definitions(VDrumLab
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(VDrumLab
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)
