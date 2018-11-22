/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <regex>
#include "rb_tree.h"
/* Include more if you need */
#include "linked_list.h"

using namespace std;

/* Use these functions to replace words in a string.
* Make sure you add -std=c++11 option when you compile.
*/
void replace_all(string& str, const string& from, const string& to) {

	string whitespaces[] = {" ", "\t", "\n", "\f", "\r", "\v"};

	for(string white: whitespaces){
		std::regex reg1("^" + from + white, std::regex_constants::icase);
	    str = string(std::regex_replace(str, reg1, to + white));

	    std::regex reg2(white + from + "$", std::regex_constants::icase);
	    str = string(std::regex_replace(str, reg2, white + to));

	    for(string another: whitespaces){
	    	std::regex reg3(white + from + another, std::regex_constants::icase);
	    	str = string(std::regex_replace(str, reg3, white + to + another));
	    	str = string(std::regex_replace(str, reg3, white + to + another));
		}
	}
	std::regex reg4("^" + from + "$", std::regex_constants::icase);
	str = string(std::regex_replace(str, reg4, to));
}


int main(int argc, char* argv[])
{
	/* args: input filename, output filename */
	ifstream input(argv[1]);
	ofstream output(argv[2]);

	/* variables */
	RBTree<LinkedList> tree;
	LinkedList list;

	/* read lines from file */
	if(input.is_open()){
		while(!input.eof()){
			string line;
			getline(input, line);

			// insert into list
			list.insertBack(new Element(line));

			// insert words into tree
			stringstream ss(line);
			string word;
			while(ss>>word){
				// store as lower case for case insensitive
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				tree.insert(word);

				LinkedList* words_list = tree.search(word)->value;
				if(words_list->empty())
					words_list->insertBack(new Element(list.length() - 1));
				else{
					if(words_list->getIntValueOf(words_list->back()) != list.length() - 1){
						words_list->insertBack(new Element(list.length() - 1));
					}
				}
			}
		}
	}
	input.close();

	// handle commands
	string line;
	getline(cin, line);
	while(line != "Q"){
		string command, from, to;
		stringstream ss(line);
		ss>>command>>from>>to;

		if(command == "R"){
			string lower_from = from;
			string lower_to = to;
			// for case insensitive
			std::transform(lower_from.begin(), lower_from.end(), lower_from.begin(), ::tolower);
			std::transform(lower_to.begin(), lower_to.end(), lower_to.begin(), ::tolower);

			RBNode<LinkedList> *node_from = tree.search(lower_from);
			RBNode<LinkedList> *node_to = tree.search(lower_to);

			if(tree.is_external(node_to)){
				tree.insert(lower_to);
				node_to = tree.search(lower_to);
			}

			LinkedList* words_from = node_from->value;
			LinkedList*	words_to = node_to->value;
			for(Element* head = words_from->front(); head != words_from->tail(); head = words_from->getNextOf(head)){
				int num = words_from->getIntValueOf(head);

				// replace text
				Element *line_from = list.get(num);
				string str_line = list.getStringValueOf(line_from);
				cout<<"< "<<str_line<<endl;

				replace_all(str_line, from, to);
				cout<<"> "<<str_line<<endl<<endl;
				list.replace(line_from, new Element(str_line));

				if(lower_from != lower_to){
					// replace tree
					if(words_to->empty() || words_to->getIntValueOf(words_to->back()) < num){
						words_to->insertBack(new Element(num));
					}
					else{
						Element* front = words_to->front();
						while(front != words_to->tail()){
							int value = words_to->getIntValueOf(front);

							if(value == num) break;
							else if(value > num){
								words_to->insertBefore(front, new Element(num));
								break;
							}
							else
								front = words_to->getNextOf(front);
						}
					}
				}
			}

			// remove node
			if(lower_from != lower_to)
				tree.remove(lower_from);
		}

		getline(cin, line);
	}

	// store them into output
	for(Element* iter = list.front(); iter != list.tail(); iter = list.getNextOf(iter)){
		output<<list.getStringValueOf(iter);
		if(iter != list.back())
			output<<endl;
	}

	output.close();
	return 0;
}
