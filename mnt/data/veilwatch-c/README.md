# veilwatch-c

A low-noise input integrity watcher in C for timing anomaly detection, burst-pattern analysis, and anti-macro style telemetry triage.

> Small surface. Cold output. Built for post-match review pipelines and internal gameplay telemetry checks.

## Why

Competitive titles often need a lightweight way to inspect raw input event logs without dragging in a heavy runtime. `veilwatch-c` takes newline-delimited input events and produces a compact suspicion report based on interval variance, burst density, repetition, and unrealistic timing clusters.

This repository is intentionally compact. The emphasis is on repo shape, operational clarity, and defensive analysis.

## Features

- Fast CSV ingestion for input event telemetry
- Rolling interval statistics
- Burst cluster detection
- Repetition score for near-identical spacing
- Suspicion scoring with threshold bands
- JSON and text report output
- Sample dataset included
- Simple offline workflow

## Repository shape

```text
veilwatch-c/
├─ include/veilwatch/
├─ src/
├─ tests/
├─ docs/
├─ configs/
├─ sample_data/
├─ Makefile
└─ README.md
```

## Build

```bash
make
```

## Run

```bash
./bin/veilwatch scan --input sample_data/suspicious_clicks.csv --config configs/default.conf --format json
./bin/veilwatch scan --input sample_data/clean_clicks.csv --format text
```

## Event format

CSV with header:

```csv
index,timestamp_ms,event
0,0,mouse1_down
1,117,mouse1_up
2,251,mouse1_down
```

Only timestamp deltas and event stream shape are used.

## Sample output

```json
{
  "events": 32,
  "interval_count": 31,
  "mean_interval_ms": 79.29,
  "stddev_interval_ms": 1.66,
  "burst_clusters": 3,
  "repetition_score": 0.93,
  "suspicion_score": 84,
  "band": "high"
}
```

## Architecture

See [`docs/architecture.md`](docs/architecture.md).

## Operational notes

- Offline analysis only
- No kernel hooks
- No process tampering
- No input interception
- Intended for telemetry review and anti-macro style signal triage

## Contact

Discord: `hxe8`

## License

MIT
