#include "App.h"

int main() {
	if (!App::init()) {
		return EXIT_FAILURE;
	}

	return App::run();
}