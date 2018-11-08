#include <iostream>
#include <string>

#include "single_list.h"

using namespace std;


//////////////////////////////////////////////
// CAUTION: DO NOT CHANGE INCLUDED HEADERS  //
//////////////////////////////////////////////


/* Our singly linked lists have one header elements: the "head" which
   points the first element. The "next" link of the back header is
   NULL. 
   An empty list looks like this:

                  
          HEAD ---> NULL 
                  

   A list with two elements in it looks like this:
   
                   +-------+    +-------+
          HEAD --->|   1   |--->|   2   |--->NULL
                   +-------+    +-------+

   You should not change the name, input arguments, and
   input/output data types of existing functions. */



/*** COMPLETE FUNCTIONS BELOW ***/

/* SINGLY LINKED LIST */

/* Initializes LIST as an empty list with a head. */
single_list::single_list()
{
  /*** MODIFY HERE ***/
	this->head = NULL;
}

single_list::~single_list()
{
  /*** MODIFY HERE ***/
	while(this->head != NULL){
		this->list_remove(this->head);
	}
}

int
single_list::list_get_data1(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data1;
}

int
single_list::list_get_data2(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data2;
}

string
single_list::list_get_data3(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data3;
}


/* Returns the element after ELEM in its list. */
list_elem *
single_list::list_next (list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->next;
}


/* Returns LIST's head. */
list_elem *
single_list::list_head (void)
{
  /*** MODIFY HERE ***/
	return this->head;
}

/* Insert ELEM at the beginning of LIST, so that it becomes the head 
   in LIST. */
void 
single_list::list_insert_front (list_elem *elem)
{
    /*** MODIFY HERE ***/
    elem->next = this->head;
    this->head = elem;
}

/* Insert ELEM just before BEFORE, which may be either an interior
 element or a head. */
void 
single_list::list_insert_before (list_elem *before, list_elem *elem)
{
  /*** MODIFY HERE ***/
	if(before == this->head){
		this->list_insert_front(elem);
		return;
	}

	list_elem* left_of_before = this->head;
	while(left_of_before->next != before)
		left_of_before = left_of_before->next;
	left_of_before->next = elem;
	elem->next = before;
}

/* Insert ELEM just after AFTER, which may be either an interior
 element or a head. */
void 
single_list::list_insert_after (list_elem *after, list_elem *elem)
{
  /*** MODIFY HERE ***/
	list_elem* right_of_after = after->next;
	after->next = elem;
	elem->next = right_of_after;
}

/* Replace FROM with TO and deconstruct FROM */
void 
single_list::list_replace (list_elem *from, list_elem *to)
{
  /*** MODIFY HERE ***/
	this->list_insert_before(from, to);
	to->next = from->next;
	delete from;
}


/* Removes ELEM from its list and deconstructs it. */
void
single_list::list_remove (list_elem *elem)
{
  /*** MODIFY HERE ***/
	if(elem == this->head){
		this->head = elem->next;
		delete elem;
		return;
	}

	list_elem* before = this->head;
	while(before->next != elem)
		before = before->next;
	before->next = elem->next;
	delete elem;
}

/* Returns true if LIST is empty, false otherwise. */
bool 
single_list::list_empty (void)
{
  /*** MODIFY HERE ***/
  return this->head == NULL;  
}


