#include "DCEL.h"
#include "Halfedge.h"
#include "Vertex.h"
#include <cassert>
#include <string>
#include <queue>
#include <stack>
#include "Face.h"
#include <list>
DCEL::DCEL() {
	Head = Tail = Curr = nullptr;
	std::list<Face, std::vector<Face>> faceList;
	std::list<Face, std::vector<Face>> triangleList;
	std::list<Halfedge, std::vector<Halfedge>> HEList;
}

bool DCEL::isEmpty() const {
	return (Head == nullptr);
}


/*Comparator to compare the Y values inside the vertex and returns the bigger y value or if they are the same returns the smaller x valued one*/

bool DCEL::compareY::operator()(Halfedge* const & p1, Halfedge* const & p2) {

	if (p1->getData()->getY() == p2->getData()->getY()) {
		return p1->getData()->getX()  > p2->getData()->getX();
	}

	// return "true" if "p1" is ordered before "p2", for example:
return p1->getData()->getY() > p2->getData()->getY();
}

void DCEL::makeTriangles() {
	// Make a queue
	
	std::list<Face, std::vector<Face>> faceList1;
	faceList1 = faceList;
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	Halfedge* temp2 = new  Halfedge(0);
	Halfedge* Previous = new  Halfedge(0);
	int first = 1;
	int count = 1;
	for each(Face item in faceList) {
		if (first == 1) {
			first = first + 1;
			continue;//Dont do anything to boundary face.
		}
		//printListFaces();
		std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q;
		int counter = 0;
		temp1 = item.getInner();
		temp = temp1;
		

		temp = temp->getPrevious();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			// assign left and right chains to the objects 
			temp->getData()->setDirection(1);// left direction
			temp1->getData()->setDirection(2);// right direction

			q.push(temp);// push them to the top so we can process them
			q.push(temp1);
			counter += 2;
			temp1 = temp1->getNext();
			if (temp->getData()->getY() == temp1->getData()->getY()) {
				//temp1->setDirection(2);

				break;
			}
			temp = temp->getPrevious();
			if (temp->getData()->getY() == temp1->getData()->getY()) {

				//temp->getData()->setDirection(1);

				q.push(temp);
				counter += 1;
				break;
			}
			
		}
		//printListFaces();
		
		std::cout << "Face " << count << "\n";
		count = count + 1;
		// pseudo code
		if ((temp1->getNext()->getNext()->getNext()->getData()->getY()) == temp1->getData()->getY()) {
			triangleList.push_back(item);
			continue; // already a triangle, proceed to next face.
		}

		// get a face, order from top to bottom
		std::stack<Halfedge*> myStack;
		Face f = item;
		//faceList.remove(f);
		
		int Size = q.size();
		temp = q.top();
		q.pop();
		myStack.push(temp);
		temp = q.top();
		q.pop();
		myStack.push(temp);
		Previous = temp;
		
		for (int i = 0; i < Size - 1; i++) {
			int size1 = q.size();
			if (size1 == 1) {
				break;
			}
			if (q.empty()) {
				break;
			}
			temp = q.top();
			q.pop();
			
			if (temp->getData()->getDirection() != myStack.top()->getData()->getDirection()) {// Different chains
				while (!myStack.empty()) {// pop everything on the stack

					int sizer = myStack.size();
					if (sizer == 1) {
						//temp2 = myStack.top();
						//myStack.pop();
						break;
					}
					
						temp2 = myStack.top();
						Insert2(temp, temp2);

						myStack.pop();
					
				}



				myStack.push(temp2);
				myStack.push(temp);
			}
			else {
				temp2= myStack.top();
				myStack.pop();
				while (true) {
					int sizer = myStack.size();
					if (sizer <= 0) {
						break;
					}
					temp1 = myStack.top();
					int orientation1 = orientation(temp, temp1, temp2);
					if (orientation1 ==1) {
						
							myStack.pop();
							Insert2(temp, temp1);
						
					}
					else {
						myStack.pop();
						break;
					}
				}
				myStack.push(temp1);
				myStack.push(temp);
			}
			int number = myStack.size();
			int number2 = q.size();
			Previous = temp;
			
		}
		while (!myStack.empty()) {// pop everything on the stack
			int sizer = myStack.size();
			if (sizer >= 3) {
				myStack.pop();
				temp= q.top();
				temp1 = myStack.top();
				Insert2(temp, temp1);
				
			}

			if (sizer == 2) {
				break;
			}

		}
	}
	
	
	
}


