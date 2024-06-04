#include "CanvasActions.h"
#include "Configuration.hpp"

void CanvasPaintAction::run(pixels_t& pixels, bool forward) {
	// Perform the paint process.
	try {
		pixels.at(y).at(x) = forward ? new_color : old_color;
	}
	catch (std::exception e) {
		// Don't do anything.
	}
}

CanvasFillAction::~CanvasFillAction() {
	for (int i = 0; i < data.size(); i++) {
		delete data[i];
	}
}

void CanvasFillAction::run(pixels_t& pixels, bool forward) {
	// Perform the fill process.
	auto it = data.begin();

	while (it != data.end()) {
		(*it)->run(pixels, forward);
		it++;
	}
}

CanvasActions::CanvasActions() {
	curr_action = queue.begin();
	onUndo = [](bool _) {};
	onRedo = [](bool _) {};
	onActionRecorded = []() {};
	onActionsForget = []() {};
	onChangesMade = []() {};
}

CanvasActions::~CanvasActions() {
	for (int i = 0; i < queue.size(); i++) {
		delete queue[i];
	}
}

void CanvasActions::undo(pixels_t& pixels) {
	if (curr_action != queue.begin()) {
		curr_action--;

		// Run action.
		(*curr_action)->run(pixels, false);

		// Update the UI.
		// Notify when the actions index go forward or backward.
		onUndo(curr_action == queue.begin());

		// Update the FileManager.
		onChangesMade();
	}
}

void CanvasActions::redo(pixels_t& pixels) {
	if (curr_action != queue.end()) {
		// Run action.
		(*curr_action)->run(pixels, true);

		curr_action++;

		// Update the UI.
		// Notify when the actions index go forward or backward.
		onRedo(curr_action == queue.end());

		// Update the FileManager.
		onChangesMade();
	}
}

void CanvasActions::record(CanvasAction* action) {
	// Remove the forward actions if the index is not at the end of the queue.
	if (curr_action != queue.end()) {
		while (curr_action != queue.end()) {
			delete (*curr_action);
			curr_action = queue.erase(curr_action);
		}
		curr_action = queue.end();
	}
	// Remove the first action if the queue is at limit.
	else {
		if (queue.size() == Configuration::maxActionsQueueSize) {
			queue.erase(queue.begin());
		}
	}

	// Add the action to the queue.
	queue.push_back(action);
	// Set the last action on the end.
	curr_action = queue.end();

	// Update the UI.
	// Notify that the queue has been updated.
	onActionRecorded();

	// Update the FileManager.
	onChangesMade();
}

void CanvasActions::forget(void) {
	if (queue.size() > 0) {
		// Delete each action in the actions queue.
		for (int i = 0; i < queue.size(); i++) {
			delete queue[i];
		}

		// Clear actions queue.
		queue = {};
		// Reset current action.
		curr_action = queue.begin();

		// Update the UI.
		onActionsForget();
	}
}
