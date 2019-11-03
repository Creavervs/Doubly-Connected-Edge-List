
#include "HALFEDGE.h"
#include "VERTEX.h"
#include "Face.h"
#include <queue>
#include <list>
class DCEL
{
	//friend class Face;
private:
	Halfedge* Head; // points to head node in list
	Halfedge* Tail; // points to tail node in list
	Halfedge* Curr; // points to "current" node
	std::list<Face, std::vector<Face>> faceList;
	std::list<Face, std::vector<Face>> triangleList;
	std::list<Halfedge, std::vector<Halfedge>> HEList;
public:
	DCEL();
	class compareY {
	public:
		bool operator()(Halfedge* const & p1, Halfedge* const & p2);
	};
	
	void printList();
	void printListAnti();
	void printListTriangles();
	void printTwin();
	void setFaceBoundary();
	void printListFaces();
	std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> makeQueue();
	void makeTriangles();
	void makeTriangles2();
	bool isEmpty() const;
	bool inList() const;
	bool PrefixNode(Vertex* newData);
	bool Insert(Vertex* newData,Vertex* nextData); //Used on Creation of DCEL
	bool Insert1(Halfedge* Source, Halfedge*   Destination);// Used on Adding to DCEL
	bool Insert2(Halfedge * Source1, Halfedge * Destination1);
	bool Advance();
	bool Retreat();
	void gotoHead();
	void gotoTail();
	bool setPosition(Vertex const &Target);
	bool DeleteCurrentNode();
	bool DeleteValue(const Vertex& Target);
	Vertex* getCurrentData() const;
	bool setCurrentData( Vertex* newData);
	Halfedge* getCurrentHalfedge();
	void printTwinPrev();
	void putFaceIn(Face f1);
	bool interiorOfP(Halfedge* h1, Halfedge* h2, Halfedge* h3);
	bool onSegment(Halfedge* p, Halfedge* q, Halfedge* r);
	int orientation(Halfedge* p, Halfedge* q, Halfedge* r);
	void showpq(std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q);
	int findMinVertexValue(Halfedge* start);
};