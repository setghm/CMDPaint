#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include "types.h"

void error_print(const char *message);

color8_t color_bg(UIElement *element);
color8_t color_fg(UIElement *element);

#endif