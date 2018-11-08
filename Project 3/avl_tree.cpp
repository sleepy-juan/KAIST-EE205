/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo.
*/

#include "avl_tree.h"
#include <iostream>
#include <string>

/* 
* Include your linked list here 
* e.g., #include "your_linked_list_header.h"
*/
#include "linked_list.h"

using namespace std;

/* 
* You can do this! Feel free to ask to TA if you have anything unclear. 
* I'm here to help you!
*/

/* Return the height of the tree. Remember external nodes are valid nodes. 
* Suppose we have a tree as follows. * means an external node.
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this tree has the height of 3
*
* ### Already implemented.
*/
template <class T>
int AVLTree<T>::height(AVLNode<T> *n) {
	return n->height;
}

/*
* Assign proper height value after operations on nodes.
* You will need this function in some functions.
* such as rotate_right(), rotate_left(), balance(), etc.
*
* Make sure all children have proper heights before you execute
* this function on a node.
*
* ### Already implemented.
*/
template <class T>
void AVLTree<T>::update_height(AVLNode<T> *n) {
	if (is_external(n)) {
		n->height = 0;
	}
	else {
		int lh = height(n->leftChild);
		int rh = height(n->rightChild);

		n->height = (lh >= rh ? lh : rh) + 1;
	}
}

/* Print keys along inorder traversal. Separate each key by a single space.
* Do not print external node's key, which is an empty string. The input is
* the root node of the tree you want to tarverse.
* e.g.,
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this function should print "d b a c " (with no newline character).
* 
*/
template <class T>
void AVLTree<T>::inorder_print(AVLNode<T> *n) {
	if(!is_external(n->leftChild))
		inorder_print(n->leftChild);
	cout << n->key << " ";
	if(!is_external(n->rightChild))
		inorder_print(n->rightChild);
}

/* 
* Print keys along preorder traversal. 
* The rule is the same as inorder_print(), except the order. 
*/
template <class T>
void AVLTree<T>::preorder_print(AVLNode<T> *n) {
	cout << n->key << " ";
	if(!is_external(n->leftChild))
		preorder_print(n->leftChild);
	if(!is_external(n->rightChild))
		preorder_print(n->rightChild);
}

/* Refer to the supplementary PPT file. */
template <class T>
void AVLTree<T>::balance(AVLNode<T> *n) {
	AVLNode<T> *iter = n;
	while(iter != NULL){
		int factor = balance_factor(iter);

		if(factor == -2) {		// In case of left rotation
			if(height(iter->rightChild->leftChild) <= height(iter->rightChild->rightChild)){
				if(is_root(iter))
					root = rotate_left(iter);
				else
					rotate_left(iter);
			}
			else{	// double rotation is needed.
				rotate_right(iter->rightChild);
				if(is_root(iter))
					root = rotate_left(iter);
				else
					rotate_left(iter);
			}

			break;
		}
		else if(factor == 2) {	// In case of right rotation
			if(height(iter->leftChild->leftChild) >= height(iter->leftChild->rightChild)){
				if(is_root(iter))
					root = rotate_right(iter);
				else
					rotate_right(iter);
			}
			else{	// double rotation is needed.
				rotate_left(iter->leftChild);
				if(is_root(iter))
					root = rotate_right(iter);
				else
					rotate_right(iter);
			}

			break;
		}
		
		update_height(iter);
		iter = iter->parent;
	}
}

/* For your reference, the function has already been implemented. */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T> *n) {
	AVLNode<T> *x = n->leftChild;

	n->leftChild = x->rightChild;
	n->leftChild->parent = n;

	x->rightChild = n;
	x->parent = n->parent;

	if (!is_root(n)) {
		if (n->parent->leftChild == n)
			n->parent->leftChild = x;
		else
			n->parent->rightChild = x;
	}
	n->parent = x;

	/* the order of updates is important */
	update_height(n);
	update_height(x);

	return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T> *n) {
	AVLNode<T> *x = n->rightChild;

	n->rightChild = x->leftChild;
	n->rightChild->parent = n;

	x->leftChild = n;
	x->parent = n->parent;

	if(!is_root(n)){
		if (n->parent->leftChild == n)
			n->parent->leftChild = x;
		else
			n->parent->rightChild = x;
	}
	n->parent = x;

	/* update height */
	update_height(n);
	update_height(x);

	return x;
}

/* 
* Refer to page 6 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
* Use string::compare function for comparison between two keys.
*/
template <class T>
AVLNode<T>* AVLTree<T>::search(string key) {
	AVLNode<T> *node = this->root;

	while(!is_external(node)){
		if(node->key.compare(key) == 0) break;
		else if(node->key.compare(key) < 0) node = node->rightChild;
		else node = node->leftChild;
	}
	return node;
}

/*
* I have also implemented this function for your reference and convenience. 
* 조교 자비 오지고 지리고 렛잇고 아리랑 고개를 넘ㅇ...
*/
template <class T>
bool AVLTree<T>::insert(string key) {
	AVLNode<T> *n = search(key);

	if (is_external(n)) {
		n->key = key;
		n->leftChild = new AVLNode<T>("", n);
		n->rightChild = new AVLNode<T>("", n);

		balance(n);

		return true;
	}
	else
		return false; // the key already exists
}

template <class T>
void cleanUpNode(AVLNode<T>* node){
	if(node != NULL){
		if(node->leftChild != NULL){
			if(node->leftChild->value != NULL)
				delete node->leftChild->value;
			delete node->leftChild;
		}	
		if(node->rightChild != NULL){
			if(node->rightChild->value != NULL)
				delete node->rightChild->value;
			delete node->rightChild;
		}
		if(node->value != NULL)
			delete node->value;
		delete node;
	}
}

/* 
* Remove a node. Return true if successful(if the key exists), false otherwise. 
* Refer to page 8~9, 22~23 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
*/
template <class T>
bool AVLTree<T>::remove(string key) {
	AVLNode<T> *n = search(key);
	if(is_external(n)) return false;

	// if node has no right children
	if(is_external(n->rightChild)){
		if(is_root(n)){	// n is root
			root = n->leftChild;
			root->parent = NULL;
		}
		else{
			n->leftChild->parent = n->parent;
			if(n->parent->leftChild == n)
				n->parent->leftChild = n->leftChild;
			else
				n->parent->rightChild = n->leftChild;
		}

		n->leftChild = NULL;
		cleanUpNode(n);
		return true;
	}

	// find node to exchange
	AVLNode<T> *r = n->rightChild;
	while(!is_external(r)) r = r->leftChild;
	r = r->parent;

	// disconnect
	if(r->parent->leftChild == r)
		r->parent->leftChild = new AVLNode<T>("", r->parent);
	else
		r->parent->rightChild = new AVLNode<T>("", r->parent);

	// exchange
	n->key = r->key;
	delete n->value;
	n->value = r->value;
	r->value = NULL;
	cleanUpNode(r);

	return true;
}

/* 
* You need to explicitly instantiate the template to use it in the main function.
* Instantiate here if you need to.
* e.g., 
* template class AVLTree<Your_linkedlist_class>;
*/
template class AVLTree<LinkedList>; 

/* You can do it! */

