#pragma once

void platform_init();
void rapi_init();

// operating system
#define OS_LINUX 0x1b4
#define OS_WINDOWS 0x1ef
#define OS_MACOS 0x197

#define OS OS_LINUX
// rendering API

#if OS == OS_LINUX
#define RAPI_OPENGL 0x140
#define RAPI_VULKAN 0x14c
#endif

#if OS == OS_WINDOWS
#define RAPI_OPENGL 0x140
#define RAPI_VULKAN 0x14c
#define RAPI_DIRECTX 0x15e
#endif

#if OS == OS_MACOS
#define RAPI_METAL 0x11e
#endif

#define RAPI RAPI_OPENGL