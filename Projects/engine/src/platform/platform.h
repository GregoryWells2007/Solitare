#pragma once

// operating system
#define OS_LINUX 0x1b4
#define OS_WINDOWS 0x1ef
#define OS_MACOS 0x197

// rendering API

#define RAPI_OPENGL 0x140
#define RAPI_VULKAN 0x14c
#define RAPI_METAL 0x11e
#define RAPI_DIRECTX 0x15e

// build platforms
#define OS OS_LINUX
#define RAPI RAPI_OPENGL