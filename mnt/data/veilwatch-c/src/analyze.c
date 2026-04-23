#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "veilwatch/analyze.h"

static double compute_mean(const long long *values, size_t count) {
    double sum = 0.0;
    size_t i;
    for (i = 0; i < count; ++i) {
        sum += (double)values[i];
    }
    return count == 0 ? 0.0 : sum / (double)count;
}

static double compute_stddev(const long long *values, size_t count, double mean) {
    double acc = 0.0;
    size_t i;
    if (count == 0) {
        return 0.0;
    }
    for (i = 0; i < count; ++i) {
        double delta = (double)values[i] - mean;
        acc += delta * delta;
    }
    return sqrt(acc / (double)count);
}

static int count_burst_clusters(const long long *intervals, size_t count, long long threshold, int cluster_min) {
    int clusters = 0;
    int run = 0;
    size_t i;
    for (i = 0; i < count; ++i) {
        if (intervals[i] <= threshold) {
            run++;
        } else {
            if (run >= cluster_min) {
                clusters++;
            }
            run = 0;
        }
    }
    if (run >= cluster_min) {
        clusters++;
    }
    return clusters;
}

static double compute_repetition_score(const long long *intervals, size_t count, long long tolerance) {
    size_t i;
    size_t repeated = 0;
    if (count < 2) {
        return 0.0;
    }
    for (i = 1; i < count; ++i) {
        long long diff = intervals[i] - intervals[i - 1];
        if (diff < 0) {
            diff = -diff;
        }
        if (diff <= tolerance) {
            repeated++;
        }
    }
    return (double)repeated / (double)(count - 1);
}

static int clamp_score(int score) {
    if (score < 0) {
        return 0;
    }
    if (score > 100) {
        return 100;
    }
    return score;
}

int analyze_events(const event_record *events, size_t count, const config *cfg, analysis_result *out) {
    long long *intervals;
    double mean;
    double stddev;
    int bursts;
    double repetition;
    int score = 0;
    size_t i;

    if (events == NULL || cfg == NULL || out == NULL || count < 2) {
        return -1;
    }

    intervals = (long long *)calloc(count - 1, sizeof(long long));
    if (intervals == NULL) {
        return -1;
    }

    for (i = 1; i < count; ++i) {
        intervals[i - 1] = events[i].timestamp_ms - events[i - 1].timestamp_ms;
        if (intervals[i - 1] < 0) {
            free(intervals);
            return -1;
        }
    }

    mean = compute_mean(intervals, count - 1);
    stddev = compute_stddev(intervals, count - 1, mean);
    bursts = count_burst_clusters(intervals, count - 1, cfg->burst_interval_threshold, cfg->burst_cluster_min);
    repetition = compute_repetition_score(intervals, count - 1, cfg->repetition_tolerance);

    if (stddev <= cfg->macro_stddev_threshold) {
        score += 35;
    }
    if (bursts > 0) {
        score += bursts * 12;
    }
    if (repetition >= 0.80) {
        score += 30;
    } else if (repetition >= 0.55) {
        score += 18;
    }
    if (mean > 0.0 && mean < 90.0) {
        score += 10;
    }

    memset(out, 0, sizeof(*out));
    out->events = count;
    out->interval_count = count - 1;
    out->mean_interval_ms = mean;
    out->stddev_interval_ms = stddev;
    out->burst_clusters = bursts;
    out->repetition_score = repetition;
    out->suspicion_score = clamp_score(score);

    if (out->suspicion_score >= cfg->high_suspicion_score) {
        strncpy(out->band, "high", sizeof(out->band) - 1);
    } else if (out->suspicion_score >= cfg->medium_suspicion_score) {
        strncpy(out->band, "medium", sizeof(out->band) - 1);
    } else {
        strncpy(out->band, "low", sizeof(out->band) - 1);
    }

    free(intervals);
    return 0;
}
