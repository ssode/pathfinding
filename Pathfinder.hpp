#pragma once

#include <stack>
#include <vector>
#include "Node.hpp"
#include "GUI.hpp"

class Pathfinder {
private:
	//reference to the grid loaded from the file
	std::vector<std::vector<Node>> &grid;

	const GUI& gui;

	// heuristic cost function (hCost)
	int manhattanDistance(const Node& start, const Node& end);

	// method to get pointers to the nodes accessible from the given node
	std::vector<Node*> getNeighbors(const Node& node);

public:
	// constructor takes in a 2d vector of nodes
	Pathfinder(std::vector<std::vector<Node>>& _grid, const GUI& _gui) : grid(_grid), gui(_gui) {};

	// method to find the path from the start location to the target location using A*
	std::stack<Node> findPath(Node *start, Node *target);
};