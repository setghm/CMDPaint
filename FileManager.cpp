#include "FileManager.h"
#include "Configuration.hpp"
#include "Console.hpp"
#include <iostream>
#include <fstream>

bool FileManager::create(void) {
	// Abort operation if the user doesn't want to discard changes.
	if (!confirmDiscardUnsavedChanges()) {
		return false;
	}

	// Close the current file.
	current_file_path = L"";

	// Clear the canvas buffer and restore
	// its size and back and front colors.
	canvas->actionsForget();
	canvas->setFrontColor(Configuration::defaultFrontColor);
	canvas->setBackColor(Configuration::defaultBackColor);
	canvas->resize(Configuration::defaultImageWidth, Configuration::defaultImageHeight);
	canvas->clear();

	Console::getInstance()->setProjectTitle(Configuration::defaultProjectTitle);

	// Indicate that this project is saved.
	isSaved = true;
	Console::getInstance()->setUnsavedProjectMark(false);

	return true;
}

bool FileManager::open(std::wstring filepath) {
	// Abort operation if the user doesn't want to discard changes.
	if (!confirmDiscardUnsavedChanges()) {
		return false;
	}

	auto console = Console::getInstance();
	
	// Select a file with the file picker dialog if no filepath was supplied.
	if (filepath.size() == 0) {
		filepath = console->showFilePicker(L"Select a file to edit");

		if (filepath.size() == 0) {
			return false;
		}
	}

	// Read the selected file.
	std::ifstream file(filepath, std::ios::binary);

	// First retrieve the width and height.
	uint32_t width, height;
	file.read(reinterpret_cast<char*>(&width), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(&height), sizeof(uint32_t));

	// Now, read the pixels row by row.
	pixels_t pixels;
	for (int y = 0; y < height; y++) {
		std::vector<uint8_t> row;

		for (int x = 0; x < width; x++) {
			uint8_t pixel;
			file.read(reinterpret_cast<char*>(&pixel), sizeof(uint8_t));
			row.push_back(pixel);
		}

		pixels.push_back(row);
	}

	// Send the values to canvas.
	canvas->actionsForget();
	canvas->resize(width, height);
	canvas->setPixels(pixels);

	file.close();

	// Set project title and current file path.
	current_file_path = filepath;
	console->setProjectTitle(current_file_path);

	// Indicate that this project is saved.
	isSaved = true;
	Console::getInstance()->setUnsavedProjectMark(false);

	return true;
}

bool FileManager::save(bool save_as) {
	auto console = Console::getInstance();

	// Check if there are an active file path.
	if (current_file_path.size() == 0 || save_as) {
		bool overwrite = true;

		do {
			// Show save dialog.
			std::wstring filepath = console->showFileSaver(
				L"Select where to save the file"
			);

			// No file selected, operation canceled.
			if (filepath.size() == 0) {
				return false;
			}

			// Check if the selected file exists.
			std::fstream file(filepath);

			// Request overwrite consent.
			if (file.good()) {
				int result = console->showDialog(
					L"Overwrite",
					L"This file already exists, overwrite it?",
					MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON2
				);

				// Save or save as the file.
				overwrite = result == IDYES;
			}
			else {
				overwrite = true;
			}

			if (overwrite) {
				current_file_path = filepath;
			}

		} while (!overwrite);
	}

	// Write information into the file path.
	std::ofstream file(current_file_path, std::ios::binary);
	uint32_t width = canvas->getZoneWidth();
	uint32_t height = canvas->getZoneHeight();
	auto pixels = canvas->getPixels();

	file.write(reinterpret_cast<const char*>(&width), sizeof(uint32_t));
	file.write(reinterpret_cast<const char*>(&height), sizeof(uint32_t));

	for (auto row : pixels) {
		for (const uint8_t& pixel : row) {
			file.write(reinterpret_cast<const char*>(&pixel), sizeof(uint8_t));
		}
	}

	file.close();

	// Indicate that the project was saved successfully.
	isSaved = true;
	console->setUnsavedProjectMark(false);
	console->setProjectTitle(current_file_path);

	return true;
}

bool FileManager::exit(void) {
	// Only true if the user wants to discard changes.
	return confirmDiscardUnsavedChanges();
}

bool FileManager::confirmDiscardUnsavedChanges() {
	auto console = Console::getInstance();

	// If changes made, request confirm.
	if (!isSaved) {
		// Show confirmation dialog.
		int result = console->showDialog(
			L"Unsaved changes",
			L"Do you want to save your work before?",
			MB_YESNO | MB_ICONWARNING | MB_DEFBUTTON1
		);

		// Save or save as the file.
		if (result == IDYES) {
			return save();
		}
	}

	return true;
}

void FileManager::whenChangesMade() {
	isSaved = false;
	Console::getInstance()->setUnsavedProjectMark(true);
}
