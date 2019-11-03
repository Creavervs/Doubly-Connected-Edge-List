#include "Face.h"
//#include "Halfedge.h"


Face::Face() {
	inner = nullptr;
	outer = nullptr;
}
Face::Face(Halfedge* const newInner, Halfedge* const newOuter) {
	inner = newInner;
	outer = newOuter;
}

void Face::setInner(Halfedge* const newInner) {
	inner = newInner;
}
void Face::setOuter(Halfedge* const newOuter) {
	outer = newOuter;
}

Halfedge* Face::getInner() {
	return inner;
}
Halfedge* Face::getOuter() {
	return outer;
}
