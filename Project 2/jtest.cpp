/*
	jtest.cpp
	- test program for EE205 Data Structures and Algorithms for Electrical Engineering

	Author @ Juan Lee (juanlee@kaist.ac.kr), School of Computing, KAIST
*/

#include <iostream>
#include <stdio.h>
using namespace std;

// linked lists
#include "double_list.h"
#include "single_list.h"

// test functions declaration
void TEST_2a();
void TEST_2as();
void TEST_2ad();
void TEST_2b();
void TEST_2bs();
void TEST_2bd();

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void redPrint(const char* msg){
	printf("%s%s%s", ANSI_COLOR_RED, msg, ANSI_COLOR_RESET);
}

void yellowPrint(const char* msg){
	printf("%s%s%s", ANSI_COLOR_YELLOW, msg, ANSI_COLOR_RESET);
}

void greenPrint(const char* msg){
	printf("%s%s%s", ANSI_COLOR_GREEN, msg, ANSI_COLOR_RESET);
}

/*
	main: void -> int
	- main function of this program
*/
int main(int argc, char* argv[]){

	greenPrint("JTEST Running...\n");
	greenPrint("Author @ Juan Lee (juanlee@kaist.ac.kr), School of Computing, KAIST\n\n");

	TEST_2a();
	TEST_2b();
	return 0;
}

/*
	TEST_2a: void -> void
	- test for 2-a
*/
void TEST_2a(){
	TEST_2as();
	TEST_2ad();
}

/*
	TEST_2as: void -> void
	- test for 2-a Single
*/
void TEST_2as(){
	cout<<"========== TEST FOR 2A Single =========="<<endl;

	////////////////////////////////////////////////////////////////////////////
	int score = 0, nProblems = 0;
	single_list sl;
	list_elem *head, *next, *next_of_next;				// search
	list_elem *first, *before_first, *after_first;		// contained
	list_elem *dummy1, *dummy2, *dummy3;					// dummy
	int data1, data2;
	string data3;

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-1]\t");
	cout<<"initial head is NULL ...";
	nProblems++;

	head = sl.list_head();
	if(head == NULL){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-2]\t");
	cout<<"initially empty ...";
	nProblems++;

	if(sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-3]\t");
	cout<<"insert front ...";
	nProblems++;

	first = new list_elem(1, 1, "first data");
	sl.list_insert_front(first);
	head = sl.list_head();
	if(first == head && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-4]\t");
	cout<<"insert before ...";
	nProblems++;

	before_first = new list_elem(1, 2, "before first");
	sl.list_insert_before(first, before_first);
	head = sl.list_head();
	next = sl.list_next(head);
	if(before_first == head && first == next && !sl.list_empty() && head != next){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-5]\t");
	cout<<"insert after ...";
	nProblems++;

	after_first = new list_elem(1, 3, "after first");
	sl.list_insert_after(first, after_first);
	head = sl.list_head();
	next = sl.list_next(head);
	next_of_next = sl.list_next(next);
	if(before_first == head && first == next && after_first == next_of_next && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-6]\t");
	cout<<"replace first ...";
	nProblems++;

	dummy1 = new list_elem(2, 1, "dummy 2-1");
	sl.list_replace(before_first, dummy1);
	head = sl.list_head();
	next = sl.list_next(head);
	next_of_next = sl.list_next(next);
	if(dummy1 == head && first == next && after_first == next_of_next && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-7]\t");
	cout<<"replace middle ...";
	nProblems++;

	dummy2 = new list_elem(2, 2, "dummy 2-2");
	sl.list_replace(first, dummy2);
	head = sl.list_head();
	next = sl.list_next(head);
	next_of_next = sl.list_next(next);
	if(dummy1 == head && dummy2 == next && after_first == next_of_next && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-8]\t");
	cout<<"replace last ...";
	nProblems++;

	dummy3 = new list_elem(2, 3, "dummy 2-3");
	sl.list_replace(after_first, dummy3);
	head = sl.list_head();
	next = sl.list_next(head);
	next_of_next = sl.list_next(next);
	if(dummy1 == head && dummy2 == next && dummy3 == next_of_next && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-9]\t");
	cout<<"get data ...";
	nProblems++;

	data1 = sl.list_get_data1(dummy1);
	data2 = sl.list_get_data2(dummy1);
	data3 = sl.list_get_data3(dummy1);
	if(data1 == 2 && data2 == 1 && data3 == "dummy 2-1" && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-10]\t");
	cout<<"remove middle ...";
	nProblems++;

	sl.list_remove(dummy2);

	head = sl.list_head();
	next = sl.list_next(head);
	next_of_next = sl.list_next(next);
	if(dummy1 == head && dummy3 == next && next_of_next == NULL && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-11]\t");
	cout<<"remove last ...";
	nProblems++;

	sl.list_remove(dummy3);

	head = sl.list_head();
	next = sl.list_next(head);
	if(dummy1 == head && next == NULL && !sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-12]\t");
	cout<<"remove first ...";
	nProblems++;

	sl.list_remove(dummy1);

	head = sl.list_head();
	if(head == NULL && sl.list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2as-13]\t");
	cout<<"test for insert big data ...";
	nProblems++;

	for(int i=1; i<100; i++){
		for(int j=1; j<100; j++){
			sl.list_insert_front(new list_elem(i, j, "dummy"));
		}
	}

	head = sl.list_head();
	bool flag = true;
	for(int i=99; i>0; i--){
		for(int j=99; j>0; j--){
			data1 = sl.list_get_data1(head);
			data2 = sl.list_get_data2(head);
			head = sl.list_next(head);

			//cout<<"real : ("<<i<<","<<j<<") but you : ("<<data1<<","<<data2<<")"<<endl;
			
			if(data1 != i || data2 != j){
				flag = false;
				break;
			}
		}
		if(!flag) break;
	}

	if(flag){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	cout<<"You have passed "<<score<<" of "<<nProblems<<endl;
	cout<<"========== FINISHED FOR 2A Single =========="<<endl<<endl;
}

