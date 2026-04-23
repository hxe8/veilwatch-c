#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "veilwatch/parser.h"

int parse_events_csv(const char *path, event_record **events_out, size_t *count_out) {
    FILE *fp;
    char line[256];
    size_t cap = 64;
    size_t count = 0;
    event_record *events;

    if (events_out == NULL || count_out == NULL || path == NULL) {
        return -1;
    }

    fp = fopen(path, "r");
    if (fp == NULL) {
        return -1;
    }

    events = (event_record *)calloc(cap, sizeof(event_record));
    if (events == NULL) {
        fclose(fp);
        return -1;
    }

    if (fgets(line, sizeof(line), fp) == NULL) {
        free(events);
        fclose(fp);
        return -1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *token;
        char *cursor = line;
        long long ts = 0;
        char evt[32] = {0};
        int field = 0;

        while ((token = strtok(field == 0 ? cursor : NULL, ",")) != NULL) {
            if (field == 1) {
                ts = atoll(token);
            } else if (field == 2) {
                strncpy(evt, token, sizeof(evt) - 1);
                evt[strcspn(evt, "\r\n")] = '\0';
            }
            field++;
        }

        if (field < 3) {
            continue;
        }

        if (count == cap) {
            event_record *grown;
            cap *= 2;
            grown = (event_record *)realloc(events, cap * sizeof(event_record));
            if (grown == NULL) {
                free(events);
                fclose(fp);
                return -1;
            }
            events = grown;
        }

        events[count].timestamp_ms = ts;
        strncpy(events[count].event, evt, sizeof(events[count].event) - 1);
        events[count].event[sizeof(events[count].event) - 1] = '\0';
        count++;
    }

    fclose(fp);
    *events_out = events;
    *count_out = count;
    return 0;
}

void free_events(event_record *events) {
    free(events);
}
