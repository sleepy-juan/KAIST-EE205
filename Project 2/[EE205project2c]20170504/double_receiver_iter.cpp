#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "double_list_iter.h"

using namespace std;

/* YOU CAN CHANGE INCLUDED HEADERS ^0^ */

int main(int argc, char* argv[])
{
	/* 1st arg: input file name , 2nd arg: output file name */

	double_list dl;
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	time_t start, finish;
	time(&start);

	// get input from ifstream
	int msg, pkt;
	string content;
	d_list_elem* prev = NULL;
	if(input.is_open()){
		while(!input.eof()){
			input>>msg>>pkt>>content;
			d_list_elem* elem = new d_list_elem(msg, pkt, content);

			if(prev == NULL){ // initial input
				dl.d_list_insert_front(elem);
				prev = elem;
				continue;
			}

			// find the position to put element in order of (msg, pkt)
			d_list_elem* iter = prev;
			while(iter != dl.d_list_head() && iter != dl.d_list_tail()){
				int iter_msg = dl.d_list_get_data1(iter);
				int iter_pkt = dl.d_list_get_data2(iter);

				// same (msg, pkt)
				if(iter_msg == msg && iter_pkt == pkt){
					dl.d_list_replace(iter, elem);
					break;
				}
				else if(iter_msg > msg || (iter_msg == msg && iter_pkt > pkt)){ // go back
					d_list_elem* next = dl.d_list_prev(iter);
					if(next == dl.d_list_head()){ // front
						dl.d_list_insert_front(elem);
						break;
					}
					if(dl.d_list_get_data1(next) < msg || (dl.d_list_get_data1(next) == msg && dl.d_list_get_data2(next) < pkt)){ // prev passing the element
						dl.d_list_insert_after(next, elem);
						break;
					}
					iter = next;
				}
				else{
					d_list_elem* next = dl.d_list_next(iter);
					if(next == dl.d_list_tail()){ // back
						dl.d_list_insert_back(elem);
						break;
					}
					if(dl.d_list_get_data1(next) > msg || (dl.d_list_get_data1(next) == msg && dl.d_list_get_data2(next) > pkt)){ // prev passing the element
						dl.d_list_insert_before(next, elem);
						break;
					}
					iter = next;
				}
			}

			prev = elem;
		}
		input.close();
	}
	
	///////////////////////////////////////////////////////
	//                                                   //
	//  DOUBLY LINKED LIST RECEIVER IMPLEMENTATION HERE  //
	//                                                   //
	///////////////////////////////////////////////////////

	double_list::Iter p = find(dl.begin(), dl.end(), 4);
	if (p == dl.end())
	{
		output << "No 4th message" << endl;
	}
	else
	{
		output << "4th message exists" << endl;
	}

	time(&finish);
	output<<endl<<"Running Time: "<<difftime(finish, start)<<" s.";

	output.close();


	return 0;
}
