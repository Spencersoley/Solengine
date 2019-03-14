#pragma once

#include <glm/glm.hpp>

class Node
{
public:
	Node(int f, int x, int y);
	~Node();

	void setf(int value) { m_f = value; }
	void updatef() { m_f = m_g + m_h; }
	void setg(int value) { m_g = value; }
	void seth(int value) { m_h = value; }
	int getf() { return m_f; }
	int getg() { return m_g; }
	int geth() { return m_h; }

	int getXPos() { return m_xPos; }
	int getYPos() { return m_yPos; }
	glm::vec2 getDir();

	int count;

private:
	int m_xPos;
	int m_yPos;

	glm::vec2 m_dir = { 0, 0 };

	int m_f; // f = g + h
	int m_g = 0; //cost
	int m_h = 0;; //heuristic estimate to goal state
	
	Node* p_parent;

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

