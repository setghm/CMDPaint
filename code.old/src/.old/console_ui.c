#include "console.h"

void ui_element_set(UIElement *element, int x, int y) {
	element->color = 0x70;
	element->size.width = 1;
	element->size.height = 1;
	element->position.x = x;
	element->position.y = y;
}

void ui_label_set(UILabel *label, const wchar_t *text, int x, int y) {
	label->text = wcsdup(text);
	ui_element_set(UI_LABEL(label), x, y);
	ui_set_size(UI_LABEL(label), wcslen(text), NO_CHANGE);
}

UILabel *ui_label_new(const wchar_t *text, int x, int y) {
	NEW(UILabel, label);
	ui_label_set(label, text, x, y);
	return label;
}

UILabel *ui_label_new_ascii(const char *text, int x, int y) {
	wchar_t *text_wide;
	UILabel *label = NULL;
	
	text_wide = (wchar_t *) calloc(
		strlen(text) + 1,
		sizeof(wchar_t));
	
	mbstowcs(text_wide, text, strlen(text));
	
	label = ui_label_new(text_wide, x, y);
	free(text_wide);
	
	return label;
}

void ui_label_destroy(UILabel *label) {
	if (label) {
		SAFE_RELEASE(label->text);
		free(label);
		label = NULL;
	}
}

UIButton *ui_button_with_label(	const wchar_t *text,
								int x,
								int y)
{
	NEW(UIButton, button);
	ui_label_set(&button->super, text, x, y);
	return button;
}

void ui_button_set_styles(	UIButton *button,
							color8_t normal,
							color8_t active,
							int padding_x,
							int padding_y)
{
	button->color_normal = normal;
	button->color_active = active;
	button->padding_x = padding_x;
	button->padding_y = padding_y;
	
	ui_set_size(UI_BUTTON(button),
				ui_get_width(UI_BUTTON(button)) +
					button->padding_x * 2,
				ui_get_height(UI_BUTTON(button)) +
					button->padding_y * 2);
	
	ui_button_update_color(button);
}

void ui_button_update_color(UIButton *button) {
	if (button->active) {
		button->super.super.color = button->color_active;
	} else {
		button->super.super.color = button->color_normal;
	}
}

bool ui_button_clicked(UIButton *button, int x, int y) {
	button->active = (
		(x >= button->super.super.position.x &&
		 x <= button->super.super.position.x +
			   button->super.super.size.width - 1) &&
		(y >= button->super.super.position.y &&
		 y <= button->super.super.position.y +
			   button->super.super.size.height - 1));

	ui_button_update_color(button);
	
	return button->active;
}

void ui_button_unactive(UIButton *button) {
	button->active = false;
	ui_button_update_color(button);
}

void ui_button_destroy(UIButton *button) {
	if (button) {
		SAFE_RELEASE(button->super.text);
		free(button);
		button = NULL;
	}
}

int ui_get_pos_x(UIElement *element) {
	return element->position.x;
}

int ui_get_pos_y(UIElement *element) {
	return element->position.y;
}

int ui_get_width(UIElement *element) {
	return element->size.width;
}

int ui_get_height(UIElement *element) {
	return element->size.height;
}

color8_t ui_get_color(UIElement *element) {
	return element->color;
}

void ui_set_color(UIElement *element, color8_t color) {
	if (color != NO_CHANGE) element->color = color;
}

void ui_set_position(UIElement *element, int x, int y) {
	if (x != NO_CHANGE) element->position.x = x;
	if (y != NO_CHANGE) element->position.x = y;
}

void ui_set_size(UIElement *element, int w, int h) {
	if (w != NO_CHANGE) element->size.width = w;
	if (h != NO_CHANGE) element->size.height = h;
}
