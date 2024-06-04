#include "Canvas.h"
#include "Console.hpp"
#include "input.hpp"
#include "ComponentsHelpers.hpp"

Canvas::Canvas(int width, int height) : Element(
		Configuration::canvasStartX,
		Configuration::canvasStartY,
		Configuration::canvasMaxW,
		Configuration::canvasMaxH,
		0x00)
{
	// By Default do nothing on callbacks.
	onFrontColorChanged = [](CanvasColor _) {};
	onBackColorChanged = [](CanvasColor _) {};

	// Set the default background and foreground colors.
	front_color = Configuration::defaultFrontColor;
	back_color = Configuration::defaultBackColor;

	// Initialize zone area at 0.
	zonew = 0;
	zoneh = 0;

	// Default values.
	grid = false; // Turn off grid.
	
	// Resize canvas.
	resize(width, height);
}

void Canvas::input(const InputEvent& event) {

	// Check if the event is a mouse event with button down.
	if (event.device == InputDevice::Mouse) {

		// Check if the event was performed inside the area of the canvas.
		if (event.mouse.x >= zonex && event.mouse.x < zonex + zonew &&
			event.mouse.y >= zoney && event.mouse.y < zoney + zoneh) {

			if (event.mouse.button == MouseButton::Left ||
				event.mouse.button == MouseButton::Right) {

				// Get the relative position of the mouse click.
				int xp = event.mouse.x - zonex;
				int yp = event.mouse.y - zoney;
				bool is_left_pressed = event.mouse.button == MouseButton::Left;

				// Check what tool is currently active.
				switch (tool) {
				case CanvasTools::Pen:
					usePen(xp, yp, is_left_pressed);
					break;
				case CanvasTools::FillBucket:
					// Start the fill process.
					useFillBucket(xp, yp, is_left_pressed);
					break;
				case CanvasTools::ColorPicker:
					// Start the pick process.
					useColorPicker(xp, yp, is_left_pressed);
					break;
				}
			}
		}
	}
}

void Canvas::draw(void) {
	Console* console = Console::getInstance();

	// Check if the border should be drawed along the X axis.
	if (draw_border_x) {
		for (int i = zonex; i < zonex + zonew; i++) {
			console->drawChar(i, zoney - 1, L'\u2500', 0x0F);
			console->drawChar(i, zoney + zoneh, L'\u2500', 0x0F);
		}
	}
	// Check if the border should be drawed along the Y axis.
	if (draw_border_y) {
		for (int i = zoney; i < zoney + zoneh; i++) {
			console->drawChar(zonex - 1, i, L'\u2502', 0x0F);
			console->drawChar(zonex + zonew, i, L'\u2502', 0x0F);
		}
	}
	// Check if the border corners shold be drawed.
	if (draw_border_y && draw_border_x) {
		console->drawChar(zonex - 1, zoney - 1, L'\u250C', 0x0F);
		console->drawChar(zonex + zonew, zoney + zoneh, L'\u2518', 0x0F);
		console->drawChar(zonex + zonew, zoney - 1, L'\u2510', 0x0F);
		console->drawChar(zonex - 1, zoney + zoneh, L'\u2514', 0x0F);
	}

	// Draw the draw-zone.
	for (int i = 0; i < zoneh; i++) {
		// Get the current row.
		std::vector<uint8_t> row = pixels.at(i);
		// Draw a row.
		console->drawColorVector(x + zonex, y + i + zoney, row);
	}

	// Draw the grid if enabled.
	if (grid) {
		console->drawRectOfChar(x + zonex, y + zoney, zonew, zoneh, L'\u00b7');
	}
}

void Canvas::resize(int width, int height) {
	// Limit the values for width and height.
	if (width > w) {
		width = w;
	}
	if (height > h) {
		height = h;
	}

	// Center the draw zone.
	zonex = (int)((Configuration::canvasEndX - width) / 2);
	zoney = (int)((Configuration::canvasEndY - height) / 2);

	// Determine wheter a border should be drawed around the canvas.
	draw_border_x = height < Configuration::canvasMaxH;
	draw_border_y = width < Configuration::canvasMaxW;

	// Resize the pixels matrix.
	pixels.resize(height);

	for (int j = 0; j < height; j++) {
		std::vector<uint8_t>& row = pixels[j];
		row.resize(width);

		// Fill the row with the back color.
		for (int i = 0; i < width; i++) {
			// Only fill new pixels.
			if (i >= zonew || j >= zoneh) {
				row[i] = (uint8_t)back_color;
			}
		}
	}

	// Store the values in this instance.
	zonew = width;
	zoneh = height;
}

void Canvas::clear(void) {
	for (std::vector<uint8_t>& row : pixels) {
		for (uint8_t& pixel : row) {
			pixel = (uint8_t)back_color;
		}
	}
}

void Canvas::usePen(int xp, int yp, bool use_front_color) {
	// Put a pixel of the current color in the desired location.
	uint8_t& current_pixel = pixels.at(yp).at(xp);
	uint8_t new_color = use_front_color ? (uint8_t)front_color : (uint8_t)back_color;

	// Exit if the target pixel is already painted with the new color.
	if (current_pixel == new_color) {
		return;
	}

	// Record this action if the last action is not equal.
	auto action = new CanvasPaintAction(xp, yp, current_pixel, new_color);
	actions.record(action);

	// Paint the desired pixel.
	current_pixel = new_color;
}

void Canvas::useFillBucket(int xp, int yp, bool use_front_color) {
	// Define the fill node structure and the queue.
	struct FillNode { int x; int y; };
	std::vector<FillNode> fill_queue;

	// Define the action to be recorded.
	CanvasFillAction* action = new CanvasFillAction();
	actions.record(action);

	// Define the source and destination colors.
	short src_c = pixels.at(yp).at(xp);
	short dst_c = use_front_color ? (short)front_color : (short)back_color;

	// Define the node agregate process.
	const std::function<void(int,int)> addNode = [&](int px, int py) {
		// Get the desired pixel.
		const uint8_t& pixel = pixels.at(py).at(px);

		if (pixel == src_c && pixel != dst_c) {
			FillNode node = { px, py };
			fill_queue.push_back(node);

			// Record this node.
			action->add(new CanvasPaintAction(px, py, src_c, dst_c));
		}
	};

	// Get the start pixel.
	addNode(xp, yp);

	// Start the fill process.
	while (fill_queue.size() != 0) {
		// Delete the last node.
		FillNode node = fill_queue.back();
		fill_queue.pop_back();

		// Perform the paint operation.
		uint8_t& current_pixel = pixels.at(node.y).at(node.x);
		current_pixel = dst_c;

		// Add the top pixel to the queue.
		if (node.y - 1 >= 0) {
			addNode(node.x, node.y - 1);
		}

		// Add the left pixel to the queue.
		if (node.x - 1 >= 0) {
			addNode(node.x - 1, node.y);
		}

		// Add the right pixel to the queue.
		if (node.x + 1 < zonew) {
			addNode(node.x + 1, node.y);
		}

		// Add the bottom pixel to the queue.
		if (node.y + 1 < zoneh) {
			addNode(node.x, node.y + 1);
		}
	}
}

void Canvas::useColorPicker(int xp, int yp, bool to_front_color) {
	// Get the clicked pixel.
	uint8_t selected_color = pixels.at(yp).at(xp);

	// Change back or front color depending on which mouse
	// button was pressed.
	if (to_front_color) {
		front_color = toCanvasColor(selected_color);
		onFrontColorChanged(front_color);
	}
	else {
		back_color = toCanvasColor(selected_color);
		onBackColorChanged(back_color);
	}
}