std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> DCEL::makeQueue() {


	std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q;
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);

	temp = Head;
	temp1 = Head;
	q.push(temp);
	temp = temp->getNext();
	// Using lambda to compare elements.

	while (temp != temp1) {
		q.push(temp);
		temp = temp->getNext();

	}

	return q;
}
void DCEL::printTwin() {
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head->getTwin();
	temp = Head->getTwin();
	int g = temp->getData()->getX();
	int h = temp->getData()->getY();
	std::cout << g << " "
		<< h << " " << "\n";
	temp = temp->getNext();

	while (temp->getData() != temp1->getData()) {
		g = temp->getData()->getX();
		h = temp->getData()->getY();
		std::cout <<g << " "
			<< h << " " << "\n";
		temp = temp->getNext();

	}
}
void DCEL::printTwinPrev() {
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head->getTwin();
	temp = Head->getTwin();
	int g = temp->getData()->getX();
	int h = temp->getData()->getY();
	std::cout << g << " "
		<< h << " " << "\n";
	temp = temp->getPrevious();

	while (temp != temp1) {
		g = temp->getData()->getX();
		h = temp->getData()->getY();
		std::cout << g << " "
			<< h << " " << "\n";
		temp = temp->getPrevious();

	}
}



void DCEL::printList() {   // Clockwise print from front to back of list.
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head;
	temp = Head;
	std::cout << temp->getData()->getX() << " "
		<< temp->getData()->getY() << " " << "\n";
	temp = temp->getNext();
	while (temp != temp1) {
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << "\n";
		temp = temp->getNext();
	}
}
void DCEL::setFaceBoundary() {   // sets the face boundary of all faces.
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head;
	temp = Head;
	Face f1(temp, NULL);
	faceList.push_back(f1);
	temp = temp->getNext();
	while (temp != temp1) {
		f1.setInner(temp);
		temp->setFace(&f1);
		temp = temp->getNext();
	}
}
void DCEL::printListFaces() {   // Clockwise print from front to back of list.
	std::cout << faceList.size();
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	int count = 1;
	std::cout << "\nFace " << count << "\n";
	for each(Face item in faceList) {
		temp1 = item.getInner();
		temp = temp1;
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
		temp = temp->getNext();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			std::cout << temp->getData()->getX() << " "
				<< temp->getData()->getY() << " " << temp->getData()->getDirection()<<"\n";
			temp = temp->getNext();
		}
		std::cout << "\nFace Outer " << count << "\n";
		temp1 = item.getOuter();
		temp = temp1;
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
		temp = temp->getNext();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			std::cout << temp->getData()->getX() << " "
				<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
			temp = temp->getNext();
		}

		
		std::cout << "\nFace " << count << "\n";
		count++;
		std::cout << "\nFace " << count << "\n";
	}


}

void DCEL::printListTriangles() {   // Clockwise print from front to back of list.
	std::cout << triangleList.size();
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	int count = 1;
	std::cout << "\nFace " << count << "\n";
	for each(Face item in triangleList) {
		temp1 = item.getInner();
		temp = temp1;
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
		temp = temp->getNext();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			std::cout << temp->getData()->getX() << " "
				<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
			temp = temp->getNext();
		}
		std::cout << "\nFace Outer " << count << "\n";
		temp1 = item.getOuter();
		temp = temp1;
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
		temp = temp->getNext();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			std::cout << temp->getData()->getX() << " "
				<< temp->getData()->getY() << " " << temp->getData()->getDirection() << "\n";
			temp = temp->getNext();
		}


		std::cout << "\nFace " << count << "\n";
		count++;
		std::cout << "\nFace " << count << "\n";
	}


}

