#ifndef STATE
#define STATE

typedef enum ColorNow {
    RED             = 1 << 0,
    GREEN           = 1 << 1,
    BLINK_GREEN     = 1 << 2,
    YELLOW          = 1 << 3
} ColorNow;

#endif