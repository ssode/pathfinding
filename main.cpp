#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <SDL.h>
#include <SDL_main.h>
#include "Pathfinder.hpp"
#include "GUI.hpp"

int main(int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	int startRow, startCol, targRow, targCol;
	std::ifstream inFile("grid.txt");
	std::string line;
	std::vector<std::vector<Node>> grid;
	while (std::getline(inFile, line)) {
		std::istringstream iss(line);
		std::vector<Node> temp;
		char c;
		while (iss >> c) {
			int val = c - '0';
			if (val == 2) {
				startRow = grid.size();
				startCol = temp.size();
			} else if (val == 3) {
				targRow = grid.size();
				targCol = temp.size();
			}
			
			temp.emplace_back(Node(grid.size(), temp.size(), (NodeType)val));
			
		}
		grid.push_back(temp);
	}
	bool displaying = true;
	GUI gui(grid);
	Pathfinder pf(grid, gui);
	std::stack<Node> path = pf.findPath(&grid[startRow][startCol], &grid[targRow][targCol]);
	gui.draw();
	while (!path.empty()) {
		const Node& n = path.top();
		if (!(n.i == targRow && n.j == targCol))
			grid[n.i][n.j].type = NodeType::Path;
		path.pop();
		gui.draw();
		gui.wait(20);
	}

	SDL_Event e;
	while (displaying) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT)
				displaying = false;
		}
	}
	SDL_Quit();
	return 0;
}