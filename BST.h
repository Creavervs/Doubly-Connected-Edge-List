#pragma once
#include "Halfedge.h"
class BST
{
private:
	typedef struct node
	{
		Halfedge* data;
		Halfedge* helper;
		node* left;
		node* right;
	}node;

private: node* root;
private: node* makeEmpty(node* t);
private: node* insert(Halfedge* x, node* t);
private: node* findMin(node* t);
private: node* findMax(node* t);
private: node* remove(Halfedge* x, node* t);
private: void inorder(node* t);
private: node* find(node* t, Halfedge* x);
private: node* findaRoot(node* t, Halfedge* x);
private: node* findaParent(node* t, Halfedge* x, node* t1);

public:
	BST();
	~BST();
	void Insert(Halfedge* x);
	void Remove(Halfedge* x);
	void Display();
	void Search(Halfedge* x);
	Halfedge* returnRootLeft(Halfedge* x);
	Halfedge* returnParent(Halfedge* x);
	void changeData(Halfedge* x, Halfedge* y);
	Halfedge* getHelper(Halfedge* x);
	void setHelper(Halfedge* x, Halfedge* y);
};

