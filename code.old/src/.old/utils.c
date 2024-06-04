#include "utils.h"

void error_print(const char *message) {
	fprintf(stderr, "[ERROR] %s\n", message);
}

color8_t color_bg(UIElement *element) {
	return element->color & 0xF0;
}

color8_t color_fg(UIElement *element) {
	return element->color & 0x0F;
}
