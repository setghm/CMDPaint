#include "app/App.hpp"

int main() {
	if (!App::init()) {
		return EXIT_FAILURE;
	}

	return App::run();
}