// Open303 Interactive Test
// Run this in the SuperCollider IDE for an interactive acid bassline demo

(
s.waitForBoot({

    // Define the synth
    SynthDef(\acid303, {
        var sig, env;
        sig = Open303.ar(
            gate: \gate.kr(1),
            noteNum: \note.kr(60),
            velocity: \velocity.kr(0.5),
            waveform: \waveform.kr(0.2),
            tuning: \tuning.kr(440),
            cutoff: \cutoff.kr(1000),
            resonance: \resonance.kr(85),
            envMod: \envMod.kr(60),
            decay: \decay.kr(800),
            accent: \accent.kr(70),
            volume: \volume.kr(-6),
            ampSustain: \ampSustain.kr(0),
            ampDecay: \ampDecay.kr(1230),
            ampRelease: \ampRelease.kr(1),
            feedbackHPF: \feedbackHPF.kr(150),
            normalAttack: \normalAttack.kr(3),
            accentAttack: \accentAttack.kr(3),
            accentDecay: \accentDecay.kr(200),
            slideTime: \slideTime.kr(60)
        );

        // Simple envelope for note duration
        env = EnvGen.kr(Env.asr(0.01, 1, 0.1), \gate.kr(1), doneAction: 2);
        sig = sig * env;

        Out.ar(\out.kr(0), sig ! 2);
    }).add;

    s.sync;

    // Play a test pattern
    Pdef(\acidTest,
        Pbind(
            \instrument, \acid303,
            \dur, 0.25,
            \note, Pseq([36, 48, 43, 41, 36, 48, 43, 41], inf),
            \velocity, Prand([0.5, 0.9], inf), // some accents (>= 0.79 triggers accent)
            \cutoff, Pexprand(600, 2500, inf),
            \resonance, 88,
            \envMod, Pwhite(50, 80, inf),
            \decay, 600,
            \waveform, 0.2,
            \legato, Pwrand([0.5, 1.2], [0.7, 0.3], inf) // some slides
        )
    ).play;

    "Open303 test pattern playing!".postln;
    "".postln;
    "To stop: Pdef(\\acidTest).stop;".postln;
    "".postln;
    "Try the other examples below by selecting and evaluating them:".postln;
});
)

// === STOP PATTERN ===
// Evaluate this to stop:
Pdef(\acidTest).stop;

// === EXAMPLE 1: Classic Acid ===
(
Pdef(\acidTest,
    Pbind(
        \instrument, \acid303,
        \dur, 0.125,
        \note, Pseq([24, 36, 31, 29], inf) + Prand([0, 12], inf),
        \velocity, Prand([0.4, 0.5, 0.95], inf),
        \cutoff, Pexprand(400, 3000, inf),
        \resonance, 92,
        \envMod, 75,
        \decay, 400,
        \waveform, 0.1,
        \legato, 0.8
    )
).play;
)

// === EXAMPLE 2: Deep Bass ===
(
Pdef(\acidTest,
    Pbind(
        \instrument, \acid303,
        \dur, 0.5,
        \note, Pseq([24, 24, 36, 31], inf),
        \velocity, 0.6,
        \cutoff, 600,
        \resonance, 75,
        \envMod, 40,
        \decay, 1200,
        \waveform, 0.0, // pure saw
        \legato, 0.9
    )
).play;
)

// === EXAMPLE 3: Squelchy ===
(
Pdef(\acidTest,
    Pbind(
        \instrument, \acid303,
        \dur, Prand([0.125, 0.25, 0.125], inf),
        \note, Pseq([36, 48, 43, 48, 41, 48, 43, 36], inf),
        \velocity, Pseq([0.95, 0.5, 0.5, 0.95], inf), // accented pattern
        \cutoff, Pwhite(800, 1800, inf),
        \resonance, 95,
        \envMod, 85,
        \decay, 300,
        \waveform, 0.7, // more square
        \legato, Prand([0.4, 1.5], inf)
    )
).play;
)
