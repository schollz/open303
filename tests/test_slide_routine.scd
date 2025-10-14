// Open303 Sliding Test - Using t_trig with Routine
// Tests sliding behavior on a synth that doesn't get released
// The synth remains active and receives new note triggers

(
s.waitForBoot({

    // Define the synth with t_trig instead of gate
    SynthDef(\acid303_slide, {
		arg t_trig;
        var sig, env;
        sig =  Open303.ar(
            gate: \gate.kr(1),
			trig: t_trig,
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
            slideTime: \slideTime.kr(6000)
        );
        // No doneAction - synth stays alive
        Out.ar(\out.kr(0), sig ! 2);
    }).add;

    s.sync;

    // Create the synth
    ~acidSynth = Synth(\acid303_slide);

    s.sync;

    // Start a routine that triggers new notes every 0.125 seconds
    ~slideRoutine = Routine({
        var notes = [36, 48, 43, 41, 36, 48, 43, 41,
                     24, 36, 31, 29, 36, 48, 52, 48];
        var velocities = [0.5];
        var noteIndex = 0;

        inf.do {
            // Set the new note and velocity
            ~acidSynth.set(
				\gate, 1,
                \note, notes.wrapAt(noteIndex).postln,
                \velocity, velocities.wrapAt(noteIndex),
                \t_trig, 1  // Trigger the envelope
            );

            noteIndex = noteIndex + 1;

            // Wait 0.125 seconds before next trigger
			(0.125/2).wait;
			// set gate to 0
			// ~acidSynth.set(\gate,0);
			(0.125/2).wait;

        };
    });

    // Play the routine
    ~slideRoutine.play;

    "".postln;
    "Open303 sliding test running!".postln;
    "The synth stays active and slides between notes.".postln;
    "".postln;
    "To stop: ~slideRoutine.stop; ~acidSynth.free;".postln;
    "".postln;
});
)

// === STOP THE TEST ===
// Evaluate this to stop:
(
~slideRoutine.stop;
~acidSynth.free;
"Stopped.".postln;
)

