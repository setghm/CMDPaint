#include "UserInterface.h"
#include "Configuration.hpp"
#include "core.hpp"
#include "ComponentsHelpers.hpp"

UserInterface::UserInterface(
	std::function<void(FileMenuOption)> onFileMenuOptionSelected,
	std::function<void(void)> onCanvasUndo,
	std::function<void(void)> onCanvasRedo,
	std::function<void(CanvasTools)> onToolSelected,
	std::function<void(void)> onGridToggled,
	std::function<void(CanvasColor)> onFrontColorSelected,
	std::function<void(CanvasColor)> onBackColorSelected,
	std::function<void(void)> onColorsSwaped,
	std::function<void(int, int)> onCanvasResize
) {
	// Create controls.

	// Main divider.
	Divider* divider_main = new Divider(Configuration::uiStartX, 0, Configuration::screenHeight, 0x80, L'\u2502', true);
	// Title.
	Label* label_app_name = new Label(Configuration::uiStartX + 1, 0, L"PixelPaint", 0x8F);

	// File menu section.
	Button* button_new = new Button(Configuration::uiStartX + 1, 2, L"New", 0x78, 10);
	Button* button_open = new Button(Configuration::uiStartX + 1, 3, L"Open", 0x71, 10);
	Button* button_save = new Button(Configuration::uiStartX + 1, 4, L"Save", 0x76, 10);
	Button* button_save_as = new Button(Configuration::uiStartX + 1, 5, L"Save As", 0x75, 10);
	Button* button_exit = new Button(Configuration::uiStartX + 1, 6, L"Exit", 0x74, 10);
	Divider* divider_file_menu = new Divider(Configuration::uiStartX + 1, 7, 10, 0x80);

	// Tools section.
	Label* label_tools = new Label(Configuration::uiStartX + 1, 8, L"Tools", 0x8F);
	button_tool_undo = new Button(Configuration::uiStartX + 1, 10, L"\u2190", 0x87, 5);
	button_tool_redo = new Button(Configuration::uiStartX + 6, 10, L"\u2192", 0x87, 5);
	button_tool_pen = new Button(Configuration::uiStartX + 1, 11, L"Pen", 0x70, 10);
	button_tool_fill = new Button(Configuration::uiStartX + 1, 12, L"Fill", 0x70, 10);
	button_tool_picker = new Button(Configuration::uiStartX + 1, 13, L"Picker", 0x70, 10);
	Button* button_tool_grid = new Button(Configuration::uiStartX + 1, 14, L"Grid", 0x70, 10);
	Divider* divider_tools = new Divider(Configuration::uiStartX + 1, 15, 10, 0x80);

	// Color palette section.
	Label* label_color_palette = new Label(Configuration::uiStartX + 1, 16, L"Colors", 0x8F);
	// Front and back buttons.
	label_front_color = new Label(Configuration::uiStartX + 1, 27, L" F ", 0x0F);
	Button* button_swap = new Button(Configuration::uiStartX + 4, 27, L"\u2190\u2192", 0x8F, 4);
	label_back_color = new Label(Configuration::uiStartX + 8, 27, L" B ", 0x0F);
	Divider* divider_colors = new Divider(Configuration::uiStartX + 1, 28, 10, 0x80);
	// Create all the color buttons.
	for (int i = 0; i < 16; i++) {
		int xp = (i < 8) ? Configuration::uiStartX + 1 : Configuration::uiStartX + 6;
		int yp = (i < 8) ? 18 + i : 18 + i - 8;
		uint8_t color = i << 4 | i;
		
		// Create each color button.
		Button* button_color = new Button(xp, yp, L" ", color, 5);

		// Detect when the right button is pressed over this control in order to
		// set the back color.
		button_color->setDetectRightButton(true);
		
		// Register the event callbacks.
		button_color->setOnPressed([=]() {
			onFrontColorSelected(toCanvasColor(i));
			label_front_color->setBackColor(color);
			label_front_color->setFrontColor(CONTRAST_COLOR(color));
		});
		button_color->setOnRightPressed([=]() {
			onBackColorSelected(toCanvasColor(i));
			label_back_color->setBackColor(color);
			label_back_color->setFrontColor(CONTRAST_COLOR(color));
		});

		// Add this button to the children.
		addChild(button_color);
	}

	// Resize section.
	Label* label_resize = new Label(Configuration::uiStartX + 1, 29, L"Image Size", 0x8F);
	Label* label_size_x = new Label(Configuration::uiStartX + 1, 31, L"SizeX:", 0x8F);
	Edit* edit_width = new Edit(Configuration::uiStartX + 7, 31, 7, 3);
	Label* label_size_y = new Label(Configuration::uiStartX + 1, 32, L"SizeY:", 0x8F);
	Edit* edit_height = new Edit(Configuration::uiStartX + 7, 32, 7, 3);
	Button* button_resize = new Button(Configuration::uiStartX + 1, 34, L"Apply", 0xF0, 10);

	// Author message.
	Label* label_author = new Label(Configuration::uiStartX + 1, Configuration::screenHeight - 1, L"\u00A9 SetApps", 0x87);

	// Add all the child controls.
	addChild(divider_main);
	addChild(label_app_name); // File menu.
	addChild(button_new);
	addChild(button_open);
	addChild(button_save);
	addChild(button_save_as);
	addChild(button_exit);
	addChild(divider_file_menu);
	addChild(label_tools); // Tools.
	addChild(button_tool_undo);
	addChild(button_tool_redo);
	addChild(button_tool_pen);
	addChild(button_tool_fill);
	addChild(button_tool_picker);
	addChild(button_tool_grid);
	addChild(divider_tools);
	addChild(label_color_palette); // Color palette.
	addChild(label_front_color);
	addChild(button_swap);
	addChild(label_back_color);
	addChild(divider_colors);
	addChild(label_resize); // Resize section.
	addChild(label_size_x);
	addChild(edit_width);
	addChild(label_size_y);
	addChild(edit_height);
	addChild(button_resize);
	addChild(label_author); // Author message.

	// Register callbacks on buttons.
	// File menu.
	button_new->setOnPressed([=]() {
		onFileMenuOptionSelected(FileMenuOption::New);
	});
	button_open->setOnPressed([=]() {
		onFileMenuOptionSelected(FileMenuOption::Open);
	});
	button_save->setOnPressed([=]() {
		onFileMenuOptionSelected(FileMenuOption::Save);
	});
	button_save_as->setOnPressed([=]() {
		onFileMenuOptionSelected(FileMenuOption::SaveAs);
	});
	button_exit->setOnPressed([=]() {
		onFileMenuOptionSelected(FileMenuOption::Exit);
	});

	// Tools section.
	button_tool_undo->setOnPressed(onCanvasUndo);
	button_tool_redo->setOnPressed(onCanvasRedo);
	button_tool_pen->setOnPressed([=]() {
		highlightToolButton(button_tool_pen);
		onToolSelected(CanvasTools::Pen);
	});
	button_tool_fill->setOnPressed([=]() {
		highlightToolButton(button_tool_fill);
		onToolSelected(CanvasTools::FillBucket);
	});
	button_tool_picker->setOnPressed([=]() {
		highlightToolButton(button_tool_picker);
		onToolSelected(CanvasTools::ColorPicker);
	});
	button_tool_grid->setOnPressed([=]() {
		// Highlight the grid when activated.
		uint8_t cc = button_tool_grid->getColor();
		button_tool_grid->setColor(cc == 0x70 ? 0x3F : 0x70);

		onGridToggled();
	});

	// Colors section.
	button_swap->setOnPressed([=]() {
		uint8_t color_lfc = label_front_color->getColor();
		uint8_t color_lbc = label_back_color->getColor();

		// Swap the labels colors.
		label_front_color->setColor(color_lbc);
		label_back_color->setColor(color_lfc);

		onColorsSwaped();
	});

	// Resize section.
	button_resize->setOnPressed([=]() {
		// Get the resize edit values.
		int w = std::stoi(edit_width->getValue());
		int h = std::stoi(edit_height->getValue());

		// Clamp values.
		if (w > Configuration::canvasMaxW) {
			w = Configuration::canvasMaxW;
			edit_width->setValue(std::to_wstring(w));
		}
		if (h >= Configuration::canvasMaxH) {
			h = Configuration::canvasMaxH;
			edit_height->setValue(std::to_wstring(h));
		}

		onCanvasResize(w, h);
	});

	// Show default values.
	// Tools section.
	button_tool_undo->setEnabled(false);
	button_tool_redo->setEnabled(false);
	highlightToolButton(button_tool_pen); // The selected tool by default.

	// Color palette section.
	whenFrontColorChanges(Configuration::defaultFrontColor);
	whenBackColorChanges(Configuration::defaultBackColor);

	// Resize section.
	edit_width->setValue(std::to_wstring(Configuration::defaultImageWidth));
	edit_height->setValue(std::to_wstring(Configuration::defaultImageHeight));
	
}

