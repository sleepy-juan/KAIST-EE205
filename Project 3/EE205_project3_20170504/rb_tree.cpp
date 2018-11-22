/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#include "rb_tree.h"
#include <iostream>
#include <string>

#include "linked_list.h"
using namespace std;

/******************************************************/
/******************** CLASS BASICS ********************/
/******************************************************/

// constructor
template <class T>
RBTree<T>::RBTree(){
	// root property: root is black
	root = new RBNode<T>("", false, NULL);
}

// destructor
template <class T>
RBTree<T>::~RBTree(){
	while(!is_external(root)){
		remove(root->key);
	}
	delete root;
}

/******************************************************/
/********************** DISPLAY ***********************/
/******************************************************/

// display
template <class T>
void RBTree<T>::display(){
	if(is_external(root)){
		cout << "Tree is empty." << endl;
		return;
	}
	cout << "root: " << root->key << endl;;
	inorder_print(root);
	cout << endl;
	preorder_print(root);
	cout << endl;
}

template <class T>
void RBTree<T>::displayRB(){
	if(is_external(root)){
		cout << "Tree is empty." << endl;
		return;
	}
	cout << "root: " << root->key << endl;;
	inorder_printRB(root);
	cout << endl;
	preorder_printRB(root);
	cout << endl;
}

// inorder print
template <class T>
void RBTree<T>::inorder_print(RBNode<T> *n){
	if(!is_external(n->leftChild))
		inorder_print(n->leftChild);
	cout << n->key << " ";
	if(!is_external(n->rightChild))
		inorder_print(n->rightChild);
}

template <class T>
void RBTree<T>::inorder_printRB(RBNode<T> *n){
	if(!is_external(n->leftChild))
		inorder_printRB(n->leftChild);
	cout << n->key << "(" << (n->isRed ? "R" : "B") <<") ";
	if(!is_external(n->rightChild))
		inorder_printRB(n->rightChild);
}

// preorder print
template <class T>
void RBTree<T>::preorder_print(RBNode<T> *n) {
	cout << n->key << " ";
	if(!is_external(n->leftChild))
		preorder_print(n->leftChild);
	if(!is_external(n->rightChild))
		preorder_print(n->rightChild);
}

template <class T>
void RBTree<T>::preorder_printRB(RBNode<T> *n) {
	cout << n->key << "(" << (n->isRed ? "R" : "B") <<") ";
	if(!is_external(n->leftChild))
		preorder_printRB(n->leftChild);
	if(!is_external(n->rightChild))
		preorder_printRB(n->rightChild);
}

/******************************************************/
/****************** NODE INFORMATION ******************/
/******************************************************/

// is external
template <class T>
bool RBTree<T>::is_external(RBNode<T> *n) {
	return (n->leftChild == NULL && n->rightChild == NULL);
}

// is root
template <class T>
bool RBTree<T>::is_root(RBNode<T> *n) {
	return n->parent == NULL;
}

// get height
template <class T>
int RBTree<T>::height(RBNode<T> *n){
	return n->height;
}

// update height
template <class T>
void RBTree<T>::update_height(RBNode<T> *n){
	if(is_external(n)) {
		n->height = 0;
	}
	else {
		int lh = height(n->leftChild);
		int rh = height(n->rightChild);

		n->height = (lh >= rh ? lh : rh) + 1;
	}
}

/******************************************************/
/****************** TREE STRUCTURES *******************/
/******************************************************/

