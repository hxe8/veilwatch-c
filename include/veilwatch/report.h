#ifndef VEILWATCH_REPORT_H
#define VEILWATCH_REPORT_H

#include <stdio.h>
#include "types.h"

void write_report(FILE *stream, const analysis_result *result, output_format format);

#endif
