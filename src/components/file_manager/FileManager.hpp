#pragma once

#include "../ComponentTypes.hpp"
#include "../canvas/Canvas.hpp"
#include <string>
#include <functional>

class FileManager {
private:
	Canvas* canvas;
	std::wstring current_file_path;
	bool isSaved;

	std::function<void(int, int)> onFileOpened;

	bool confirmDiscardUnsavedChanges();
public:
	FileManager(Canvas* _canvas) :
		canvas(_canvas),
		current_file_path(L""),
		isSaved(true),
		onFileOpened ([](int, int) {})
	{}

	bool create(void);
	bool open(std::wstring filepath=L"");
	bool save(bool save_as=false);
	bool exit(void);

	void setOnFileOpened(std::function<void(int, int)> callback) { onFileOpened = callback; }

	void whenChangesMade();
};

