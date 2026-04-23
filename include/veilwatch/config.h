#ifndef VEILWATCH_CONFIG_H
#define VEILWATCH_CONFIG_H

#include "types.h"

int config_default(config *cfg);
int config_load(const char *path, config *cfg);

#endif
