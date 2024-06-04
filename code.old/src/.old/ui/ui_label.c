#include "ui_label.h"

UILabel *label_new(const wchar_t *text, int x, int y) {
	UILabel *label = (UILabel *) malloc(sizeof(UILabel));
	memset(label, 0, sizeof(UILabel));
	
	label->text = wcsdup(text);
	label->super.position.x = x;
	label->super.position.y = y;
	
	label->super.size.width = wcslen(text);
	label->super.size.height = 1;
	
	return label;
}

void label_free(UILabel *label) {
	SAFE_FREE(label->text);
	free(label);
	label = NULL;
}

void label_change_text(UILabel *label, const wchar_t *text) {
	SAFE_FREE(label->text);
	label->text = wcsdup(text);
	label->super.size.width = wcslen(text);
}
