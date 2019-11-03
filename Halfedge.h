/*Halfedge class is used to encapsulate the low - level pointer operations*/
#pragma once 

#include "VERTEX.h"
#include "Face.h"
#include "Halfedge.h"
class Halfedge
{
	//friend class Face;

private:
	Vertex* Data; // data "capsule"
	Halfedge* Twin;
	// Consider using smart pointers instead
	Halfedge* Next; // pointer to next node
	Halfedge* Previous;
	Face *incidentFace;
	int direction;
public:
	Halfedge();
	Halfedge(Vertex* newData);
	void setTwin(Halfedge* newNext);
	void setData(Vertex* newData);
	void setNext(Halfedge*  newNext);
	Vertex* getData();
	Halfedge* getTwin();
	Halfedge* getNext() ;
	void setPrevious(Halfedge*  newPrev);
	Halfedge* getPrevious() ;
	void setFace(Face*  newFace);
	void setMultiFields(Vertex* newData, Halfedge* newNext, Halfedge* newPrevious, Halfedge* newTwin);
	void setTwinData(Vertex  *newData);
	
};
