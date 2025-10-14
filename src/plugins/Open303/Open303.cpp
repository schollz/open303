// Open303.cpp
// SuperCollider wrapper for Open303 bass synthesizer

#include "Open303.hpp"
#include "SC_PlugIn.hpp"

static InterfaceTable *ft;

namespace Open303 {

Open303::Open303() {
    const float samplerate = sampleRate();
    synth.setSampleRate(samplerate);

    // Initialize with default values from input parameters
    float waveform = in0(Waveform);
    float tuning = in0(Tuning);
    float cutoff = in0(Cutoff);
    float resonance = in0(Resonance);
    float envmod = in0(EnvMod);
    float decay = in0(Decay);
    float accent = in0(Accent);
    float volume = in0(Volume);
    float amp_sustain = in0(AmpSustain);
    float amp_decay = in0(AmpDecay);
    float amp_release = in0(AmpRelease);
    float feedback_hpf = in0(FeedbackHPF);
    float normal_attack = in0(NormalAttack);
    float accent_attack = in0(AccentAttack);
    float accent_decay = in0(AccentDecay);
    float slide_time = in0(SlideTime);

    synth.setWaveform(waveform);
    synth.setTuning(tuning);
    synth.setCutoff(cutoff);
    synth.setResonance(resonance);
    synth.setEnvMod(envmod);
    synth.setDecay(decay);
    synth.setAccent(accent);
    synth.setVolume(volume);
    synth.setAmpSustain(amp_sustain);
    synth.setAmpDecay(amp_decay);
    synth.setAmpRelease(amp_release);
    synth.setFeedbackHighpass(feedback_hpf);
    synth.setNormalAttack(normal_attack);
    synth.setAccentAttack(accent_attack);
    synth.setAccentDecay(accent_decay);
    synth.setSlideTime(slide_time);

    // Store initial values
    m_prev_waveform = waveform;
    m_prev_tuning = tuning;
    m_prev_cutoff = cutoff;
    m_prev_resonance = resonance;
    m_prev_envmod = envmod;
    m_prev_decay = decay;
    m_prev_accent = accent;
    m_prev_volume = volume;
    m_prev_amp_sustain = amp_sustain;
    m_prev_amp_decay = amp_decay;
    m_prev_amp_release = amp_release;
    m_prev_feedback_hpf = feedback_hpf;
    m_prev_normal_attack = normal_attack;
    m_prev_accent_attack = accent_attack;
    m_prev_accent_decay = accent_decay;
    m_prev_slide_time = slide_time;

    m_prev_gate = 0.f;
    m_prev_trig = 0.f;
    m_prev_note_num = -1.f;
    m_current_note = -1;

    // Determine calculation function based on rate
    if (inRate(Gate) == calc_FullRate) {
        mCalcFunc = make_calc_function<Open303, &Open303::next_a>();
    } else {
        mCalcFunc = make_calc_function<Open303, &Open303::next_k>();
    }

    next_k(1);
}

Open303::~Open303() {
}

void Open303::next_a(int nSamples) {
    float *outbuf = out(Out1);

    for (int i = 0; i < nSamples; ++i) {
        // Read gate, trig, note, and velocity for this sample
        float gate = in(Gate)[i];
        float trig = in(Trig)[i];
        float note_num = in(NoteNum)[i];
        int velocity = (int)(in(Velocity)[i] * 127.f);

        // Handle note on/off
        bool should_trigger = false;

        // Trigger on gate rising edge
        if (gate > 0.5f && m_prev_gate <= 0.5f) {
            should_trigger = true;
        }
        // Trigger on trig rising edge (even if gate is already high)
        else if (trig > 0.5f && m_prev_trig <= 0.5f) {
            should_trigger = true;
        }

        if (should_trigger) {
            int note = (int)note_num;
            // Retrigger envelopes while maintaining pitch slide
            synth.retriggerNote(note, velocity);
            m_current_note = note;
        } else if (gate <= 0.5f && m_prev_gate > 0.5f) {
            // Gate went low - note off
            if (m_current_note >= 0) {
                synth.noteOn(m_current_note, 0, 0.0);
                m_current_note = -1;
            }
        } else if (gate > 0.5f && note_num != m_prev_note_num) {
            // Note changed while gate is high - slide to new note without re-triggering envelope
            int note = (int)note_num;
            synth.noteOn(note, velocity, 0.0);
            m_current_note = note;
        }

        m_prev_gate = gate;
        m_prev_trig = trig;
        m_prev_note_num = note_num;

        // Update parameters if changed
        float waveform = in(Waveform)[i];
        if (waveform != m_prev_waveform) {
            synth.setWaveform(waveform);
            m_prev_waveform = waveform;
        }

        float cutoff = in(Cutoff)[i];
        if (cutoff != m_prev_cutoff) {
            synth.setCutoff(cutoff);
            m_prev_cutoff = cutoff;
        }

        float resonance = in(Resonance)[i];
        if (resonance != m_prev_resonance) {
            synth.setResonance(resonance);
            m_prev_resonance = resonance;
        }

        float envmod = in(EnvMod)[i];
        if (envmod != m_prev_envmod) {
            synth.setEnvMod(envmod);
            m_prev_envmod = envmod;
        }

        // Generate one sample
        outbuf[i] = static_cast<float>(synth.getSample());
    }
}

void Open303::next_k(int nSamples) {
    float *outbuf = out(Out1);

    // Read control rate inputs
    float gate = in0(Gate);
    float trig = in0(Trig);
    float note_num = in0(NoteNum);
    int velocity = (int)(in0(Velocity) * 127.f);

    // Handle note on/off
    bool should_trigger = false;

    // Trigger on gate rising edge
    if (gate > 0.5f && m_prev_gate <= 0.5f) {
        should_trigger = true;
    }
    // Trigger on trig rising edge (even if gate is already high)
    else if (trig > 0.5f && m_prev_trig <= 0.5f) {
        should_trigger = true;
    }

    if (should_trigger) {
        int note = (int)note_num;
        // Retrigger envelopes while maintaining pitch slide
        synth.retriggerNote(note, velocity);
        m_current_note = note;
    } else if (gate <= 0.5f && m_prev_gate > 0.5f) {
        // Gate went low - note off
        if (m_current_note >= 0) {
            synth.noteOn(m_current_note, 0, 0.0);
            m_current_note = -1;
        }
    } else if (gate > 0.5f && note_num != m_prev_note_num) {
        // Note changed while gate is high - slide to new note without re-triggering envelope
        int note = (int)note_num;
        synth.noteOn(note, velocity, 0.0);
        m_current_note = note;
    }

    m_prev_gate = gate;
    m_prev_trig = trig;
    m_prev_note_num = note_num;

    // Update parameters if changed
    float waveform = in0(Waveform);
    if (waveform != m_prev_waveform) {
        synth.setWaveform(waveform);
        m_prev_waveform = waveform;
    }

    float tuning = in0(Tuning);
    if (tuning != m_prev_tuning) {
        synth.setTuning(tuning);
        m_prev_tuning = tuning;
    }

    float cutoff = in0(Cutoff);
    if (cutoff != m_prev_cutoff) {
        synth.setCutoff(cutoff);
        m_prev_cutoff = cutoff;
    }

    float resonance = in0(Resonance);
    if (resonance != m_prev_resonance) {
        synth.setResonance(resonance);
        m_prev_resonance = resonance;
    }

    float envmod = in0(EnvMod);
    if (envmod != m_prev_envmod) {
        synth.setEnvMod(envmod);
        m_prev_envmod = envmod;
    }

    float decay = in0(Decay);
    if (decay != m_prev_decay) {
        synth.setDecay(decay);
        m_prev_decay = decay;
    }

    float accent = in0(Accent);
    if (accent != m_prev_accent) {
        synth.setAccent(accent);
        m_prev_accent = accent;
    }

    float volume = in0(Volume);
    if (volume != m_prev_volume) {
        synth.setVolume(volume);
        m_prev_volume = volume;
    }

    float amp_sustain = in0(AmpSustain);
    if (amp_sustain != m_prev_amp_sustain) {
        synth.setAmpSustain(amp_sustain);
        m_prev_amp_sustain = amp_sustain;
    }

    float amp_decay = in0(AmpDecay);
    if (amp_decay != m_prev_amp_decay) {
        synth.setAmpDecay(amp_decay);
        m_prev_amp_decay = amp_decay;
    }

    float amp_release = in0(AmpRelease);
    if (amp_release != m_prev_amp_release) {
        synth.setAmpRelease(amp_release);
        m_prev_amp_release = amp_release;
    }

    float feedback_hpf = in0(FeedbackHPF);
    if (feedback_hpf != m_prev_feedback_hpf) {
        synth.setFeedbackHighpass(feedback_hpf);
        m_prev_feedback_hpf = feedback_hpf;
    }

    float normal_attack = in0(NormalAttack);
    if (normal_attack != m_prev_normal_attack) {
        synth.setNormalAttack(normal_attack);
        m_prev_normal_attack = normal_attack;
    }

    float accent_attack = in0(AccentAttack);
    if (accent_attack != m_prev_accent_attack) {
        synth.setAccentAttack(accent_attack);
        m_prev_accent_attack = accent_attack;
    }

    float accent_decay = in0(AccentDecay);
    if (accent_decay != m_prev_accent_decay) {
        synth.setAccentDecay(accent_decay);
        m_prev_accent_decay = accent_decay;
    }

    float slide_time = in0(SlideTime);
    if (slide_time != m_prev_slide_time) {
        synth.setSlideTime(slide_time);
        m_prev_slide_time = slide_time;
    }

    // Generate samples
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = static_cast<float>(synth.getSample());
    }
}

} // namespace Open303

PluginLoad(Open303UGens) {
    ft = inTable;
    registerUnit<Open303::Open303>(ft, "Open303", false);
}