void DCEL::printListAnti() {   // Clockwise print from front to back of list.
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head->getData()->getIncidentEdge();
	temp = Head->getData()->getIncidentEdge();
	std::cout << temp->getData()->getX() << " "
		<< temp->getData()->getY() << " " << "\n";
	temp = temp->getPrevious();
	while (temp != temp1) {
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << "\n";
		temp = temp->getPrevious();
	}
}
bool DCEL::PrefixNode(Vertex* newData) {
	Halfedge* newNode = new(std::nothrow) Halfedge(newData);
	if (newNode == nullptr) { return false; }

	newNode->setNext(Head);
	Head = newNode;
	return true;
}
bool DCEL::Insert(Vertex* newData,Vertex* nextData) {

	// for each halfedge being added;
	/*Set the twin
		Set the next
			Set the Previous
				Set the Incident edge
					
	
	*/
	//Problem with the incident edge not being set as previous.

	//Problem with the next of the first node being set as previous.

	Halfedge* newNode = new(std::nothrow) Halfedge(newData);
	Halfedge* newTwin = new(std::nothrow) Halfedge(nextData);
	Halfedge* temp = new(std::nothrow) Halfedge(0);

	if (isEmpty()) {
		newNode->setNext(Head);
		newNode->setPrevious(Tail);
		newTwin->setNext(Head);
		newTwin->setPrevious(Head);

		newNode->setTwin(newTwin);
		newTwin->setTwin(newNode);

		
		
		Head = Tail = Curr = newNode;
		Head->setTwin(newTwin);
		Tail->setTwin(newTwin);
		Curr->setTwin(newTwin);
		newNode->getData()->setIncidentEdge(newNode);
		newTwin->getData()->setIncidentEdge(newTwin);
		return true;
	}
	if (newNode == nullptr || Curr == nullptr) {
		return false;
	}
	newNode->setTwin(newTwin);
	newTwin->setTwin(newNode);
	Curr->setNext(newNode);
	newNode->setNext(Curr);
	newNode->setPrevious(Curr);
	newNode->getData()->getIncidentEdge()->setPrevious(Curr);
	//newTwin->setPrevious(Curr->getTwin());
	newTwin->setNext(Curr->getTwin());
	newTwin->setPrevious(Head->getTwin());

	
	//
	Curr->setNext(newNode);
	Curr->getTwin()->setPrevious(newTwin);
	//Curr->setTwinData(newData);
	
	// set the twins of each
	
	//
	//Set the next and previous of the twins
	

	//If we are adding to the tail then we do this
	

	if (Curr == Tail) {
		Tail = newNode;
		Curr = Tail;
		Curr->setNext(Head);
		
		Head->setPrevious(Curr);
		//Curr->getData()->setIncidentEdge(newNode);

		//Head->setTwin(newTwin);
		//Curr->setTwin(Head->getTwin());
		Head->getTwin()->setNext(Curr->getTwin());
	
		Curr->getTwin()->setPrevious(Curr->getTwin()->getPrevious());

		newNode->getData()->setIncidentEdge(newNode);
		
		newTwin->getData()->setIncidentEdge(newTwin);
		
		
	}
	//The condition for adding to the end.

	else {



	}
	
	return true;
}

