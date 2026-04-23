#include <stdio.h>
#include <stdlib.h>
#include "veilwatch/cli.h"
#include "veilwatch/config.h"
#include "veilwatch/parser.h"
#include "veilwatch/analyze.h"
#include "veilwatch/report.h"

int main(int argc, char **argv) {
    scan_request req;
    config cfg;
    event_record *events = NULL;
    size_t count = 0;
    analysis_result result;

    if (parse_cli(argc, argv, &req) != 0) {
        print_usage(argv[0]);
        return 1;
    }

    if (config_load(req.config_path, &cfg) != 0) {
        fprintf(stderr, "veilwatch: failed to load config\n");
        return 1;
    }

    if (parse_events_csv(req.input_path, &events, &count) != 0) {
        fprintf(stderr, "veilwatch: failed to parse input\n");
        return 1;
    }

    if (analyze_events(events, count, &cfg, &result) != 0) {
        fprintf(stderr, "veilwatch: analysis failed\n");
        free_events(events);
        return 1;
    }

    write_report(stdout, &result, req.format);
    free_events(events);
    return 0;
}
