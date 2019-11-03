#pragma once

//#include "Halfedge.h"
class Face
{
	friend class Halfedge;
private:
	Halfedge* inner;
	Halfedge* outer;
public:
	Face();
	Face(Halfedge* const newInner, Halfedge* const newOuter);
	void setInner(Halfedge* const newInner);
	void setOuter(Halfedge* const newOuter);
	Halfedge* getInner();
	Halfedge* getOuter();
	
};