// restruct tree
// given parent of double red
template <class T>
void RBTree<T>::restruct(RBNode<T> *v){
	if(v->parent->leftChild == v){
		if(v->leftChild->isRed){ 
			RBNode<T> *parent = v->parent;

			// make v as root of subtree
			if(is_root(parent))
				root = v;
			else{
				if(parent->parent->leftChild == parent)
					parent->parent->leftChild = v;
				else
					parent->parent->rightChild = v;
			}
			v->parent = parent->parent;

			// connect v's right child as parent's left child
			parent->leftChild = v->rightChild;
			v->rightChild->parent = parent;

			// connect parent as v's right child
			v->rightChild = parent;
			parent->parent = v;

			// recolor
			v->isRed = false;
			parent->isRed = true;
		}
		else{
			RBNode<T> *parent = v->parent;
			RBNode<T> *child = v->rightChild;

			// make child as root of subtree
			if(is_root(parent))
				root = child;
			else{
				if(parent->parent->leftChild == parent)
					parent->parent->leftChild = child;
				else
					parent->parent->rightChild = child;
			}
			child->parent = parent->parent;

			// connect child's left child as v's right child
			v->rightChild = child->leftChild;
			child->leftChild->parent = v;

			// connect child's right child as parent's left child
			parent->leftChild = child->rightChild;
			child->rightChild->parent = parent;

			// connect v as left child of child
			child->leftChild = v;
			v->parent = child;

			// connect parent as right child of child
			child->rightChild = parent;
			parent->parent = child;

			// recolor
			child->isRed = false;
			parent->isRed = true;
		}
	}
	else{
		if(v->leftChild->isRed){
			RBNode<T> *parent = v->parent;
			RBNode<T> *child = v->leftChild;

			// connect child as root of subtree
			if(is_root(parent))
				root = child;
			else{
				if(parent->parent->leftChild == parent)
					parent->parent->leftChild = child;
				else
					parent->parent->rightChild = child;
			}
			child->parent = parent->parent;

			// connect child's left child as parent's right child
			parent->rightChild = child->leftChild;
			child->leftChild->parent = parent;

			// connect child's right child as v's left child
			v->leftChild = child->rightChild;
			child->rightChild->parent = v;

			// connect parent as child's left child
			child->leftChild = parent;
			parent->parent = child;

			// connect v as child's right child
			child->rightChild = v;
			v->parent = child;

			// recolor
			child->isRed = false;
			parent->isRed = true;
		}
		else{
			RBNode<T> *parent = v->parent;

			// connect v as root of subtree
			if(is_root(parent))
				root = v;
			else{
				if(parent->parent->leftChild == parent)
					parent->parent->leftChild = v;
				else
					parent->parent->rightChild = v;
			}
			v->parent = parent->parent;

			// connect v's left child as parent's right child
			parent->rightChild = v->leftChild;
			v->leftChild->parent = parent;

			// connect parent as v's left child
			v->leftChild = parent;
			parent->parent = v;

			// recolor
			v->isRed = false;
			parent->isRed = true;
		}
	}
}

// recolor tree
// should be recursive
template <class T>
void RBTree<T>::recolor(RBNode<T> *v){
	RBNode<T> *sibling;
	if(v->parent->leftChild == v)
		sibling = v->parent->rightChild;
	else
		sibling = v->parent->leftChild;

	sibling->isRed = false;
	v->isRed = false;

	if(!is_root(v->parent)){
		v->parent->isRed = true;
		if(v->parent->parent->isRed)
			solve_double_red(v->parent);
	}
}

template <class T>
void RBTree<T>::solve_double_red(RBNode<T> *n){
	if(!is_root(n) && n->parent->isRed){\
		RBNode<T> *s;
		if(n->parent->parent->leftChild == n->parent)
			s = n->parent->parent->rightChild;
		else
			s = n->parent->parent->leftChild;

		if(s->isRed)
			recolor(n->parent);
		else
			restruct(n->parent);
	}
}

/******************************************************/
/********************* OPERATIONS *********************/
/******************************************************/

// search
template <class T>
RBNode<T>* RBTree<T>::search(string key){
	RBNode<T> *node = this->root;

	while(!is_external(node)){
		if(node->key.compare(key) == 0) break;
		else if(node->key.compare(key) < 0) node = node->rightChild;
		else node = node->leftChild;
	}
	return node;
}

// insert
template <class T>
bool RBTree<T>::insert(string key){
	RBNode<T> *n = search(key);

	if(is_external(n)){
		n->key = key;
		n->isRed = true;	// insert red
		if(is_root(n))
			n->isRed = false;
		n->leftChild = new RBNode<T>("", false, n);
		n->rightChild = new RBNode<T>("", false, n);

		solve_double_red(n);
		return true;
	}
	
	return false;
}

