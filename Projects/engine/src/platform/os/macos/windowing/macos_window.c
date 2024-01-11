#include "src/platform/platform.h"

#if PLATFORM == PLATFORM_MACOS
#include "src/windowing/window.h"
#include "stdio.h"

void print_platform() {
    printf("PLAFROM MACOS");
}

#endif