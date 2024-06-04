#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "core/core.h"
#include "controls/controls.h"

void layout_create(void);
bool layout_input(void);
void layout_draw(void);
void layout_cleanup(void);

bool layout_is_closed(void);

#endif //__LAYOUT_H__
