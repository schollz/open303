// Open303 Plugin Load Test
// This script verifies that the Open303 plugin loads correctly

(
// Test that the class exists
if(Open303.notNil, {
    "✓ Open303 class found".postln;
}, {
    "✗ ERROR: Open303 class not found".postln;
    1.exit;
});

// Boot server and test plugin
s.waitForBoot({
    var testPassed = true;

    "✓ Server booted".postln;

    // Try to create a simple SynthDef
    try {
        SynthDef(\open303_test, {
            var sig = Open303.ar(
                gate: 1,
                noteNum: 60,
                velocity: 0.5,
                waveform: 0.2,
                cutoff: 1000,
                resonance: 85
            );
            Out.ar(0, sig ! 2);
        }).add;

        s.sync;
        "✓ SynthDef compiled successfully".postln;

    } {
        "✗ ERROR: Failed to compile SynthDef".postln;
        testPassed = false;
    };

    // Try to instantiate the synth
    if(testPassed, {
        try {
            var testSynth = Synth(\open303_test);
            0.5.wait;
            testSynth.free;
            "✓ Synth instantiated and freed successfully".postln;
            "".postln;
            "=================================".postln;
            "✓ All tests passed!".postln;
            "Open303 plugin is working correctly.".postln;
            "=================================".postln;
        } {
            "✗ ERROR: Failed to instantiate synth".postln;
            testPassed = false;
        };
    });

    // Exit
    1.wait;
    0.exit;
});
)
