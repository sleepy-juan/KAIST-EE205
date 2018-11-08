#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "double_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

int main(int argc, char* argv[])
{
	/* 1st arg: input file name , 2nd arg: output file name */
	double_list dl;
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	/* T_start = the time that reciever starts */
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

	// write output to ofstream
	int lastmsg = -1;
	int lastpkt = 0;
	for(d_list_elem* elem = dl.d_list_front(); elem != NULL && elem != dl.d_list_tail(); elem = dl.d_list_next(elem)){
		msg = dl.d_list_get_data1(elem);
		pkt = dl.d_list_get_data2(elem);
		content = dl.d_list_get_data3(elem);

		if(msg != lastmsg){ // start of new message
			if(lastmsg != -1) // if prev message exists
				output<<"- End Message "<<lastmsg<<endl<<endl;
			output<<"- Message "<<msg<<endl;

			lastmsg = msg;
			lastpkt = 0;
		}

		if(lastpkt + 1 != pkt){ // packet loss
			// packet loss
			for(int pktnum = lastpkt+1; pktnum<pkt; pktnum++)
				output<<"WARNING: packet "<<pktnum<<" of message "<<msg<<" is missing"<<endl;
			output<<content<<endl;
			lastpkt = pkt;
		}
		else{
			output<<content<<endl;
			lastpkt++;
		}
	}

	// for ending of last message
	if(lastmsg != -1)
		output<<"- End Message "<<lastmsg<<endl;

	time(&finish);
	output<<endl<<"Running Time: "<<difftime(finish, start)<<" s.";

	output.close();
	
	///////////////////////////////////////////////////////
	//                                                   //
	//  DOUBLY LINKED LIST RECEIVER IMPLEMENTATION HERE  //
	//                                                   //
	///////////////////////////////////////////////////////

	/* T_finish = the time that reciever finishes */

	/* Write to the output file "Running Time: (T_finish-T_start) s." */

	return 0;
}
