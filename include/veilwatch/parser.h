#ifndef VEILWATCH_PARSER_H
#define VEILWATCH_PARSER_H

#include "types.h"

int parse_events_csv(const char *path, event_record **events_out, size_t *count_out);
void free_events(event_record *events);

#endif
