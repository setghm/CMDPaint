#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#define _WIN32_WINNT	0x0601

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

//#include "types.h"
//#include "utils.h"

#ifndef APPNAME
#define APPNAME "Application"
#endif

#define SAFE_RELEASE(o) \
	if (o != NULL) { \
		free(o); \
		o = NULL; \
	}
#define NEW(type, name) \
	type *name = (type *) malloc(sizeof(type)); \
	memset(name, 0, sizeof(type));

#endif
