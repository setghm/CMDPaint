#pragma once

#include "ComponentTypes.hpp"
#include "Canvas.h"
#include <string>

class FileManager {
private:
	Canvas* canvas;
	std::wstring current_file_path;
	bool isSaved;

	bool confirmDiscardUnsavedChanges();
public:
	FileManager(Canvas* _canvas) : canvas(_canvas), current_file_path(L""), isSaved(true) {}

	bool create(void);
	bool open(std::wstring filepath=L"");
	bool save(bool save_as=false);
	bool exit(void);

	void whenChangesMade();
};

