#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "veilwatch/config.h"

int config_default(config *cfg) {
    if (cfg == NULL) {
        return -1;
    }
    cfg->macro_stddev_threshold = 5.0;
    cfg->burst_interval_threshold = 18;
    cfg->burst_cluster_min = 3;
    cfg->repetition_tolerance = 3;
    cfg->high_suspicion_score = 75;
    cfg->medium_suspicion_score = 45;
    return 0;
}

static void apply_pair(config *cfg, const char *key, const char *value) {
    if (strcmp(key, "macro_stddev_threshold") == 0) {
        cfg->macro_stddev_threshold = atof(value);
    } else if (strcmp(key, "burst_interval_threshold") == 0) {
        cfg->burst_interval_threshold = atoll(value);
    } else if (strcmp(key, "burst_cluster_min") == 0) {
        cfg->burst_cluster_min = atoi(value);
    } else if (strcmp(key, "repetition_tolerance") == 0) {
        cfg->repetition_tolerance = atoll(value);
    } else if (strcmp(key, "high_suspicion_score") == 0) {
        cfg->high_suspicion_score = atoi(value);
    } else if (strcmp(key, "medium_suspicion_score") == 0) {
        cfg->medium_suspicion_score = atoi(value);
    }
}

int config_load(const char *path, config *cfg) {
    FILE *fp;
    char line[256];

    if (config_default(cfg) != 0) {
        return -1;
    }
    if (path == NULL) {
        return 0;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *eq;
        char *key;
        char *value;

        if (line[0] == '#' || line[0] == '\n') {
            continue;
        }

        eq = strchr(line, '=');
        if (eq == NULL) {
            continue;
        }

        *eq = '\0';
        key = line;
        value = eq + 1;
        value[strcspn(value, "\r\n")] = '\0';
        apply_pair(cfg, key, value);
    }

    fclose(fp);
    return 0;
}
