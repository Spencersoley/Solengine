#pragma once
class Node
{
public:
	Node(int value, int x, int y);
	~Node();

	void setValue(int value) { m_value = value; }
	int getValue() { return m_value; }
	int getXPos() { return m_xPos; }
	int getYPos() { return m_yPos; }

private:
	int m_value;
	int m_xPos;
	int m_yPos;

	float g; //cost
	float h; //heuristic estimate to goal state
	float f; // f = g + h


	// zombie checks what node it's on
	// zombie finds the value of the 8 nodes around it
	// zombie is given the lowest valued of these as its destination 
	// zombie movement is initiated towards its destination
	// zombie arrives at destination and needs a new destination
	// zombie checks what node it's on
	// zombie finds the values of the 8 nodes around it

	// __(This must run parralel to the node behaviour)__
	// Nodes recalculate their value based on how long it would take for the player to reach them.
	// Player's centre is above a certain node. That node is given the value 0.
	// Nodes diagonally are given the valu of 1.4, and the adjacent are given the value of 1
	// 



	// The node at the player's position is grabbed. Its value is set to zero.
	// The nodes that can't be crossed have their values set to -1.
	// All other nodes have their values set to 200.
	// A function is called on the player's node. It checks if its adjacent nodes aren't -1.
	// it sets the value of the adjacent nodes that aren't -1 to its own value +1.
	// it checks the diagonal nodes aren't -1 and sets their values to 1.41
	// it calls a function on each non -1 adjacent node, telling it to do the same.
	// that adjacent node compares the values of the adjacents with its own value +1
	// if its own value +1 is lower than the adjacent node's value, the adjacent node's value changes to it
	// it the does the same for its diagonal nodes.
	// checks adjacents, sets adjacents, checks diagonals, sets diagonals, calls function from adjacents



	// 

	// create pathfinder class
	// give each zombie a reference to the pathfinder 
	// pathfinder takes level data and zombie position and target position as inputs
	// pathfinder uses A* to find shortest route from start to finish
	//
	// zombies position is translated to a node number, and can access that node to find a direction
	// zombie takes that direction and moves until its grabs a node with a different direction
};

