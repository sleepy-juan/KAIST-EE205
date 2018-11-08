#include <iostream>
#include <stdexcept>
#include <string>
#include <cstring>
#include <ctime>
#include <fstream>
#include <sstream>

#include "single_list.h"

using namespace std;

/* DO NOT CHANGE INCLUDED HEADERS */

int main(int argc, char* argv[])
{
  /* 1st arg: input file name , 2nd arg: output file name */
	single_list sl;
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	time_t start, finish;
	time(&start);

	// get input from ifstream
	int msg, pkt;
	string content;
	if(input.is_open()){
		while(!input.eof()){
			input>>msg>>pkt>>content;
			list_elem* elem = new list_elem(msg, pkt, content);

			// find the position to put element in order of (msg, pkt)
			list_elem* prev = NULL;
			list_elem* iter = NULL;
			for(iter = sl.list_head(); iter != NULL; prev = iter, iter = sl.list_next(iter)){
				if(sl.list_get_data1(iter) < msg) continue;
				if(sl.list_get_data1(iter) > msg) break;
				if(sl.list_get_data2(iter) < pkt) continue;
				break;
			}

			if(prev == NULL && iter == NULL){ // empty
				sl.list_insert_front(elem);
			}
			else if(prev == NULL){
				if(sl.list_get_data1(iter) == msg && sl.list_get_data2(iter) == pkt){
					sl.list_replace(iter, elem); // replace
				}
				else{ // or
					sl.list_insert_front(elem);
				}
			}
			else if(iter == NULL){ // last position
				sl.list_insert_after(prev, elem);
			}
			else{
				if(sl.list_get_data1(iter) == msg && sl.list_get_data2(iter) == pkt){
					sl.list_replace(iter, elem); // replace
				}
				else{ // or
					sl.list_insert_after(prev, elem);
				}
			}
		}	
		input.close();
	}
    
    list_elem *print = sl.list_head();
    int i = 1;
    while(1){
        if(print == NULL) break;
        
        if(sl.list_get_data1(print) == i){
            output << "- Message "<<i<<endl;
            for(int j = 1; sl.list_get_data1(print) == i; j++){
                if(sl.list_get_data2(print) == j){
                    output<<sl.list_get_data3(print)<<endl;
                    print = sl.list_next(print);
                    if(print == NULL) break;
                }
                else{
                    output<<"WARNING: packet "<<j<<" of message "<<i<<" is missing"<<endl;
                }
            }
            output << "- End Message "<<i<<endl<<endl;
        }
        i++;
    }

    /*
	// write output to ofstream
	int lastmsg = -1;
	int lastpkt = 0;
	for(list_elem* elem = sl.list_head(); elem != NULL; elem = sl.list_next(elem)){
		msg = sl.list_get_data1(elem);
		pkt = sl.list_get_data2(elem);
		content = sl.list_get_data3(elem);

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
     
     */

	time(&finish);
	output<<endl<<"Running Time: "<<difftime(finish, start)<<" s.";

	output.close();

  ///////////////////////////////////////////////////////
  //                                                   //
  //  SINGLY LINKED LIST RECEIVER IMPLEMENTATION HERE  //
  //                                                   //
  ///////////////////////////////////////////////////////
  
  return 0;
}
