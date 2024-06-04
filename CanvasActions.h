#pragma once

#include <cinttypes>
#include <vector>
#include <functional>
#include "ComponentTypes.hpp"

class CanvasAction {
public:
	virtual void run(pixels_t& pixels, bool forward) = 0;
};

class CanvasPaintAction : public CanvasAction {
private:
	int x;
	int y;
	uint8_t old_color;
	uint8_t new_color;
public:
	CanvasPaintAction(int _x, int _y, uint8_t oc, uint8_t nc) :
		x(_x), y(_y), old_color(oc), new_color(nc) {}

	virtual void run(pixels_t& pixels, bool forward);
};

class CanvasFillAction : public CanvasAction {
private:
	std::vector<CanvasPaintAction*> data;
public:
	CanvasFillAction() {}
	~CanvasFillAction();
	virtual void run(pixels_t& pixels, bool forward);
	void add(CanvasPaintAction* action) { data.push_back(action); }
};

class CanvasActions {
private:
	std::vector<CanvasAction*> queue;
	std::vector<CanvasAction*>::iterator curr_action;
public:
	std::function<void(bool)> onUndo;
	std::function<void(bool)> onRedo;
	std::function<void(void)> onActionRecorded;
	std::function<void(void)> onActionsForget;
	std::function<void(void)> onChangesMade;

	CanvasActions();
	~CanvasActions();
	void undo(pixels_t& pixels);
	void redo(pixels_t& pixels);
	void record(CanvasAction* action);
	void forget(void);
};
