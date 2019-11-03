
/* Vertex class is used to encapsulate the data and separate it from the pointers
that define the list structure*/
#pragma once 
//#include "Halfedge.h"

#include <iostream>
#include <fstream>
#include<string>


class VERTEX {
	friend class Halfedge;
private:
	int x;
	int y;
	Halfedge* incident;
	int state;
	int direction;

public:
	VERTEX(int x = 0, int y = 0);
	void addValue(int x, int y);
	int getX();
	int getY();
	void setIncidentEdge(Halfedge*  newHalfedge);
	void setState(int s);
	int getState();
	void setDirection(int newDirection);
	int getDirection();
	Halfedge*  getIncidentEdge();

	//Reporter Member Functions
	// . . . Unchanged from previous declaration
	//Mutator Member Functions
	// . . . Unchanged from previous declaration
	//Operator Overloads

}; // Vertex

typedef VERTEX Vertex; // Isn