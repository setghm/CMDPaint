#include "ui_button.c"

UIButton *button_new(const wchar_t *text, int x, int y) {
	UIButton *button = (UIButton *) malloc(sizeof(UIButton));
	memset(button, 0, sizeof(UIButton));
	
	button->super.text = wcsdup(text);
	button->super.super.position.x = x;
	button->super.super.position.y = y;
	
	button->super.super.size.width = wcslen(text) + 2;
	button->super.super.size.height = 0;
	
	return button;
}

void button_free(UIButton *button) {
	free(button->super.text);
	free(button);
	button = NULL;
}

void button_set_color(UIButton *button, color8_t text_color, color8_t bg_color) {
	button->normal_color = text_color | (bg_color << 4);
	button->active_color = bg_color | (text_color << 4);
}
