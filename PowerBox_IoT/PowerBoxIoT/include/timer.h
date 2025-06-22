#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>
#include "global_config.h"


void printLocalTime();
void timeavailable(struct timeval *t);
void readTime();




#endif