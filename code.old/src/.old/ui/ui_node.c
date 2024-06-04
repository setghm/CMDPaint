#include "ui_node.h"
#include "ui_button.h"
#include "ui_label.h"

UINode *node_new(UIElement *element, UIClass type) {
	UINode *node = (UINode *) malloc(sizeof(UINode));
	
	node->type = type;
	node->element = element;
	
	return node;
}

void node_free(UINode *node) {
	switch (node->type) {
		case UI_CLASS_ELEMENT:
			free(node->element);
			break;
		case UI_CLASS_LABEL:
			label_free((UILabel *) node->element);
			break;
		case UI_CLASS_BUTTON:
			button_free((UIButton *) node->element);
			break;
	}
	
	free(node);
	node = NULL;
}
