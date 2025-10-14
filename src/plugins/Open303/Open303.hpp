// Open303.hpp
// SuperCollider wrapper for Open303 bass synthesizer

#pragma once

#include "SC_PlugIn.hpp"
#include "DSP/rosic_Open303.h"

namespace Open303 {

class Open303 : public SCUnit {
public:
    Open303();
    ~Open303();

private:
    void next_a(int nSamples);
    void next_k(int nSamples);

    enum InputParams {
        Gate,          // 0
        NoteNum,       // 1
        Velocity,      // 2
        Waveform,      // 3
        Tuning,        // 4
        Cutoff,        // 5
        Resonance,     // 6
        EnvMod,        // 7
        Decay,         // 8
        Accent,        // 9
        Volume,        // 10
        // Extended parameters
        AmpSustain,    // 11
        AmpDecay,      // 12
        AmpRelease,    // 13
        FeedbackHPF,   // 14
        NormalAttack,  // 15
        AccentAttack,  // 16
        AccentDecay,   // 17
        SlideTime,     // 18
        NumInputParams
    };

    enum Outputs { Out1, NumOutputParams };

    // Store previous values for change detection
    float m_prev_waveform;
    float m_prev_tuning;
    float m_prev_cutoff;
    float m_prev_resonance;
    float m_prev_envmod;
    float m_prev_decay;
    float m_prev_accent;
    float m_prev_volume;
    float m_prev_amp_sustain;
    float m_prev_amp_decay;
    float m_prev_amp_release;
    float m_prev_feedback_hpf;
    float m_prev_normal_attack;
    float m_prev_accent_attack;
    float m_prev_accent_decay;
    float m_prev_slide_time;

    // Gate tracking
    float m_prev_gate;
    int m_current_note;

    rosic::Open303 synth;
};

} // namespace Open303
