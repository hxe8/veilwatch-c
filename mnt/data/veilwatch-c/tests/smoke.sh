#!/usr/bin/env sh
set -eu
./bin/veilwatch scan --input sample_data/clean_clicks.csv --format text >/tmp/veilwatch_clean.txt
grep -q "band:" /tmp/veilwatch_clean.txt
./bin/veilwatch scan --input sample_data/suspicious_clicks.csv --format json >/tmp/veilwatch_suspicious.json
grep -q '"suspicion_score"' /tmp/veilwatch_suspicious.json
echo "smoke: ok"
