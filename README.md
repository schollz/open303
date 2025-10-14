# Open303 SuperCollider Plugin

A SuperCollider port of the Open303 TB-303 bass synthesizer.

Original DSP code by RobinSchmidt (MIT License).
Source: https://github.com/RobinSchmidt/RS-MET

## Building

Requires CMake and SuperCollider source code.

```bash
make              # Build plugin
make install      # Install to Extensions directory
make uninstall    # Remove from Extensions directory
```

Default SuperCollider source path: `~/Documents/supercollider`

Override with: `make SC_PATH=/path/to/supercollider`

## Testing

```bash
sclang tests/test_load.scd
```

## Parameters

- gate, noteNum, velocity
- waveform (0-1), tuning (Hz)
- cutoff (Hz), resonance (0-100), envMod (0-100)
- decay (ms), accent (0-100), volume (dB)
- ampSustain (dB), ampDecay (ms), ampRelease (ms)
- feedbackHPF (Hz)
- normalAttack (ms), accentAttack (ms), accentDecay (ms)
- slideTime (ms)

## Usage

```supercollider
Open303.ar(
    gate: gate,
    noteNum: noteNum,
    velocity: velocity,
    cutoff: cutoff,
    resonance: resonance
)
```

See `tests/test_interactive.scd` for examples.

## License

DSP code: MIT License (RobinSchmidt)
SuperCollider wrapper: Same as SuperCollider project
