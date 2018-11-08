/*
	linked_list.cpp
	- doubly linked list

	Author @ Juan Lee (juanlee@kaist.ac.kr)
*/

#include "linked_list.h"

////////// Constructor and Destructor //////////

LinkedList::LinkedList(){
	_head = new Element;
	_tail = new Element;
	_head->next = _tail;
	_tail->prev = _head;
	_length = 0;
}

LinkedList::~LinkedList(){
	while(!empty()){
		remove(_head->next);
	}
	delete _head;
	delete _tail;
}

////////// Element-related //////////

string LinkedList::getStringValueOf(Element* element){
	return element->string_value;
}

int LinkedList::getIntValueOf(Element* element){
	return element->int_value;
}

Element* LinkedList::getNextOf(Element* element){
	return element->next;
}

Element* LinkedList::getPrevOf(Element *element){
	return element->prev;
}

Element* LinkedList::get(int index){
	if(index >= _length) return NULL;

	int i = 0;
	Element *iter = _head->next;
	while(i < index){
		i++;
		iter = iter->next;
	}

	return iter;
}

Element* LinkedList::head(){
	return _head;
}

Element* LinkedList::tail(){
	return _tail;
}

Element* LinkedList::front(){
	return _head->next;
}

Element* LinkedList::back(){
	return _tail->prev;
}

////////// insertion //////////

void LinkedList::insertFront(Element* element){
	insertAfter(_head, element);
}

void LinkedList::insertBack(Element* element){
	insertBefore(_tail, element);
}

void LinkedList::insertBefore(Element* target, Element* element){
	if(target == _head) return;

	Element* before = target->prev;

	before->next = element;
	element->next = target;
	target->prev = element;
	element->prev = before;

	_length++;
}

void LinkedList::insertAfter(Element* target, Element* element){
	if(target == _tail) return;

	Element* after = target->next;

	target->next = element;
	element->next = after;
	after->prev = element;
	element->prev = target;

	_length++;
}

////////// replace //////////

void LinkedList::replace(Element* from, Element* to){
	insertBefore(from, to);
	remove(from);
}

////////// remove //////////

void LinkedList::remove(Element* element){
	element->prev->next = element->next;
	element->next->prev = element->prev;

	delete element;
	_length--;
}

////////// number of elements //////////

int LinkedList::length(){
	return _length;
}

bool LinkedList::empty(){
	return _length == 0;
}