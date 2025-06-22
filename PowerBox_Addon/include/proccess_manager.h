#ifndef PROCCESS_MANAGER_H
#define PROCCESS_MANAGER_H

#include "global_config.h"
#include "device_setup.h"

void BLEPowerBoxSend(void *declaration);
extern TaskHandle_t bleTaskHandle;
void processInit();

#endif