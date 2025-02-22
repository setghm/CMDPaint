#pragma once

#ifndef _WIN32_WINNT
	#define _WIN32_WINNT	0x0601
#endif

#define UNICODE

#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cinttypes>
#include <cmath>
#include <app/Configuration.hpp>

#define NEW(type, name) \
	type *name = (type *) malloc(sizeof(type)); \
	memset(name, 0, sizeof(type));
