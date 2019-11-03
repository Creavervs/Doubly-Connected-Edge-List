#include "BST.h"
#include "Halfedge.h"
#include <iostream>
BST::node* BST::makeEmpty(node* t)
{
	if (t == NULL)
		return NULL;
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	return NULL;
}

BST::node* BST::insert(Halfedge* x, node* t) {

	if (t == NULL) {
		t = new node;
		t->data = x;
		t->left = t->right = NULL;
	}
	else if (x->getData()->getY() < t->data->getData()->getY())
		t->left = (x, t->left);

	else if (x->getData()->getY() > t->data->getData()->getY())
		t->right = insert(x, t->right);
	return t;
}

BST::node*BST::findMin(node* t)
{
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

BST::node* BST::findMax(node* t)
{
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

BST::node* BST::remove(Halfedge* x, node* t) {
	node* temp;
	if (t == NULL)
		return NULL;
	else if (x->getData()->getY() < t->data->getData()->getY())
		t->left = remove(x, t->left);
	else if (x->getData()->getY() > t->data->getData()->getY())
		t->right = remove(x, t->right);
	else if (t->left&& t->right) {
		temp = findMin(t->right);
		t->data = temp->data;
		t->right = remove(t->data, t->right);
	}

	else
	{
		temp = t;
		if (t->left == NULL) {
			t = t->right;
		}
		else if (t->right == NULL) {
			t = t->left;

		}
		delete temp;

	}

	return t;
}

void BST::inorder(node* t)
{
	if (t != NULL) {


		inorder(t->left); /*in order traversal*/
		std::cout << t->data->getData()->getX() << " " << t->data->getData()->getY() << " " << t->data->getData()->getState() << "\n ";
		inorder(t->right);/*reverse order*/
	}
}

BST::node* BST::find(node* t, Halfedge* x)
{
	if (t == NULL)
		return NULL;
	else if (x->getData()->getY() < t->data->getData()->getY())
		return find(t->left, x);
	else if (x->getData()->getY() > t->data->getData()->getY())
		return find(t->right, x);
	else
		return t;
}
BST::node* BST::findaRoot(node* pRoot, Halfedge* x)
{
	if (pRoot == NULL) {
		return pRoot;
	}
	if (pRoot->left == NULL && pRoot->right == NULL)
		return pRoot;

	if ((pRoot->left != NULL && pRoot->left->data->getData()->getY() == x->getData()->getY())
		|| (pRoot->right != NULL && pRoot->right->data->getData()->getY() == x->getData()->getY()))
		return pRoot->left;

	if (pRoot->data->getData()->getY() > x->getData()->getY())
		return findaRoot(pRoot->left, x);

	if (pRoot->data->getData()->getY() < x->getData()->getY())
		return findaRoot(pRoot->right, x);


}
BST::node* BST::findaParent(node* pRoot, Halfedge* x, node* parent)
{
	if (pRoot == NULL) {
		return parent;
	}
	else if (pRoot->left == NULL && pRoot->right == NULL)
		return pRoot;

	else if ((pRoot->left != NULL && pRoot->left->data->getData()->getY() == x->getData()->getY())
		|| (pRoot->right != NULL && pRoot->right->data->getData()->getY() == x->getData()->getY()))
		return pRoot;

	else if ((pRoot->left != NULL &&pRoot->data->getData()->getY()) > x->getData()->getY())
		return findaParent(pRoot->left, x,pRoot);
	else if ((pRoot->right != NULL && pRoot->data->getData()->getY()) < x->getData()->getY())
		return findaParent(pRoot->right, x,pRoot);
	else
		return pRoot;

}





/*Public Functions which call the private functions*/

BST::BST()
{
	root = nullptr;
}

BST::~BST()
{
	root = makeEmpty(root);
}

void BST::Insert(Halfedge* x)
{

	root = insert(x, root);

}

void BST::Remove(Halfedge* x)
{
	node* temp;
	temp = root;
	root = remove(x, root);
}

void BST::Display()
{

	inorder(root);
	std::cout << std::endl;
}

void BST::Search(Halfedge* x)
{
	root = find(root, x);
}
Halfedge* BST::returnRootLeft(Halfedge* x)
{
	node* temp;
	temp = root;
	temp = findaParent(root, x,root);

	if (root == NULL) {
		return NULL;
	}
	return temp->data;
}
Halfedge* BST::returnParent(Halfedge* x)
{
	node* temp;
	temp = root;
	if (x == nullptr) {
		return nullptr;
	}
	temp = findaParent(root, x,root);
	if (root == NULL) {
		return NULL;
	}
	return temp->data;
}
void BST::changeData(Halfedge* x, Halfedge* y)
{
	root = find(root, x);
	root->data = y;
}

Halfedge* BST::getHelper(Halfedge* x) {
	node* temp;
	temp = root;
	temp = find(root, x);
	return temp->helper;
}
void BST::setHelper(Halfedge* x, Halfedge* y) {
	node* temp;
	temp = root;
	temp = find(root, x);
	temp->helper = y;

}

/*To DO: for this class  the Y value is only being compared, it needs to have a X value comparison kicking in here too*/