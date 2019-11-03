#include "VERTEX.h"
#include "Halfedge.h"
VERTEX::VERTEX(int X, int Y) {
	x = X;
	y = Y;
	incident = nullptr;
	state = 0;  /*State indicates whether it is a start, end, merge or combine vertex used in the POlYGON TRIANGULATIONS*/
	direction = 0;
}

void VERTEX::addValue(int X, int Y) {
	x = X;
	y = Y;

}
int VERTEX::getX() {
	return x;
}
int VERTEX::getY() {
	return y;
}

void Vertex::setIncidentEdge(Halfedge*  newHalfedge) {
	incident = newHalfedge;
}
Halfedge*   Vertex::getIncidentEdge() {
	return incident;
}
void Vertex::setState(int s) {
	state = s;
}
int Vertex::getState() {
	return state;
}
void Vertex::setDirection(int newDirection) {
	direction = newDirection;
}
int Vertex::getDirection() {
	return direction;
}