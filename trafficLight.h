#ifndef TRAFFIC_LIGHT
#define TRAFFIC_LIGHT

//TODO: Remove
#include <stdio.h>

#include <sys/time.h>
#include <stdbool.h>

#include "state.h"

// MILLSECOND

extern long long timeToggleDeley;
extern const long long timeBlinkDeley;

// BUTTON

extern long long lastTimePushButton; 
extern const long long needDurationPush;
extern bool isPush;

// MODES

extern bool isForceGreen;
extern bool isRedShort;
extern ColorNow stateNow;

long long timeInMilliseconds(void);

void checkButton();

void diodWork(int pin, bool isBlinking, long long nextTimeDiodToggle);

int trafficLight(void);

#endif