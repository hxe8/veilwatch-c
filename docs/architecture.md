# Architecture

`veilwatch-c` is shaped as a compact offline telemetry analyzer.

## Flow

1. **CLI** parses mode, input path, output format, and config path.
2. **Config** loads thresholds from a tiny key-value file.
3. **Parser** reads CSV events into a flat array.
4. **Analyzer** computes intervals and extracts timing signals.
5. **Reporter** emits either text or JSON.

## Signals

- **Mean interval**: baseline spacing between events.
- **Interval standard deviation**: low spread can indicate automated cadence.
- **Burst clusters**: compact groups of very short intervals.
- **Repetition score**: measures how often adjacent deltas remain nearly identical.
- **Suspicion score**: bounded score from weighted signals.

## Design choices

- **No dependencies**: easier portability and simpler review.
- **Flat arrays**: predictable memory footprint.
- **Offline only**: safer scope; no invasive integration.
- **Text config**: easy tuning without recompilation.
