#pragma once

#include "Element.hpp"
#include <vector>
#include "ComponentTypes.hpp"
#include <functional>
#include "CanvasActions.h"

class Canvas : public Element {
private:
	// Pixels position and size.
	int zonew;
	int zoneh;
	int zonex;
	int zoney;

	// Pixels data.
	pixels_t pixels;

	// Colors to paint with.
	CanvasColor front_color;
	CanvasColor back_color;

	// Border around the canvas.
	bool draw_border_x;
	bool draw_border_y;

	// Tools to edit the pixels.
	CanvasTools tool;
	bool grid;

	// Event callbacks.
	std::function<void(CanvasColor)> onFrontColorChanged;
	std::function<void(CanvasColor)> onBackColorChanged;

	// Actions queue.
	CanvasActions actions;

	// Tools processes.
	void usePen(int xp, int yp, bool use_front_color);
	void useFillBucket(int xp, int yp, bool use_front_color);
	void useColorPicker(int xp, int yp, bool to_front_color);
public:
	// Constructor.
	Canvas(int width, int height);

	// Life cycle events.
	void input(const InputEvent& event) override;
	void draw(void) override;

	// Modify methods.
	void resize(int width, int height);
	void toggleGrid(void) { grid = !grid; }
	void undo(void) { actions.undo(pixels); }
	void redo(void) { actions.redo(pixels); }
	void actionsForget(void) { actions.forget(); }
	void clear(void);

	// Accessors.
	CanvasColor getFrontColor(void) { return front_color; }
	CanvasColor getBackColor(void) { return back_color; }
	const pixels_t& getPixels(void) { return pixels; }
	constexpr int getZoneWidth(void) { return zonew; }
	constexpr int getZoneHeight(void) { return zoneh; }
	void setFrontColor(const CanvasColor value) { front_color = value; }
	void setBackColor(const CanvasColor value) { back_color = value; }
	void setPixels(const pixels_t& pixels) { this->pixels = pixels; }
	void setTool(const CanvasTools value) { tool = value; }
	void setOnFrontColorChanged(std::function<void(CanvasColor)> callback) { onFrontColorChanged = callback; }
	void setOnBackColorChanged(std::function<void(CanvasColor)> callback) { onBackColorChanged = callback; }
	void setOnUndo(std::function<void(bool)> callback) { actions.onUndo = callback; }
	void setOnRedo(std::function<void(bool)> callback) { actions.onRedo = callback; }
	void setOnActionRecorded(std::function<void(void)> callback) { actions.onActionRecorded = callback; }
	void setOnActionsForget(std::function<void(void)> callback) { actions.onActionsForget = callback; }
	void setOnChangesMade(std::function<void(void)> callback) { actions.onChangesMade = callback; }
};

