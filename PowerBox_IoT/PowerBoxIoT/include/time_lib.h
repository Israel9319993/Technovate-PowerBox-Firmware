#ifndef TIME_LIB_H
#define TIME_LIB_H
#include <Arduino.h>
#include "global_config.h"

class Time
{
public:
    Time();
    void ReadTime();
    void Begin();
    static void PrintLocalTime();

private:
    static void TimeAvailable(struct timeval *t);
};

#endif