bool DCEL::Insert1(Halfedge * Source,Halfedge * Destination) {
	//Need a catch here to go from left to right or right to left.
	//Need a catch here to go from left to right or right to left.
	Halfedge* Source1 = new(std::nothrow) Halfedge(0);
	Halfedge* Destination1 = new(std::nothrow) Halfedge(0);
	if (Source->getData()->getX() > Destination->getData()->getX()) {
		Halfedge* temp = Source;
		Halfedge* temp2 = Destination;
		Destination1 = temp;
		Source1 = temp2;

	}
	else {
		Source1 = Source;
		Destination1 = Destination;
	}
	
	// Make new nodes for the HE that is going to be inserted
	Halfedge* newNode = new(std::nothrow) Halfedge(Source1->getData());
	Halfedge* newTwin = new(std::nothrow) Halfedge(Destination1->getData());
	// Want to find the four nodes that need to be updated.
	Halfedge* SourcePrevious = new(std::nothrow) Halfedge(0);
	Halfedge* SourceCurrent = new(std::nothrow) Halfedge(0);
	Halfedge* DestinationPrevious = new(std::nothrow) Halfedge(0);
	Halfedge* DestinationCurrent = new(std::nothrow) Halfedge(0);
	
	SourceCurrent = Source1;
	SourcePrevious = Source1->getPrevious();
	DestinationCurrent = Destination1;
	DestinationPrevious = Destination1->getPrevious();


	
	

	
		// sets the incident edge of the new node// 
		// Sets the new node so that they complete the loops
		newNode->setNext(DestinationCurrent);
		newNode->setPrevious(SourcePrevious);
		newTwin->setNext(SourceCurrent);
		newTwin->setPrevious(DestinationPrevious);
		//Need to handle the Half edges Prior to the new nodes
		SourceCurrent->setPrevious(newTwin);
		SourcePrevious->setNext(newNode);
		DestinationCurrent->setPrevious(newNode);
		DestinationPrevious->setNext(newTwin);
		newNode->setTwin(newTwin);
		newTwin->setTwin(newNode);
		/**/
		if (Source1->getData()->getX() > Destination1->getData()->getX()) {
			Face f1(newTwin, newNode);
			faceList.push_back(f1);
		}
		else {
		
			Face f1(newNode, newTwin);
			faceList.push_back(f1);
			
		}
			
	// Make that new FaceRecord and add to the many faced god. // Game of thrones reference.
	
	
	std::cout<<"Added new HE, SIZE = : " << faceList.size() << "\n";
	return true;
}
bool DCEL::Insert2(Halfedge * Source, Halfedge * Destination) {
	//Need a catch here to go from left to right or right to left.
	Halfedge* Source1 = new(std::nothrow) Halfedge(0);
	Halfedge* Destination1 = new(std::nothrow) Halfedge(0);
	bool swap = false;
	if (Source->getData()->getX() > Destination->getData()->getX()) {
		Halfedge* temp = Source;
		Halfedge* temp2 = Destination;
		Destination1 = temp;
		Source1 = temp2;
		swap = true;
	}
	else {
		Source1 = Source;
		Destination1 = Destination;
	}

	// Make new nodes for the HE that is going to be inserted
	Halfedge* newNode = new(std::nothrow) Halfedge(Source1->getData());
	Halfedge* newTwin = new(std::nothrow) Halfedge(Destination1->getData());
	// Want to find the four nodes that need to be updated.
	Halfedge* SourcePrevious = new(std::nothrow) Halfedge(0);
	Halfedge* SourceCurrent = new(std::nothrow) Halfedge(0);
	Halfedge* SourceTwin = new(std::nothrow) Halfedge(0);
	Halfedge* SourceTwinPrevious = new(std::nothrow) Halfedge(0);

	Halfedge* DestinationPrevious = new(std::nothrow) Halfedge(0);
	Halfedge* DestinationCurrent = new(std::nothrow) Halfedge(0);
	Halfedge* DestinationTwin = new(std::nothrow) Halfedge(0);
	Halfedge* DestinationTwinPrevious = new(std::nothrow) Halfedge(0);

	SourceCurrent = Source1;
	SourcePrevious = Source1->getPrevious();

	SourceTwin = Source1->getTwin();
	SourceTwinPrevious = SourcePrevious->getTwin();

	DestinationCurrent = Destination1;
	DestinationPrevious = Destination1->getPrevious();

	DestinationTwin = Destination1->getTwin();
	DestinationTwinPrevious = DestinationPrevious->getTwin();




	// sets the incident edge of the new node// 
	// Sets the new node so that they complete the loops
	
	//Need to handle the Half edges Prior to the new nodes
	Source->setPrevious(newTwin);
	Source->getPrevious()->setNext(newNode);
	Destination->setPrevious(newNode);
	Destination->getPrevious()->setNext(newTwin);

	// Need to look at the twins of the Previous and Next Edges
	/*
	SourceTwinPrevious->setNext(newTwin);
	SourceTwin->setPrevious(newNode);
	DestinationTwinPrevious->setNext(newNode);
	DestinationTwin->setPrevious(newTwin);
	*/
	// need to reset the twins of those edges.
	newNode->setTwin(newTwin);
	newTwin->setTwin(newNode);
	newNode->setNext(Destination);
	newNode->setPrevious(Source->getPrevious());
	newTwin->setNext(SourceCurrent);
	newTwin->setPrevious(Destination->getPrevious());
	
	if (swap) {
		Face f1(newTwin, newNode);
		triangleList.push_back(f1);
	}
	else {
	
		Face f1(newNode, newTwin);
		triangleList.push_back(f1);

	}
	
	// Make that new FaceRecord and add to the many faced god. // Game of thrones reference.


	std::cout << "Added new HE, SIZE = : " << triangleList.size() << "\n";
	return true;
}




