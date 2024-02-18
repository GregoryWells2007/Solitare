#pragma once
#include "src/platform/platform.h"
#include "src/types/boolean.h"

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"

#include <sys/time.h>  

#define HEADER_DEF __attribute__((weak))
HEADER_DEF int min (int v1, int v2) {
    return (v1 > v2) ? v1 : v2;
}