void UserInterface::draw(void) {
	Console* console = Console::getInstance();

	// Draw the controls area.
	for (int y = 0; y < Configuration::screenHeight; y++) {
		for (int x = Configuration::uiStartX + 1; x < Configuration::screenWidth; x++) {
			console->drawChar(x, y, L' ', 0x80);
		}
	}

	// Draw the child controls.
	Element::draw();
}

void UserInterface::input(const InputEvent& event) {
	// Handle the input event in the child controls.
	Element::input(event);
}

void UserInterface::highlightToolButton(Button* button) {
	button_tool_pen->setColor(button_tool_pen == button ? 0x5F : 0x70);
	button_tool_fill->setColor(button_tool_fill == button ? 0x1F : 0x70);
	button_tool_picker->setColor(button_tool_picker == button ? 0x6F : 0x70);
}

void UserInterface::whenFrontColorChanges(CanvasColor value) {
	label_front_color->setBackColor(toTwoDigitsColor(value));
	label_front_color->setFrontColor(CONTRAST_COLOR(toTwoDigitsColor(value)));
}

void UserInterface::whenBackColorChanges(CanvasColor value) {
	label_back_color->setBackColor(toTwoDigitsColor(value));
	label_back_color->setFrontColor(CONTRAST_COLOR(toTwoDigitsColor(value)));
}

void UserInterface::whenUndo(bool begin_reached) {
	button_tool_undo->setColor(begin_reached ? 0x87 : 0xF0);
	button_tool_undo->setEnabled(!begin_reached);

	// Activate the redo button.
	button_tool_redo->setColor(0x0F);
	button_tool_redo->setEnabled(true);
}

void UserInterface::whenRedo(bool end_reached) {
	button_tool_redo->setColor(end_reached ? 0x87 : 0x0F);
	button_tool_redo->setEnabled(!end_reached);

	// Active the undo button.
	button_tool_undo->setColor(0xF0);
	button_tool_undo->setEnabled(true);
}

void UserInterface::whenActionRecorded(void) {
	// Activate the undo button but disable the redo button.
	button_tool_undo->setColor(0xF0);
	button_tool_undo->setEnabled(true);

	button_tool_redo->setColor(0x87);
	button_tool_redo->setEnabled(false);
}

void UserInterface::whenActionsForget(void) {
	// Disable both undo and redo buttons.
	button_tool_undo->setColor(0x87);
	button_tool_undo->setEnabled(false);

	button_tool_redo->setColor(0x87);
	button_tool_redo->setEnabled(false);
}

