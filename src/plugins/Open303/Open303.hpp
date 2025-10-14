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
        Trig,          // 1
        NoteNum,       // 2
        Velocity,      // 3
        Waveform,      // 4
        Tuning,        // 5
        Cutoff,        // 6
        Resonance,     // 7
        EnvMod,        // 8
        Decay,         // 9
        Accent,        // 10
        Volume,        // 11
        // Extended parameters
        AmpSustain,    // 12
        AmpDecay,      // 13
        AmpRelease,    // 14
        FeedbackHPF,   // 15
        NormalAttack,  // 16
        AccentAttack,  // 17
        AccentDecay,   // 18
        SlideTime,     // 19
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

    // Gate and trigger tracking
    float m_prev_gate;
    float m_prev_trig;
    float m_prev_note_num;
    int m_current_note;

    rosic::Open303 synth;
};

} // namespace Open303
