#include <iostream>
#include <string>

#include "double_list_iter.h"

using namespace std;

//////////////////////////////////////////////
// YOU CAN CHANGE INCLUDED HEADERS ^0^ //
//////////////////////////////////////////////

/* Our doubly linked lists have two header elements: the "head"
   just before the first element and the "tail" just after the
   last element. The "prev" link of the front header is null, as
   is the "next" link of the back header. Their other two links
   point toward each other via the interior elements of the list.

   An empty list looks like this:

                      +------+     +------+
                  <---| head |<--->| tail |--->
                      +------+     +------+

   A list with two elements in it looks like this:

        +------+     +-------+     +-------+     +------+
    <---| head |<--->|   1   |<--->|   2   |<--->| tail |<--->
        +------+     +-------+     +-------+     +------+

   The symmetry of this arrangement eliminates lots of special
   cases in list processing. That's a lot simpler than the code 
   would be without header elements.

   (Because only one of the pointers in each header element is used,
   we could in fact combine them into a single header element
   without sacrificing this simplicity.  But using two separate
   elements allows us to do a little bit of checking on some
   operations, which can be valuable.) 

   You SHOULD NOT change the name, input arguments, and
   input/output data types of existing functions. */

// double list

double_list::double_list()
{
  /*** MODIFY HERE ***/
  this->head = new d_list_elem;
  this->tail = new d_list_elem;

  this->head->next = this->tail;
  this->tail->prev = this->head;
}

double_list::~double_list()
{
  /*** MODIFY HERE ***/
  while(this->head->next != this->tail){
    this->d_list_remove(this->head->next);
  }
  delete this->head;
  delete this->tail;
}

int
double_list::d_list_get_data1(d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  return elem->data1;
}

int
double_list::d_list_get_data2(d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  return elem->data2;
}

string
double_list::d_list_get_data3(d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  return elem->data3;
}

/* Returns the element before ELEM in its list. If ELEM is the first 
   element in its list, returns the list head. Results are undefined 
   if ELEM is itself a list head. */
d_list_elem *
double_list::d_list_prev (d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  return elem->prev;
}

/* Returns the element after ELEM in its list. If ELEM is the last
   element in its list, returns the list tail. Return NULL if ELEM is
   itself a list tail. */
d_list_elem *
double_list::d_list_next (d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  return elem->next;
}


/* Returns LIST's head. */
d_list_elem *
double_list::d_list_head (void)
{
  /*** MODIFY HERE ***/
  return this->head;
}

/* Returns LIST's tail. */
d_list_elem *
double_list::d_list_tail (void)
{
  /*** MODIFY HERE ***/
  return this->tail;
}

/* Returns the front element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_front (void)
{
  /*** MODIFY HERE ***/
  if(this->head->next == this->tail)
    return NULL;
  return this->head->next;
}

/* Returns the back element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_back (void)
{
  /*** MODIFY HERE ***/
  if(this->tail->prev == this->head)
    return NULL;
  return this->tail->prev;
}


/* Insert ELEM at the beginning of LIST, so that it becomes the front 
   in LIST. */
void 
double_list::d_list_insert_front (d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  this->d_list_insert_after(this->head, elem);
}

/* Insert ELEM at the end of LIST, so that it becomes the back in LIST. */
void 
double_list::d_list_insert_back (d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  this->d_list_insert_before(this->tail, elem);
}

/* Insert ELEM just before BEFORE, which may be either an interior
 element or a tail. The latter case is equivalent to list_insert_back().
 Results are undefined if BEFORE is itself a list head. */
void 
double_list::d_list_insert_before (d_list_elem *before, d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  if(before == this->head) return;
  elem->next = before;
  elem->prev = before->prev;
  elem->prev->next = elem;
  elem->next->prev = elem;
}

/* Insert ELEM just after AFTER, which may be either an interior
 element or a head. The latter case is equivalent to list_insert_front().
 Results are undefined if AFTER is itself a list tail. */
void 
double_list::d_list_insert_after (d_list_elem *after, d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  if(after == this->tail) return;
  elem->prev = after;
  elem->next = after->next;
  elem->next->prev = elem;
  elem->prev->next = elem;
}

/* Replace FROM with TO and deconstruct FROM*/
void 
double_list::d_list_replace (d_list_elem *from, d_list_elem *to)
{
  /*** MODIFY HERE ***/
  from->prev->next = to;
  from->next->prev = to;
  to->prev = from->prev;
  to->next = from->next;
  delete from;
}


/* Removes ELEM from its list and deconstructu it.
   Undefined behavior if ELEM is not in a list. Results are undefined
   if ELEM is not an interior element of its list.
*/

void
double_list::d_list_remove (d_list_elem *elem)
{
  /*** MODIFY HERE ***/
  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;
  delete elem;
}

/* Returns true if LIST is empty, false otherwise. */
bool 
double_list::d_list_empty (void)
{
  /*** MODIFY HERE ***/
  return this->head->next == this->tail;
}

// iterator

double_list::Iter& double_list::Iter::operator++(){
	this->v = this->v->next;
	return *this;
}

double_list::Iter& double_list::Iter::operator--(){
	this->v = this->v->prev;
	return *this;
}

bool double_list::Iter::operator==(const Iter& other) const {
	return this->v == other.v;
}

bool double_list::Iter::operator!=(const Iter& other) const {
	return this->v != other.v;
}

//bool double_list::Iter::operator==(const int value){
//  if(this->v == NULL) return false;
//  return this->v->data1 == value;
//}

//bool double_list::Iter::operator!=(const int value){
//  if(this->v == NULL) return false;
//  return this->v->data1 != value;
//}

int& double_list::Iter::operator*(){
	return this->v->data1;
}

double_list::Iter::Iter(d_list_elem* u){
  v = u;
}

// function for iterator

double_list::Iter double_list::begin(){
	return double_list::Iter(this->d_list_front());
}

double_list::Iter double_list::end(){
	return double_list::Iter(this->d_list_tail());
}