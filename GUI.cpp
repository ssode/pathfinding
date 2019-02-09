#include "GUI.hpp"

GUI::GUI(const std::vector<std::vector<Node>>& _grid) : grid(_grid), numRows(_grid.size()), numCols(_grid[0].size()) {
	nodeSize = 15;
	window = SDL_CreateWindow("A* Pathfinding Visualizer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, numCols * nodeSize, numRows * nodeSize, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, 0);
	
}

GUI::~GUI() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void GUI::draw() const {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_Rect rect;
	rect.w = nodeSize;
	rect.h = nodeSize;
	for (const auto& row : grid) {
		for (const Node& node : row) {
			switch (node.type) {
			case NodeType::Movable:
				SDL_SetRenderDrawColor(renderer, 160, 160, 160, 255);
				break;

			case NodeType::Wall:
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				break;

			case NodeType::Ghost:
				SDL_SetRenderDrawColor(renderer, 0, 204, 0, 255);
				break;

			case NodeType::Target:
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				break;

			case NodeType::Open:
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
				break;

			case NodeType::Closed:
				SDL_SetRenderDrawColor(renderer, 204, 204, 0, 255);
				break;

			case NodeType::Path:
				SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
				break;
			}
			rect.y = node.i * nodeSize;
			rect.x = node.j * nodeSize;
			SDL_RenderFillRect(renderer, &rect);
			//SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			//SDL_RenderDrawRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}

void GUI::wait(unsigned ms) const {
	SDL_Delay(ms);
}