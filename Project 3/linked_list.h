/*
	linked_list.h
	- doubly linked list

	Author @ Juan Lee (juanlee@kaist.ac.kr)
*/

#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <string>

using namespace std;

class LinkedList;

class Element{
	friend class LinkedList;

private:
	string string_value;
	int int_value;
	Element *next;
	Element *prev;

public:
	Element(){
		next = NULL;
		prev = NULL;
	}
	Element(string value, Element* next = NULL, Element* prev = NULL){
		this->string_value = value;
		this->next = next;
		this->prev = prev;
	}
	Element(int value, Element* next = NULL, Element* prev = NULL){
		this->int_value = value;
		this->next = next;
		this->prev = prev;
	}
};

class LinkedList{
private:
	Element *_head;
	Element *_tail;
	int _length;

public:
	LinkedList();
	~LinkedList();

	string getStringValueOf(Element *);
	int getIntValueOf(Element *);

	Element* getNextOf(Element *);
	Element* getPrevOf(Element *);
	Element* get(int);

	Element* head();
	Element* tail();
	Element* front();
	Element* back();

	void insertFront(Element*);
	void insertBack(Element*);
	void insertBefore(Element*, Element*);
	void insertAfter(Element*, Element*);

	void replace(Element*, Element*);

	void remove(Element*);

	int length();
	bool empty();
};

#endif /* __LINKED_LIST__ */
