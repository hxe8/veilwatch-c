#ifndef VEILWATCH_ANALYZE_H
#define VEILWATCH_ANALYZE_H

#include "types.h"

int analyze_events(const event_record *events, size_t count, const config *cfg, analysis_result *out);

#endif
