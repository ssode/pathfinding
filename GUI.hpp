#pragma once

#include <SDL.h>
#include <vector>
#include "Node.hpp"

class GUI {
private:
	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr;
	int numRows, numCols, nodeSize;
	const std::vector<std::vector<Node>>& grid;

public:
	GUI(const std::vector<std::vector<Node>>& _grid);
	~GUI();

	void draw() const;
	void wait(unsigned ms) const;
};