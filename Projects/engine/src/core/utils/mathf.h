#pragma once
#include "engine_api.h"
#include <math.h>

HEADER_DEF float radians(float degrees) { degrees * 0.01745329251994329576923690768489; }
HEADER_DEF float degrees(float radians) { radians * 57.2957795130823208767981548141050; }