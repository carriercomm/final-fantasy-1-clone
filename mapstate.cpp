#include "mapstate.h"

MapState::MapState() {
	head = 0;
	tail = 0;
}

MapState::~MapState() {
	// cleanup any maps
	while (tail) {
		popMap();
	}
}

void MapState::pushMap(Map *map) {
	// push and initialize the new map
	if (tail) {
		tail->pauseMap();
		tail->setNext(map);
	}
	map->setPrev(tail);
	tail = map;
	tail->init(party, &input, this);
}

void MapState::popMap() {
	// cleanup and pop current map
	if (tail) {
		Map *toPop = tail;
		tail = tail->getPrev();
		if (tail) {
			tail->unpauseMap();
		}

		delete toPop;
		toPop = 0;
	}
}

void MapState::changeMap(Map *map) {
	// pop the current map
	popMap();

	// push the new map
	pushMap(map);
}

MenuState *MapState::enterMenu() {
	MenuState *ms = new MenuState();
	stateManager->pushState(ms);
	return ms;
}

void MapState::update() {
	tail->updateMap();
}

void MapState::render() {
	tail->renderMap(windowWidth, windowHeight);
}

void MapState::pause() {
	if (tail) {
		tail->pauseMap();
	}
}

void MapState::unpause() {
	if (tail) {
		tail->unpauseMap();
	}
}
