#pragma once

// this enum maps the values given in the assignment to a type of node
enum class NodeType {
	Movable, Wall, Ghost, Target, Path, Open, Closed
};

struct Node  {
	// i and j hold the row and column of the node
	// gCost holds the cost of moving from the start to this node
	// hCost holds the result of the heuristic function on this node and the target
	// fCost is the sum of gCost and hCost
	int i, j, gCost, hCost, fCost; 

	// the type of the node, mostly used to check for walls
	NodeType type;

	// will be set to the last node visited before this node was discovered, and updated if a better path to the node is found
	Node *previous;

	// the constructor will take in the coordinates and type of the node
	Node(int _i, int _j, NodeType _type);

	// overloaded operators
	bool operator>(const Node& rhs) const;
	bool operator<(const Node& rhs) const;
	bool operator==(const Node& rhs) const;
	bool operator!=(const Node& rhs) const;
};

// this is passed to the open set's constructor as a way for it to compare the total costs of each node and keep itself sorted with the least cost first
struct CostCompare {
	bool operator()(const Node *a, const Node *b) const {
		return a->fCost < b->fCost;
	}
};