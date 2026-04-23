# ADR-0001: Offline scope

## Context
The repository should remain small, reviewable, and suitable for internal telemetry triage.

## Decision
Keep the system offline and file-driven.

## Consequences
- Lower operational risk
- No invasive runtime hooks
- Easier to test with fixture data
