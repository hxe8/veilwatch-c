#ifndef VEILWATCH_TYPES_H
#define VEILWATCH_TYPES_H

#include <stddef.h>

typedef enum output_format {
    OUTPUT_TEXT = 0,
    OUTPUT_JSON = 1
} output_format;

typedef struct event_record {
    long long timestamp_ms;
    char event[32];
} event_record;

typedef struct config {
    double macro_stddev_threshold;
    long long burst_interval_threshold;
    int burst_cluster_min;
    long long repetition_tolerance;
    int high_suspicion_score;
    int medium_suspicion_score;
} config;

typedef struct analysis_result {
    size_t events;
    size_t interval_count;
    double mean_interval_ms;
    double stddev_interval_ms;
    int burst_clusters;
    double repetition_score;
    int suspicion_score;
    char band[16];
} analysis_result;

typedef struct scan_request {
    const char *input_path;
    const char *config_path;
    output_format format;
} scan_request;

#endif
