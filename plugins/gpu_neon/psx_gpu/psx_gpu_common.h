#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(PLATFORM_PC)||defined(PLATFORM_XBOX)
#else
#include <sys/time.h>
#endif 
#include "vector_types.h"
#include "psx_gpu.h"

#define unlikely(x) __builtin_expect((x), 0)

#endif

