#include "Halfedge.h"
#include "VERTEX.h"
#include "Face.h"
Halfedge::Halfedge() {
	Next = nullptr;
	Previous = nullptr;
	incidentFace = nullptr;
	direction = 0;
}

Halfedge::Halfedge( Vertex* newData) {
	Data = newData;
	Next = nullptr;
	direction = 0;
}
//
void Halfedge::setData( Vertex* newData) {
	Data = newData;
}
void Halfedge::setTwin(Halfedge*  newNext) {
	Twin = newNext;

}
//////////////////////////////////////////////////
// Sets new value for Next pointer of object.
//
// Parameters:
// newNext new value for pointer field
// Pre: none
// Post: Next field of object has been
// modified to hold newNext
//
void Halfedge::setNext(Halfedge* newNext) {
	Next = newNext;
}
Vertex* Halfedge::getData() {
	return Data;
}
Halfedge* Halfedge::getTwin() {
	return Twin;
}
//////////////////////////////////////////////////
// Returns value of Next pointer of object.
//
// Parameters: none
// Pre: object has been initialized
// Post: Next field of object has been
// returned
//
Halfedge* Halfedge::getNext()  {
	return Next;
}
void Halfedge::setPrevious(Halfedge*  newPrev) {
	Previous = newPrev;
}
Halfedge* Halfedge::getPrevious() {
	return Previous;
}


void Halfedge::setFace(Face*  newFace) {
	incidentFace = newFace;
}
void Halfedge::setMultiFields(Vertex* newData, Halfedge* newNext, Halfedge* newPrevious, Halfedge* newTwin) {
	Next = newNext;
	Data = newData;
	Previous = newPrevious;
	Twin = newTwin;
	direction = 0;
}
void Halfedge::setTwinData( Vertex*newData) {
	Twin->setData(newData);

}
