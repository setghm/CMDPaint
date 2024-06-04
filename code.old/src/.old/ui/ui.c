#include "ui.h"

struct UIList {
	UINode *front;
	UINode *back;
} elements;

bool ui_init(void) {
	elements = (UIList *) malloc(sizeof(UIList));
	memset(elements, 0, sizeof(UIList));
	
	if (elements == NULL) {
		return false;
	}
	
	return true;
}

void ui_clean(void) {
	UINode *node = elements->front;
	
	while (node != NULL) {
		UINode *next = node->next;
		node_free(node);
		node = next;
	}
	
	free(elements);
}

bool ui_add_element(UIElement *element, UIClass type) {
	UINode *node;
	
	if (elements == NULL) {
		return false;
	}
	
	node = node_new(element, type);
	
	if (elements->front == NULL) {
		elements->front = node;
	}
	
	if (elements->back != NULL) {
		elements->back->next = node;
	}
	
	elements->back = node;
	
	return true;
}

bool ui_remove_child(int index) {
	int i;
	UINode *node, *prev;
	
	if (elements == NULL) {
		return false;
	}
	
	node = elements->front;
	prev = NULL;
	
	for (i=0; i!=index && node!=NULL; i++) {
		prev = node;
		node = node->next;
	}
	
	if (i != index || node == NULL) {
		return false;
	}
	
	if (node->next != NULL) {
		if (prev != NULL) {
			prev->next = node->next;
		} else {
			elements->front = node->next;
		}
	} else {
		if (prev != NULL) {
			elements->back = prev;
			prev->next = NULL;
		} else {
			elements->front = NULL;
			elements->back = NULL;
		}
	}
	
	node_free(node);
	return true;
}

void ui_input_events(void) {
	
}

void ui_draw(void) {
	UINode *node;
	
	if (elements == NULL) {
		return;
	}
	
	node = elements->front;
	
	while (node) {
		UIElement *element = node->element;
		
		
		
		switch (node->type) {
			case UI_CLASS_LABEL: {
				break;
			}
			case UI_CLASS_BUTTON: {
				break;
			}
		}
		
		node = node->next;
	}
}