/*
	TEST_2ad: void -> void
	- test for 2-a Double
*/
void TEST_2ad(){
	cout<<"========== TEST FOR 2A Double =========="<<endl;

	////////////////////////////////////////////////////////////////////////////
	int score = 0, nProblems = 0;
	double_list dl;
	d_list_elem *head, *next, *next_of_next, *tail;			// search
	d_list_elem *first, *before_first, *after_first, *back;	// contained
	d_list_elem *dummy1, *dummy2, *dummy3;					// dummy
	int data1, data2;
	string data3;

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-1]\t");
	cout<<"initial head and tail ...";
	nProblems++;

	head = dl.d_list_head();
	tail = dl.d_list_tail();
	if(dl.d_list_next(head) == tail && dl.d_list_prev(tail) == head){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-2]\t");
	cout<<"initial front and back ...";
	nProblems++;

	head = dl.d_list_front();
	tail = dl.d_list_back();
	if(head == NULL && tail == NULL){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-3]\t");
	cout<<"prev of head ...";
	nProblems++;

	head = dl.d_list_prev(dl.d_list_head());
	if(head == NULL){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-4]\t");
	cout<<"next of tail ...";
	nProblems++;

	tail = dl.d_list_next(dl.d_list_tail());
	if(tail == NULL){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-5]\t");
	cout<<"initially empty ...";
	nProblems++;

	if(dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-6]\t");
	cout<<"insert before head ...";
	nProblems++;

	first = new d_list_elem(1, 1, "first data");
	dl.d_list_insert_before(dl.d_list_head(), first);

	if(dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
		delete first;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-7]\t");
	cout<<"insert after tail ...";
	nProblems++;

	first = new d_list_elem(1, 1, "first data");
	dl.d_list_insert_after(dl.d_list_tail(), first);

	if(dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
		delete first;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-8]\t");
	cout<<"insert front ...";
	nProblems++;

	first = new d_list_elem(1, 1, "first data");
	dl.d_list_insert_front(first);
	head = dl.d_list_front();
	if(first == head && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-9]\t");
	cout<<"insert before ...";
	nProblems++;

	before_first = new d_list_elem(1, 2, "before first");
	dl.d_list_insert_before(first, before_first);
	head = dl.d_list_front();
	next = dl.d_list_next(head);
	if(before_first == head && first == next && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-10]\t");
	cout<<"insert after ...";
	nProblems++;

	after_first = new d_list_elem(1, 3, "after first");
	dl.d_list_insert_after(first, after_first);
	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	if(before_first == head && first == next && after_first == next_of_next && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-11]\t");
	cout<<"insert back ...";
	nProblems++;

	back = new d_list_elem(1, 4, "back");
	dl.d_list_insert_back(back);

	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	tail = dl.d_list_next(next_of_next);
	if(before_first == head && first == next && after_first == next_of_next && back == tail && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-12]\t");
	cout<<"replace first ...";
	nProblems++;

	dummy1 = new d_list_elem(2, 1, "dummy 2-1");
	dl.d_list_replace(before_first, dummy1);
	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	tail = dl.d_list_next(next_of_next);
	if(dummy1 == head && first == next && after_first == next_of_next && back == tail && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-13]\t");
	cout<<"replace middle ...";
	nProblems++;

	dummy2 = new d_list_elem(2, 2, "dummy 2-2");
	dl.d_list_replace(first, dummy2);
	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	tail = dl.d_list_next(next_of_next);
	if(dummy1 == head && dummy2 == next && after_first == next_of_next && back == tail && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-14]\t");
	cout<<"replace last ...";
	nProblems++;

	dummy3 = new d_list_elem(2, 3, "dummy 2-3");
	dl.d_list_replace(back, dummy3);
	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	tail = dl.d_list_next(next_of_next);
	if(dummy1 == head && dummy2 == next && after_first == next_of_next && dummy3 == tail && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-15]\t");
	cout<<"get data ...";
	nProblems++;

	data1 = dl.d_list_get_data1(dummy1);
	data2 = dl.d_list_get_data2(dummy1);
	data3 = dl.d_list_get_data3(dummy1);
	if(data1 == 2 && data2 == 1 && data3 == "dummy 2-1" && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-16]\t");
	cout<<"remove middle ...";
	nProblems++;

	dl.d_list_remove(dummy2);

	head = dl.d_list_front();
	next = dl.d_list_next(head);
	next_of_next = dl.d_list_next(next);
	tail = dl.d_list_next(next_of_next);
	if(dummy1 == head && after_first == next && dummy3 == next_of_next && tail == dl.d_list_tail() && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-17]\t");
	cout<<"remove last ...";
	nProblems++;

	dl.d_list_remove(dummy3);

	head = dl.d_list_front();
	next = dl.d_list_next(head);
	tail = dl.d_list_next(next);
	if(dummy1 == head && next == after_first && tail == dl.d_list_tail() && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-18]\t");
	cout<<"remove first ...";
	nProblems++;

	dl.d_list_remove(dummy1);

	head = dl.d_list_front();
	tail = dl.d_list_next(head);
	if(head == after_first && tail == dl.d_list_tail() && !dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-19]\t");
	cout<<"remove all ...";
	nProblems++;

	dl.d_list_remove(dl.d_list_front());

	head = dl.d_list_front();
	if(head == NULL && dl.d_list_empty()){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	yellowPrint("[TEST 2ad-20]\t");
	cout<<"test for insert big data ...";
	nProblems++;

	for(int i=1; i<100; i++){
		for(int j=1; j<100; j++){
			dl.d_list_insert_front(new d_list_elem(i, j, "dummy"));
		}
	}

	head = dl.d_list_front();
	bool flag = true;
	for(int i=99; i>0; i--){
		for(int j=99; j>0; j--){
			data1 = dl.d_list_get_data1(head);
			data2 = dl.d_list_get_data2(head);
			head = dl.d_list_next(head);
			
			if(data1 != i || data2 != j){
				flag = false;
				break;
			}
		}
		if(!flag) break;
	}

	if(flag){
		greenPrint("PASS\n");
		score++;
	}
	else{
		redPrint("FAIL\n");
	}

	////////////////////////////////////////////////////////////////////////////
	cout<<"You have passed "<<score<<" of "<<nProblems<<endl;
	cout<<"========== FINISHED FOR 2A Double =========="<<endl<<endl;
}