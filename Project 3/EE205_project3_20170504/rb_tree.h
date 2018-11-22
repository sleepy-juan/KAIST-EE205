/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <string>
#include <iostream>

using namespace std;

/* 
* ############################CAUTION!!!############################
* You can define any additional features for your debugging purpose,
* but make sure you remove all of them before you submit this.
* ##################################################################
*/

template <class T>
class RBNode {
public:
	string key;
	T *value;
	int height;
	bool isRed;

	class RBNode<T> *leftChild;
	class RBNode<T> *rightChild;
	class RBNode<T> *parent;

	RBNode(string k, bool r, RBNode<T> *p){
		key = k;
		leftChild = NULL;
		rightChild = NULL;
		parent = p;

		value = new T;
		height = 0;
		isRed = r;
	}

	~RBNode(){
		if(value != NULL)
			delete value;
	}
};

template<class T>
class RBTree {
public:
	RBTree();
	~RBTree();
	void display();
	void displayRB();

	bool insert(string key);
	bool remove(string key);
	RBNode<T>* search(string key);

	bool is_external(RBNode<T> *n);
	bool is_root(RBNode<T> *n);

private:
	RBNode<T> *root;
	int height(RBNode<T> *n);
	void update_height(RBNode<T> *n);

	void inorder_print(RBNode<T> *n);
	void preorder_print(RBNode<T> *n);
	void inorder_printRB(RBNode<T> *n);
	void preorder_printRB(RBNode<T> *n);

	void restruct(RBNode<T> *v);
	void recolor(RBNode<T> *v);
	void solve_double_black(RBNode<T> *s);
	void solve_double_red(RBNode<T> *s);
	RBNode<T>* remove_from_binary_tree(string key);
};

#endif /* __RB_TREE_H__ */