void DCEL::gotoHead() {
	Curr = Head;
}

///////////////////////////////////////////////////////
// Resets the current position to the tail of the list.
//
void DCEL::gotoTail() {
	Curr = Tail;
}

bool DCEL::DeleteCurrentNode() {
	Halfedge* delThis;
	if (Curr == nullptr) {
		return false;
	}
	else if (Curr == Head) { //delete Head node
		delThis = Curr;
		Head = Head->getNext();
		Head->setPrevious(nullptr);
		Curr = Head;
		Curr->setPrevious(nullptr);
		if (Tail == delThis) Tail = Curr;
		delThis->setNext(nullptr);
		delete delThis;
		return true;
	}

	//locate Curr's previous node
	Halfedge* prevNode = Head;
	while (prevNode != nullptr && prevNode->getNext() != Curr) {
		prevNode = prevNode->getNext();
	}

	//check for valid Curr pointer
	if (prevNode == nullptr) {
		return false;
	}

	//previous found bypass and delete Curr
	delThis = Curr;
	if (Curr == Tail) {
		prevNode->setNext(nullptr);
	}
	else {
		prevNode->setNext(Curr->getNext());
		Curr = prevNode->getNext();
	}

	Curr->setNext(nullptr);

	Curr->setPrevious(prevNode);
	if (Tail == delThis) {
		Tail = prevNode;

	}

	delete delThis;
	return true;
}
bool DCEL::DeleteValue(const Vertex& Target) {
	Halfedge* myCurr = Head;
	Halfedge* myTrailer = nullptr;

	while (myCurr != nullptr) {// && !(myCurr->getData() == Target))
		myTrailer = myCurr;
		myCurr = myCurr->getNext();
	}
	if (myCurr == nullptr) {
return false;
	}

	if (myTrailer == nullptr) {
		Head = Head->getNext();
	}
	else {
		myTrailer->setNext(myCurr->getNext());
	}

	if (Curr == myCurr) { Curr = myTrailer; }
	if (Tail == myCurr) { Tail = myTrailer; }

	myCurr->setNext(nullptr);
	delete myCurr;
	return true;
}
bool DCEL::setCurrentData(Vertex* newData)
{
	if (!Curr) return false;
	Curr->setData(newData);
	return true;
}
Vertex* DCEL::getCurrentData() const {
	assert(Curr != nullptr);
	return (Curr->getData());
}
bool DCEL::Advance() {
	if (Curr != NULL) {
		if (Curr == Tail) {
			return false;
		}
		Curr = Curr->getNext();
		return true;
	}
	else
		return false;
}
bool DCEL::Retreat() {
	if (Curr != NULL) {
		if (Curr == Head) {
			return false;
		}
		Curr = Curr->getPrevious();
		return true;
	}
	else
		return false;


}
Halfedge* DCEL::getCurrentHalfedge() {
	return Curr;
}
bool DCEL::setPosition(Vertex const &Target) {
	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	temp1 = Head;
	temp = Head;
	if (temp == Curr) {
		Curr = temp;
		return true;
	}
	temp = temp->getNext();
	while (temp != temp1) {
		if (temp == Curr) {
			Curr = temp;
			return true;
		}
		temp = temp->getNext();
	}
	return false;
}
void  DCEL::putFaceIn(Face f1) {
	faceList.push_back(f1);
}
bool DCEL::interiorOfP(Halfedge* first, Halfedge* second, Halfedge* current) {
	Vertex v1 = *first->getData();
	Vertex v2 = *second->getData();
	Vertex v3 = *current->getData();

	int x1 = v1.getX();
	int x2 = v2.getX();
	int y1 = v1.getY();
	int y2 = v2.getY();
	int x3 = v3.getX();
	int y3 = v3.getY();
int x4 = 1000;
int y4 = v3.getY();
if (first->getData()->getDirection() == 1) {// if its a left chain
	double A1 = x3 - x2;
	double A2 = y3 - y2;
	double B1 = x1 - x2;
	double B2 = y1 - y2;
	double C1 = (A1*B2) - (A2*B1);
	double C2 = B1 - B2;
	// Gives equation
	if (C1 < 0 && C1 != 0) {
		return true;
	}
	else {
		return false;

	}
}
else {
	double A1 = x2 - x1;
	double A2 = y2 - y1;
	double B1 = x2 - x3;
	double B2 = y2 - y3;
	double C1 = (A1*B2) - (A2*B1);
	double C2 = B1 - B2;
	if (C1 < 0 && C1 != 0) {
		return true;
	}
	else {
		return false;

	}

}

// Gives equation for line of the two vertices we interested in.


}
void DCEL::makeTriangles2() {
	// Make a queue


	Halfedge* temp = new  Halfedge(0);
	Halfedge* temp1 = new  Halfedge(0);
	Halfedge* temp2 = new  Halfedge(0);
	Halfedge* Previous = new  Halfedge(0);
	int first = 1;
	int count = 1;
	for each(Face item in faceList) {
		if (first == 1) {
			first = first + 1;
			continue;//Dont do anything to boundary face.
		}
		//printListFaces();
		std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q2;
		int counter = 0;
		temp1 = item.getInner();
		temp = temp1;
		int min = findMinVertexValue(temp1); 
		q2.push(temp);
		temp = temp->getPrevious();
		while (temp->getData()->getY() != temp1->getData()->getY()) {
			// assign left and right chains to the objects 
			q2.push(temp);// push them to the top so we can process them
			temp = temp->getPrevious();
			}
		
		std::cout << "Face " << count << "\n";
		count = count + 1;
		// pseudo code
		
		
		bool dir = true;

		temp = q2.top();
		temp1 = temp;
		bool chainL = false;
		bool chainR = false;
		temp = temp->getPrevious();
		while ((chainL == false)) {
			// assign left and right chains to the objects 
			
			if (temp1->getData()->getY() == min) {
				temp1->getData()->setDirection(2);
				chainL = true;
			}
			else {
				temp1->getData()->setDirection(2);// right direction
				temp1 = temp1->getNext();
			}
		}
		while (chainR == false) {
			if (temp->getData()->getY() == min) {
				temp->getData()->setDirection(1);
				chainR = true;
			}
			else {
				temp->getData()->setDirection(1);// left direction
				temp = temp->getPrevious();
			}
		}
		
		// get a face, order from top to bottom
		std::stack<Halfedge*> myStack;
	

		showpq(q2);
		temp = q2.top();
		temp = temp;
		if ((temp->getNext()->getNext()->getNext()->getData()->getY()) == temp->getData()->getY()) {
			triangleList.push_back(item);
			continue; // already a triangle, proceed to next face.
		}
		temp = q2.top();
		myStack.push(temp);
		q2.pop();
		temp = q2.top();
		myStack.push(temp);
		q2.pop();
		Previous = temp;
		int Size = q2.size();

		for (int i = 0; i < Size-1 ; i++) {
			int size1 = q2.size();
			if (size1 == 1) {
				break;
			}
			if (q2.empty()) {
				break;
			}
			temp = q2.top();
			q2.pop();

			if (temp->getData()->getDirection() != myStack.top()->getData()->getDirection()) {// Different chains
				while (!myStack.empty()) {// pop everything on the stack

					int sizer = myStack.size();
					if (sizer == 1) {
						temp1 = myStack.top();
						myStack.pop();
						break;
					}
					temp1 = myStack.top();		
					myStack.pop();
					if (myStack.top()->getData()->getX() == temp1->getNext()->getData()->getX()) {
						Halfedge* placeholder = myStack.top();// reverse ordering
						myStack.pop();
						Insert1(temp, placeholder);
						myStack.push(temp1);
						temp1 = myStack.top();
						
					}
					else {
						Insert1(temp, temp1);
					}
					
				}



				myStack.push(Previous);
				myStack.push(temp);
			}
			else {
				temp2 = myStack.top();
				myStack.pop();
				while (true) {
					int sizer = myStack.size();
					if (sizer <= 0) {
						break;
					}
					temp1 = myStack.top();
					int orientation1 = orientation(temp, temp2, temp1);
					bool inside = interiorOfP(temp, temp2, temp1);
					if (interiorOfP(temp, temp2, temp1)) {
						
							
							Insert1(temp, temp1);
							temp2 = myStack.top();
							myStack.pop();
							
					}
					else { break; }
					
				}
				myStack.push(temp2);
				myStack.push(temp);
			}
			int number = myStack.size();
			int number2 = q2.size();
			Previous = temp;

		}
		while (!myStack.empty()) {// pop everything on the stack
			int sizer = myStack.size();
			if (sizer >= 3) {
				
				myStack.pop();
				Insert1(temp, temp1);
				break;
			}

			if (sizer == 2) {
				break;
			}

		}
	}



}
bool DCEL::onSegment(Halfedge* p, Halfedge* q, Halfedge* r)
{
	// Given three colinear points p, q, r, the function checks if 
	// point q lies on line segment 'pr' 
	int p_x = p->getData()->getX();
	int p_y = p->getData()->getY();
	int q_x = q->getData()->getX();
	int q_y = q->getData()->getY();
	int r_x = r->getData()->getX();
	int r_y = r->getData()->getY();
	if (q_x <= std::max(p_x, r_x) && q_x >= std::min(p_x, r_x) &&
		q_y <= std::max(p_y, r_y) && q_y >= std::min(p_y,r_y))
		return true;

	return false;
}
int DCEL::orientation(Halfedge* p, Halfedge* q, Halfedge* r)
{
	
	int p_x = p->getData()->getX();
	int p_y = p->getData()->getY();
	int q_x = q->getData()->getX();
	int q_y = q->getData()->getY();
	int r_x = r->getData()->getX();
	int r_y = r->getData()->getY();
	// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
	// for details of below formula. 
	double val = (q_y - p_y) * (r_x - q_x) -
		(q_x - p_x) * (r_y - q_y);

	if (val == 0) return 0;  // colinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}
void DCEL::showpq(std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q) {
	Halfedge* temp;
	std::cout << "QUEUE\n" << "\n";
	while (!q.empty()) {
		temp = q.top();
		std::cout << temp->getData()->getX() << " "
			<< temp->getData()->getY() << " " << temp->getData()->getDirection()<< "\n";
		q.pop();
	}

}
int DCEL::findMinVertexValue(Halfedge* start) {
	std::priority_queue<Halfedge*, std::vector<Halfedge*>, DCEL::compareY> q;
	int min = 0;
	Halfedge* temp;
	temp = start;
	q.push(temp);
	temp = temp->getNext();
	while (temp->getData()->getY() != start->getData()->getY()) {
		q.push(temp);
		temp = temp->getNext();
	}
	int j = 1;
	while (q.size() != 1) {
		q.pop();
	}
	min = q.top()->getData()->getY();
	return min;
}