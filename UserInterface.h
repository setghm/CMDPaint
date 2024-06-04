#pragma once

#include "controls.h"
#include <functional>
#include "ComponentTypes.hpp"

class UserInterface : public Element {
private:
	// Undo and redo buttons.
	Button* button_tool_undo;
	Button* button_tool_redo;
	// Tools buttons.
	Button* button_tool_pen;
	Button* button_tool_fill;
	Button* button_tool_picker;
	// Front and back colors labels.
	Label* label_front_color;
	Label* label_back_color;

	// Hightlight selected tool button and unhighlight the rest.
	void highlightToolButton(Button* button);
public:
	// Constructor.
	UserInterface(
		// Send callbacks.
		std::function<void(FileMenuOption)> onFileMenuOptionSelected,
		std::function<void(void)> onCanvasUndo,
		std::function<void(void)> onCanvasRedo,
		std::function<void(CanvasTools)> onToolSelected,
		std::function<void(void)> onGridToggled,
		std::function<void(CanvasColor)> onFrontColorSelected,
		std::function<void(CanvasColor)> onBackColorSelected,
		std::function<void(void)> onColorsSwaped,
		std::function<void(int, int)> onCanvasResize
	);

	// Event driven methods.
	void whenFrontColorChanges(CanvasColor value);
	void whenBackColorChanges(CanvasColor value);
	void whenUndo(bool begin_reached);
	void whenRedo(bool end_reached);
	void whenActionRecorded(void);
	void whenActionsForget(void);

	// Life cycle methods.
	void input(const InputEvent& event) override;
	void draw(void) override;
};

