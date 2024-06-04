#pragma once

#include "components.hpp"
#include "Configuration.hpp"

/* Private singleton. */
class App {
private:
	static App* instance;
public:
	static bool init(void);
	static int run(void);
private:
	// App components.
	Canvas* canvas;
	UserInterface* ui;
	FileManager* fileManager;
	
	// Life cycle fields.
	bool running;

	// Constructor.
	App();
	// Destructor.
	~App();
};

