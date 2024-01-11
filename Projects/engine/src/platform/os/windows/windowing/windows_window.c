#include "src/platform/platform.h"

#if OS == OS_WINDOWS
#include "src/windowing/window.h"
#include "stdio.h"

void print_platform() {
    printf("PLAFROM WINDOWS");
}

#endif