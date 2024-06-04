#ifndef __UI_NODE_H__
#define __UI_NODE_H__

#include "widgets.h"

UINode *node_new(UIElement *element, UIClass type);
void node_free(UINode *node);

#endif
/*
 *	End Of File
 */