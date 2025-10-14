Open303 : UGen {
    *ar { |gate=0, trig=0, noteNum=60, velocity=0.5, waveform=0.5, tuning=440, cutoff=1000, resonance=80, envMod=50, decay=1000, accent=50, volume=(-12), ampSustain=0, ampDecay=1230, ampRelease=1, feedbackHPF=150, normalAttack=3, accentAttack=3, accentDecay=200, slideTime=60|
        ^this.multiNew('audio', gate, trig, noteNum, velocity, waveform, tuning, cutoff, resonance, envMod, decay, accent, volume, ampSustain, ampDecay, ampRelease, feedbackHPF, normalAttack, accentAttack, accentDecay, slideTime);
    }

    *kr { |gate=0, trig=0, noteNum=60, velocity=0.5, waveform=0.5, tuning=440, cutoff=1000, resonance=80, envMod=50, decay=1000, accent=50, volume=(-12), ampSustain=0, ampDecay=1230, ampRelease=1, feedbackHPF=150, normalAttack=3, accentAttack=3, accentDecay=200, slideTime=60|
        ^this.multiNew('control', gate, trig, noteNum, velocity, waveform, tuning, cutoff, resonance, envMod, decay, accent, volume, ampSustain, ampDecay, ampRelease, feedbackHPF, normalAttack, accentAttack, accentDecay, slideTime);
    }

    checkInputs {
        ^this.checkValidInputs;
    }
}
