#include "App.hpp"
#include <core/core.hpp>

App* App::instance = new App();

App::App() {
	// Create the canvas component.
	canvas = new Canvas(
		Configuration::defaultImageWidth,
		Configuration::defaultImageHeight
	);

	// Create the file manager component.
	fileManager = new FileManager(canvas);

	// Create the UI component.
	ui = new UserInterface(
		// On File menu option selected callback.
		[=](FileMenuOption option) {
			switch (option) {
				case FileMenuOption::New: {
					fileManager->create();
					break;
				}
				case FileMenuOption::Open: {
					fileManager->open();
					break;
				}
				case FileMenuOption::Save: {
					fileManager->save();
					break;
				}
				case FileMenuOption::SaveAs: {
					fileManager->save(true);
					break;
				}
				case FileMenuOption::Exit: {
					if (fileManager->exit()) {
						running = false;
					}
					break;
				}
			}
		},
		// On Canvas undo and redo.
		[=](void) { canvas->undo(); },
		[=](void) { canvas->redo(); },
		// On Tool selected callback.
		[=](CanvasTools tool) { canvas->setTool(tool); },
		// On Grid toggled callback.
		[=](void) { canvas->toggleGrid(); },
		// On Color selected from the color palette.
		[=](CanvasColor color) { canvas->setFrontColor(color); },
		[=](CanvasColor color) { canvas->setBackColor(color); },
		[=](void) {
			// Swap the canvas colors.
			CanvasColor front_color = canvas->getFrontColor();
			canvas->setFrontColor(canvas->getBackColor());
			canvas->setBackColor(front_color);
		},
		// On Canvas resize callback.
		[=](int width, int height) { canvas->resize(width, height); }
	);

	// Set the canvas update callbacks.
	canvas->setOnFrontColorChanged([=](CanvasColor color) {
		ui->whenFrontColorChanges(color);
	});
	canvas->setOnBackColorChanged([=](CanvasColor color) {
		ui->whenBackColorChanges(color);
	});
	canvas->setOnUndo([=](bool begin_reached) {
		ui->whenUndo(begin_reached);
	});
	canvas->setOnRedo([=](bool end_reached) {
		ui->whenRedo(end_reached);
	});
	canvas->setOnActionRecorded([=](void) {
		ui->whenActionRecorded();
	});
	canvas->setOnActionsForget([=](void) {
		ui->whenActionsForget();
	});
	canvas->setOnChangesMade([=](void) {
		fileManager->whenChangesMade();
	});
	fileManager->setOnFileOpened([=](int width, int height) {
		ui->whenFileOpened(width, height);
	});

	running = true;
}

App::~App() {
	delete fileManager;
	delete canvas;
	delete ui;
}

bool App::init(void) {
	// Init the console.
	bool initResult = Console::getInstance()->init(
		Configuration::screenWidth,
		Configuration::screenHeight
	);

	if (!initResult) {
		std::cerr << "We're having problems starting the application" << std::endl;
		return false;
	}

	return true;
}

int App::run(void) {
	bool first_loop = true;

	InputEvent event;

	// Open or create a new project.
	instance->fileManager->create();
	
	// Main loop.
	while (instance->running) {
		if (first_loop) {
			// Skip input wait for the first time in order to draw all.
			first_loop = false;
		}
		else {
			// Input process.
			Console::getInstance()->inputWait(event);

			// Pass the input event to each component.
			instance->canvas->input(event);
			instance->ui->input(event);
		}

		// Draw process.
		// Clear the console screen.
		Console::getInstance()->clearScreen();
		
		// Redraw the components.
		instance->canvas->draw();
		instance->ui->draw();

		// Update the console screen.
		Console::getInstance()->updateScreen();

		// Delay to avoid flickering.
		Sleep(Configuration::deltaTime);
	}

	// Close console.
	Console::getInstance()->close();

	// Free instance.
	delete instance;

	return EXIT_SUCCESS;
}
