# Open303 SuperCollider Plugin

A SuperCollider port of the Open303 TB-303 bass synthesizer.

Original DSP code by RobinSchmidt (MIT License).
Source: https://github.com/RobinSchmidt/Open303/

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

## Usage

See `tests/` for examples.

## License

DSP code: MIT License (RobinSchmidt)
This code: MIT License
