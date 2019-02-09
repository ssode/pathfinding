#include "Node.hpp"

Node::Node(int _i, int _j, NodeType _type) :
	i(_i), j(_j), type(_type), fCost(-1), gCost(-1), hCost(-1), previous(nullptr) {}

bool Node::operator>(const Node& rhs) const {
	return fCost > rhs.fCost;
}

bool Node::operator<(const Node& rhs) const {
	return fCost < rhs.fCost;
}

bool Node::operator==(const Node& rhs) const {
	return i == rhs.i && j == rhs.j;
}

bool Node::operator!=(const Node& rhs) const {
	return !(i == rhs.i && j == rhs.j);
}

