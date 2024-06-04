#pragma once

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT	0x0601
#endif

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cinttypes>
#include "Configuration.hpp"

//#include "types.h"
//#include "utils.h"

#define SAFE_RELEASE(o) \
	if (o != NULL) { \
		free(o); \
		o = NULL; \
	}
#define NEW(type, name) \
	type *name = (type *) malloc(sizeof(type)); \
	memset(name, 0, sizeof(type));
