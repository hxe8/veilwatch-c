#include <stdio.h>
#include <string.h>
#include "veilwatch/cli.h"

void print_usage(const char *bin_name) {
    fprintf(stderr,
            "usage: %s scan --input <file> [--config <file>] [--format text|json]\n",
            bin_name);
}

int parse_cli(int argc, char **argv, scan_request *request) {
    int i;
    if (argc < 4 || strcmp(argv[1], "scan") != 0) {
        return -1;
    }

    request->input_path = NULL;
    request->config_path = NULL;
    request->format = OUTPUT_TEXT;

    for (i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "--input") == 0 && i + 1 < argc) {
            request->input_path = argv[++i];
        } else if (strcmp(argv[i], "--config") == 0 && i + 1 < argc) {
            request->config_path = argv[++i];
        } else if (strcmp(argv[i], "--format") == 0 && i + 1 < argc) {
            const char *value = argv[++i];
            if (strcmp(value, "json") == 0) {
                request->format = OUTPUT_JSON;
            } else {
                request->format = OUTPUT_TEXT;
            }
        } else {
            return -1;
        }
    }

    return request->input_path == NULL ? -1 : 0;
}
