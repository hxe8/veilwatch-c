#include <stdio.h>
#include "veilwatch/report.h"

void write_report(FILE *stream, const analysis_result *result, output_format format) {
    if (format == OUTPUT_JSON) {
        fprintf(stream,
                "{\n"
                "  \"events\": %zu,\n"
                "  \"interval_count\": %zu,\n"
                "  \"mean_interval_ms\": %.2f,\n"
                "  \"stddev_interval_ms\": %.2f,\n"
                "  \"burst_clusters\": %d,\n"
                "  \"repetition_score\": %.2f,\n"
                "  \"suspicion_score\": %d,\n"
                "  \"band\": \"%s\"\n"
                "}\n",
                result->events,
                result->interval_count,
                result->mean_interval_ms,
                result->stddev_interval_ms,
                result->burst_clusters,
                result->repetition_score,
                result->suspicion_score,
                result->band);
        return;
    }

    fprintf(stream,
            "veilwatch report\n"
            "----------------\n"
            "events:            %zu\n"
            "intervals:         %zu\n"
            "mean interval ms:  %.2f\n"
            "stddev interval:   %.2f\n"
            "burst clusters:    %d\n"
            "repetition score:  %.2f\n"
            "suspicion score:   %d\n"
            "band:              %s\n",
            result->events,
            result->interval_count,
            result->mean_interval_ms,
            result->stddev_interval_ms,
            result->burst_clusters,
            result->repetition_score,
            result->suspicion_score,
            result->band);
}
