#ifndef VEILWATCH_CLI_H
#define VEILWATCH_CLI_H

#include "types.h"

int parse_cli(int argc, char **argv, scan_request *request);
void print_usage(const char *bin_name);

#endif
