#include <unordered_set>
#include <set>
#include <iostream>
#include "Pathfinder.hpp"


// this is the heuristic function that is used to calculate the hCost of a node
// this method just adds up the absolute values of the differences in the row and col
// it should work well since we can't move in diagonals
int Pathfinder::manhattanDistance(const Node& start, const Node& end) {
	return abs(start.i - end.i) + abs(start.j - end.j);
}

// returns a vector of Node pointers to the nodes that are accessible from the given node
std::vector<Node*> Pathfinder::getNeighbors(const Node& node) {
	int startRow = node.i;
	int startCol = node.j;
	std::vector<Node*> ret;
	for (int i = -1; i <= 1; i++) {
		int newRow = startRow + i;
		int newCol = startCol + i;
		if (newRow == startRow && newCol == startCol) {
			continue;
		}
		if (newRow >= 0 && newRow < grid.size()) {
			ret.push_back(&grid[newRow][startCol]);
		}
		if (newCol >= 0 && newCol < grid[startRow].size()) {
			ret.push_back(&grid[startRow][newCol]);
		}
	}
	
	return ret;
}

// Finds and reconstructs the path from start to end using A* search
std::stack<Node> Pathfinder::findPath(Node *start, Node *target) {
	// the open set is an ordered set using a comparison function that keeps the node 
	// with the lowest fCost at the beginning and can store multiple nodes with the same fCost
	std::multiset<Node*, CostCompare> open; 
	std::unordered_set<Node*> closed; // the closed set is unordered because the position of elements in it isn't important
	std::stack<Node> temp; // used for rebuilding the path and will be returned empty if the search fails
	start->gCost = 0;
	start->hCost = manhattanDistance(*start, *target);
	start->fCost = start->gCost + start->hCost;
	open.insert(start);

	while (!open.empty()) {
		Node *current = *open.begin();
		if (*current == *target) {
			while (current->previous != nullptr) {
				temp.push(*current);
				current = current->previous;
			}
			return temp;
		}

		// remove the current node from the open set and add it to the closed set
		open.erase(open.begin());
		closed.insert(current);
		if (current->type != NodeType::Ghost)
			current->type = NodeType::Closed;

		// get a vector containing pointers to the nodes that you can move to from current
		std::vector<Node*> neighbors = getNeighbors(*current);
		for (Node *node : neighbors) {
			if (closed.count(node) > 0 || node->type == NodeType::Wall) // if this node is already in the closed set, or it's a wall, we can ignore this iteration
				continue;

			int temp_gCost = current->gCost + 1; // store the cost of traveling to this node in a temp variable

			// this will contain a range of iterators to the open set that includes the nodes that have the same fCost as the one we are checking
			// if the node was not found in the open set, the 2 iterators are equal
			auto res = open.equal_range(node);

			// use this so store whether a better path to this node has already been found
			bool betterPathKnown = false;

			// iterates through the range contained in res to find the node
			// if it is found, the gCosts are compared to see if the path we are on now is better than its previous one
			// if the current path is better, the node is removed from its place in the open set to be added back with updates costs
			// if the old path is better, betterPathKnown is set to true
			for (auto itr = res.first; itr != res.second; ++itr) {
				if (**itr == *node) {
					if (temp_gCost < node->gCost) {
						open.erase(itr);
					} else {
						betterPathKnown = true;
					}
					break;
				}
			}

			// if this is the best known path to the current neighbor, update its scores/previous pointer and insert it to the open set
			if (!betterPathKnown) {
				node->gCost = temp_gCost;
				node->hCost = manhattanDistance(*node, *target);
				node->fCost = node->gCost + node->hCost;
				node->previous = current;
				if (node->type != NodeType::Target)
					node->type = NodeType::Open;
				open.insert(node);
			}	
			gui.draw();
			gui.wait(20);
		}
		
	}
	return temp;
}