template <class T>
void cleanUpNode(RBNode<T>* node){
	if(node == NULL) return;

	if(node->leftChild != NULL)
		delete node->leftChild;
	if(node->rightChild != NULL)
		delete node->rightChild;
	delete node;
}

template<class T>
RBNode<T>* RBTree<T>::remove_from_binary_tree(string key){
	RBNode<T> *n = search(key);
	if(is_external(n)) return NULL;

	if(!is_external(n->leftChild) && !is_external(n->rightChild)){
		RBNode<T> *v = n->rightChild;
		while(!is_external(v->leftChild))
			v = v->leftChild;

		// connect v's right child to parent
		RBNode<T> *s;	// sibling of v
		v->rightChild->parent = v->parent;
		if(v->parent->leftChild == v){
			v->parent->leftChild = v->rightChild;
			s = v->parent->rightChild;
		}
		else{
			v->parent->rightChild = v->rightChild;
			s = v->parent->leftChild;
		}

		if(v->isRed || v->rightChild->isRed){
			v->rightChild->isRed = false;
			s = NULL;	// do not need to solve double black
		}

		n->key = v->key;
		delete n->value;
		n->value = v->value;
		v->value = NULL;
		v->rightChild = NULL;
		cleanUpNode(v);

		return s;
	}
	else if(!is_external(n->leftChild) && is_external(n->rightChild)){
		n->key = n->leftChild->key;
		delete n->value;
		n->value = n->leftChild->value;
		n->leftChild->value = NULL;

		RBNode<T>* r = n->leftChild;
		n->leftChild = new RBNode<T>("", false, n);

		cleanUpNode(r);
		return NULL;	// solved
	}
	else if(is_external(n->leftChild) && !is_external(n->rightChild)){
		n->key = n->rightChild->key;
		delete n->value;
		n->value = n->rightChild->value;
		n->rightChild->value = NULL;

		RBNode<T>* r = n->rightChild;
		n->rightChild = new RBNode<T>("", false, n);

		cleanUpNode(r);
		return NULL;	// solved
	}
	else{
		if(is_root(n)){
			root = new RBNode<T>("", false, NULL);

			cleanUpNode(n);
			return NULL;
		} 
		
		RBNode<T> *s;
		if(n->parent->leftChild == n){
			n->parent->leftChild = new RBNode<T>("", false, n->parent);
			s = n->parent->rightChild;
		}
		else{
			n->parent->rightChild = new RBNode<T>("", false, n->parent);
			s = n->parent->leftChild;
		}
		
		if(n->isRed)
			s = NULL; // no need to solve

		cleanUpNode(n);
		return s;	// solved
	}
}

template <class T>
void RBTree<T>::solve_double_black(RBNode<T>* s){
	if(is_external(s)) return;

	if(!s->isRed){
		if(s->leftChild->isRed || s->rightChild->isRed){
			// case 1: restruct
			s->isRed = true;
			restruct(s);
		}
		else{
			// case 2: recolor
			if(s->parent->isRed){
				// case 2-1
				s->parent->isRed = false;
				s->isRed = true;
			}
			else{
				s->isRed = true;
				s->parent->isRed = false;
				if(!is_root(s->parent))
					solve_double_black(s->parent);
			}
		}
	}
	else{
		// case 3
		RBNode<T> *z, *r;
		if(s->parent->leftChild == s){
			z = s->leftChild;	// case 3-1
			r = s->parent->rightChild;
		}
		else{
			z = s->rightChild;	// case 3-2
			r = s->parent->leftChild;
		}

		z->isRed = true;
		restruct(s);
		z->isRed = false;

		s->isRed = false;
		r->parent->isRed = true;

		if(r->parent->leftChild == r)
			solve_double_black(r->parent->rightChild);
		else
			solve_double_black(r->parent->leftChild);
	}
}

// remove
template <class T>
bool RBTree<T>::remove(string key){
	RBNode<T> *n = search(key);
	if(is_external(n)) return false;

	RBNode<T> *s = remove_from_binary_tree(key);
	if(s == NULL) return true;	// finishe

	solve_double_black(s);
	return true;
}

template class RBTree<LinkedList>; 