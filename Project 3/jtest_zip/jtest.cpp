/*
	jtest.cpp
	- test program for EE205 Data Structures and Algorithms for Electrical Engineering

	Author @ Juan Lee (juanlee@kaist.ac.kr), School of Computing, KAIST
*/

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <streambuf>
#include <string>
#include <regex>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//   YOU SHOULD CHANGE BELOW                                                  //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "linked_list.h"
// your linked_list header
// #include "YOUR_LINKED_LIST.h"

typedef LinkedList LinkedList;
// your linked_list class
// DO NOT modify second 'LinkedList'
// typedef YOUR_LINKED_LIST_CLASS LinkedList

////////////////////////////////////////////////////////////////////////////////

// avl tree
#include "avl_tree.h"
#include "rb_tree.h"

typedef AVLTree<LinkedList> S_AVLTree;
typedef RBTree<LinkedList> S_RBTree;

class JTest{
private:
	string test_str;
	int nProblems;
	int nPassed;

private:
	void red_print(const char* msg){
		printf("%s%s%s", "\x1b[31m", msg, "\x1b[0m");
	}

	void green_print(const char* msg){
		printf("%s%s%s", "\x1b[32m", msg, "\x1b[0m");
	}

	void yellow_print(const char* msg){
		printf("%s%s%s", "\x1b[33m", msg, "\x1b[0m");
	}

public:
	JTest(string test_str){
		this->test_str = test_str;
		nProblems = 0;
		nPassed = 0;
	}

	void start(){
		cout<<"========== TEST FOR "<<test_str<<" =========="<<endl;
	}

	void end(){
		cout<<"You have passed "<<nPassed<<" of "<<nProblems<<endl;
		cout<<"========== FINISHED FOR "<<test_str<<" =========="<<endl<<endl;
	}

	void problem(string problem_str){
		char buf[1024] = {0};
		++nProblems;
		if(nProblems < 10)
			sprintf(buf, "[%s - 0%d] %s", test_str.c_str(), nProblems, problem_str.c_str());
		else
			sprintf(buf, "[%s - %d] %s", test_str.c_str(), nProblems, problem_str.c_str());

		yellow_print(buf);
		for(int i=strlen(buf); i<65; i++) yellow_print(" ");

		fflush(stdout);
	}

	void print_difference(string expected, string get){
		if(expected != get){
			printf("////////////////////////////////////////\n");
			green_print("EXPECTED:\n");
			cout<<expected<<endl;
			red_print("GET:\n");
			cout<<get<<endl;
			printf("////////////////////////////////////////\n");
		}
	}

	void simple_check(string expected, string get, bool doDiff = false, bool visual = true){
		if(expected == get){
			pass();
		}
		else{
			fail();
			if(visual){
				if(!doDiff)
					print_difference(expected, get);
				else{
					ofstream fexpected, fget;

					fexpected.open("expected.jtest");
					fexpected << expected;
					fexpected.close();

					fget.open("get.jtest");
					fget << get;
					fget.close();

					system("diff expected.jtest get.jtest");
				}
			}
		}
	}

	void print_difference(bool expected, bool get){
		if(expected != get){
			printf("////////////////////////////////////////\n");
			green_print("EXPECTED:\n");
			if(expected) printf("True\n");
			else printf("False\n");
			red_print("GET:\n");
			if(get) printf("True\n");
			else printf("False\n");
			printf("////////////////////////////////////////\n");
		}
	}

	void simple_check(bool expected, bool get){
		if(expected == get){
			pass();
		}
		else{
			fail();
			print_difference(expected, get);
		}
	}

	void pass(){
		green_print("PASS\n");
		nPassed++;
	}

	void fail(){
		red_print("FAIL\n");
	}
};

void TEST_AVL();
void TEST_YAVL();
void TEST_RB();
void TEST_YRB();

/*
	main: void -> int
	- main function of this program
*/
int main(int argc, char* argv[]){
	if(argc != 2){
		printf("Usage: %s -all   test all the test cases below\n" \
			   "       %s -avl   test avl tree implementation\n"  \
			   "       %s -yavl  test avl-based yimacs\n" \
			   "       %s -rb    test rb tree implementation\n" \
			   "       %s -yrb   test rb-based yimacs\n",
			   argv[0], argv[0], argv[0], argv[0], argv[0]);
		return 1;
	}

	printf("%s%s%s", "\x1b[32m", "JTEST Running...\n", "\x1b[0m");
	printf("%s%s%s", "\x1b[32m", "Author @ Juan Lee (juanlee@kaist.ac.kr), School of Computing, KAIST\n\n", "\x1b[0m");

	string arg(argv[1]);
	if(arg == "-all" || arg == "-avl"){
		TEST_AVL();
	}
	if(arg == "-all" || arg == "-yavl"){
		TEST_YAVL();
	}
	if(arg == "-all" || arg == "-rb"){
		TEST_RB();
	}
	if(arg == "-all" || arg == "-yrb"){
		TEST_YRB();
	}

	return 0;
}

string TEST_get_display(S_AVLTree& tree){
	stringstream buffer;
	streambuf *old;

	old = cout.rdbuf(buffer.rdbuf());

	tree.display();
	string result = buffer.str();

	cout.rdbuf(old);

	return result;
}

string TEST_get_display(S_RBTree& tree){
	stringstream buffer;
	streambuf *old;

	old = cout.rdbuf(buffer.rdbuf());

	tree.display();
	string result = buffer.str();

	cout.rdbuf(old);

	return result;
}

void TEST_AVL(){
	JTest test("AVL Tree");
	test.start();

	////////////////////////////////////////////////////////////////////////////
	S_AVLTree tree;
	string result_str;
	bool result_bool;
	int result_int;
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display when empty");
	result_str = TEST_get_display(tree);
	test.simple_check("Tree is empty.\n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert single element: s");
	tree.insert("s");
	result_bool = tree.is_root(tree.search("s"));
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: s\ns \ns \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: s\ns \ns \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove single element: s");
	result_bool = tree.remove("s");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "Tree is empty.\n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("Tree is empty.\n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a");
	tree.insert("a");
	result_str = TEST_get_display(tree);
	test.simple_check("root: a\na \na \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b");
	tree.insert("b");
	result_str = TEST_get_display(tree);
	test.simple_check("root: a\na b \na b \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c");
	tree.insert("c");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c \nb a c \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d");
	tree.insert("d");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d \nb a c d \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e");
	tree.insert("e");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d e \nb a d c e \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e f");
	tree.insert("f");
	result_str = TEST_get_display(tree);
	test.simple_check("root: d\na b c d e f \nd b a c e f \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e f g");
	tree.insert("g");
	result_str = TEST_get_display(tree);
	test.simple_check("root: d\na b c d e f g \nd b a c f e g \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: d");
	result_bool = tree.is_root(tree.search("d"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove non-element node");
	result_bool = tree.remove("k");
	test.simple_check(false, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove external node: g");
	result_bool = tree.remove("g");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: d\na b c d e f \nd b a c f e \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: d\na b c d e f \nd b a c f e \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: d");
	result_bool = tree.is_root(tree.search("d"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove root node: d");
	result_bool = tree.remove("d");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: e\na b c e f \ne b a c f \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: e\na b c e f \ne b a c f \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: e");
	result_bool = tree.is_root(tree.search("e"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove internal node: b");
	result_bool = tree.remove("b");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: e\na c e f \ne c a f \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: e\na c e f \ne c a f \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove external node: a");
	result_bool = tree.remove("a");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: e\nc e f \ne c f \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: e\nc e f \ne c f \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance - inorder x, y, z");
	tree.insert("b");
	tree.insert("a");
	result_str = TEST_get_display(tree);
	test.simple_check("root: e\na b c e f \ne b a c f \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance - inorder z, y, x");
	tree.insert("g");
	tree.insert("k");
	result_str = TEST_get_display(tree);
	test.simple_check("root: e\na b c e f g k \ne b a c g f k \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance - inorder z, x, y");
	tree.insert("n");
	tree.insert("m");
	result_str = TEST_get_display(tree);
	test.simple_check("root: e\na b c e f g k m n \ne b a c g f m k n \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance - inorder y, x, z");
	tree.remove("a");
	tree.remove("b");
	tree.remove("c");
	tree.remove("e");
	tree.remove("f");
	tree.remove("g");
	tree.remove("k");
	tree.remove("m");
	tree.remove("n");
	tree.insert("c");
	tree.insert("a");
	tree.insert("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("b");
	tree.remove("c"); // clean up
	test.simple_check("root: b\na b c \nb a c \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove root when no right child");
	tree.insert("b");
	tree.insert("a");
	tree.remove("b");
	result_bool = tree.is_root(tree.search("a"));
	result_str = TEST_get_display(tree);
	tree.remove("a"); // clean up
	if(result_bool && result_str == "root: a\na \na \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: a\na \na \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove internal node when no right child");
	tree.insert("c");
	tree.insert("b");
	tree.insert("d");
	tree.insert("a");
	tree.remove("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("c");
	tree.remove("d");
	test.simple_check("root: c\na c d \nc a d \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance after removing 1");
	tree.insert("c");
	tree.insert("a");
	tree.insert("g");
	tree.insert("b");
	tree.insert("e");
	tree.insert("h");
	tree.insert("d");
	tree.insert("f");
	tree.insert("i");

	tree.remove("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("c");
	tree.remove("d");
	tree.remove("e");
	tree.remove("f");
	tree.remove("g");
	tree.remove("h");
	tree.remove("i");
	test.simple_check("root: g\na c d e f g h i \ng c a e d f h i \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance after removing 2");
	tree.insert("4");
	tree.insert("2");
	tree.insert("7");
	tree.insert("1");
	tree.insert("3");
	tree.insert("5");
	tree.insert("8");
	tree.insert("6");

	tree.remove("4");
	result_str = TEST_get_display(tree);
	test.simple_check("root: 5\n1 2 3 5 6 7 8 \n5 2 1 3 7 6 8 \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	test.end();
}

string TEST_get(string filename){
	ifstream t(filename);
	string result((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());
	return result;
}

string TEST_run(string command, string ycommand){
	string execute_command = "echo \"" + ycommand + "\" > .command";
	system(execute_command.c_str());

	execute_command = command + " < .command > .result";
	system(execute_command.c_str());

	string result = TEST_get(".result");

	system("rm .command .result");

	return result;
}

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

void TEST_YAVL(){
	JTest test("AVL-based Yimacs");
	test.start();

	////////////////////////////////////////////////////////////////////////////
	string single_example = "echo \"aaa bbb ccc\" > single.jtest";
	string short_example = "echo \"aaa bbb ccc\naaa ddd eee\nfff ddd eee\" > short.jtest";
	string long_example = "cp jtest.cpp jtest.jtest";
	string case_insensitive_example = "echo \"PaSs JTeSt\" > case.jtest";

	string result_str, result_output;

	system(single_example.c_str());
	system(short_example.c_str());
	system(case_insensitive_example.c_str());
	system(long_example.c_str());
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	string whitespaces[] = {" ", "\t", "\f", "\v", "\r"};

	test.problem("all whitespaces? ' ', \\t, \\r, \\f, \\v");
	bool isPass = true;
	string check_printed;
	string check_output;
	for(string white: whitespaces){
		for(string other: whitespaces){
			string whitespace_tester = "abc" + white + "def" + other + "ghi";
			string system_command = "echo \"" + whitespace_tester + "\" > whitespace.jtest";
			system(system_command.c_str());

			result_str = TEST_run("./yimacs_avl whitespace.jtest whitespace.joutput", "R abc xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> xyz" + white + "def" + other + "ghi\n\n";
			check_output = "xyz" + white + "def" + other + "ghi\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}

			result_str = TEST_run("./yimacs_avl whitespace.jtest whitespace.joutput", "R def xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> abc" + white + "xyz" + other + "ghi\n\n";
			check_output = "abc" + white + "xyz" + other + "ghi\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}

			result_str = TEST_run("./yimacs_avl whitespace.jtest whitespace.joutput", "R ghi xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> abc" + white + "def" + other + "xyz\n\n";
			check_output = "abc" + white + "def" + other + "xyz\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}
		}

		if(!isPass) break;
	}

	if(isPass){
		test.pass();
	}
	else{
		test.fail();
		test.print_difference(check_printed, result_str);
		test.print_difference(check_output, result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace first for single line file");
	result_str = TEST_run("./yimacs_avl single.jtest single.joutput", "R aaa juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n" && result_output == "juan bbb ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n", result_str);
		test.print_difference("juan bbb ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace first for single line file");
	result_str = TEST_run("./yimacs_avl single.jtest single.joutput", "R aaa juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n" && result_output == "juan bbb ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n", result_str);
		test.print_difference("juan bbb ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace internal for single line file");
	result_str = TEST_run("./yimacs_avl single.jtest single.joutput", "R bbb juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> aaa juan ccc\n\n" && result_output == "aaa juan ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> aaa juan ccc\n\n", result_str);
		test.print_difference("aaa juan ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace last for single line file");
	result_str = TEST_run("./yimacs_avl single.jtest single.joutput", "R ccc juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> aaa bbb juan\n\n" && result_output == "aaa bbb juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> aaa bbb juan\n\n", result_str);
		test.print_difference("aaa bbb juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for single line file");
	result_str = TEST_run("./yimacs_avl single.jtest single.joutput", "R aaa bbb\nR bbb juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> bbb bbb ccc\n\n< bbb bbb ccc\n> juan juan ccc\n\n" && result_output == "juan juan ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> bbb bbb ccc\n\n< bbb bbb ccc\n> juan juan ccc\n\n", result_str);
		test.print_difference("juan juan ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many firsts for short file");
	result_str = TEST_run("./yimacs_avl short.jtest short.joutput", "R aaa juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n< aaa ddd eee\n> juan ddd eee\n\n" && result_output == "juan bbb ccc\njuan ddd eee\nfff ddd eee\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n< aaa ddd eee\n> juan ddd eee\n\n", result_str);
		test.print_difference("juan bbb ccc\njuan ddd eee\nfff ddd eee\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many internals for short file");
	result_str = TEST_run("./yimacs_avl short.jtest short.joutput", "R ddd juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa ddd eee\n> aaa juan eee\n\n< fff ddd eee\n> fff juan eee\n\n" && result_output == "aaa bbb ccc\naaa juan eee\nfff juan eee\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa ddd eee\n> aaa juan eee\n\n< fff ddd eee\n> fff juan eee\n\n", result_str);
		test.print_difference("aaa bbb ccc\naaa juan eee\nfff juan eee\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many lasts for short file");
	result_str = TEST_run("./yimacs_avl short.jtest short.joutput", "R eee juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa ddd eee\n> aaa ddd juan\n\n< fff ddd eee\n> fff ddd juan\n\n" && result_output == "aaa bbb ccc\naaa ddd juan\nfff ddd juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa ddd eee\n> aaa ddd juan\n\n< fff ddd eee\n> fff ddd juan\n\n", result_str);
		test.print_difference("aaa bbb ccc\naaa ddd juan\nfff ddd juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for short file");
	result_str = TEST_run("./yimacs_avl short.jtest short.joutput", "R aaa ddd\nR ddd eee\nR eee juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == 
		"< aaa bbb ccc\n"\
		"> ddd bbb ccc\n\n"\
		"< aaa ddd eee\n"\
		"> ddd ddd eee\n\n"\
		"< ddd bbb ccc\n"\
		"> eee bbb ccc\n\n"\
		"< ddd ddd eee\n"\
		"> eee eee eee\n\n"\
		"< fff ddd eee\n"\
		"> fff eee eee\n\n"\
		"< eee bbb ccc\n"\
		"> juan bbb ccc\n\n"\
		"< eee eee eee\n"\
		"> juan juan juan\n\n"\
		"< fff eee eee\n"\
		"> fff juan juan\n\n" 
	&& result_output == "juan bbb ccc\njuan juan juan\nfff juan juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference(\
			"< aaa bbb ccc\n"\
			"> ddd bbb ccc\n\n"\
			"< aaa ddd eee\n"\
			"> ddd ddd eee\n\n"\
			"< ddd bbb ccc\n"\
			"> eee bbb ccc\n\n"\
			"< ddd ddd eee\n"\
			"> eee eee eee\n\n"\
			"< fff ddd eee\n"\
			"> fff eee eee\n\n"\
			"< eee bbb ccc\n"\
			"> juan bbb ccc\n\n"\
			"< eee eee eee\n"\
			"> juan juan juan\n\n"\
			"< fff eee eee\n"\
			"> fff juan juan\n\n" 
		,result_str);
		test.print_difference("juan bbb ccc\njuan juan juan\nfff juan juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("case insensitive test!");
	result_str = TEST_run("./yimacs_avl case.jtest case.joutput", "R pass pass\nQ");
	result_output = TEST_get("case.joutput");
	if(result_str == "< PaSs JTeSt\n> pass JTeSt\n\n" && result_output == "pass JTeSt\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< PaSs JTeSt\n> pass JTeSt\n\n", result_str);
		test.print_difference("pass JTeSt\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 1");
	TEST_run("./yimacs_avl jtest.jtest jtest.joutput", "R void juan\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "void", "juan");
	test.simple_check(result_str, result_output, true);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 2");
	TEST_run("./yimacs_avl jtest.jtest jtest.joutput", "R string something_very_long\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "string", "something_very_long");
	test.simple_check(result_str, result_output, true);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 3");
	TEST_run("./yimacs_avl jtest.jtest jtest.joutput", "R == equal\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "==", "equal");
	test.simple_check(result_str, result_output, true);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for large file 1");
	TEST_run("./yimacs_avl jtest.jtest jtest.joutput", "R void ==\nR == equal\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "void", "==");
	replace_all(result_str, "==", "equal");
	test.simple_check(result_str, result_output, true);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for large file 2");
	TEST_run("./yimacs_avl jtest.jtest jtest.joutput", "R aaa bbb\nR bbb ccc\nR ccc ==\nR == yeah!\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "aaa", "bbb");
	replace_all(result_str, "bbb", "ccc");
	replace_all(result_str, "ccc", "==");
	replace_all(result_str, "==", "yeah!");
	test.simple_check(result_str, result_output, true);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	string remove_examples = "rm *.jtest *.joutput";
	system(remove_examples.c_str());
	////////////////////////////////////////////////////////////////////////////
	test.end();
}

void TEST_RB(){
	JTest test("RB Tree");
	test.start();

	////////////////////////////////////////////////////////////////////////////
	S_RBTree tree;
	string result_str;
	bool result_bool;
	int result_int;
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display when empty");
	result_str = TEST_get_display(tree);
	test.simple_check("Tree is empty.\n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert single element: s");
	tree.insert("s");
	result_bool = tree.is_root(tree.search("s"));
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: s\ns \ns \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: s\ns \ns \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove single element: s");
	result_bool = tree.remove("s");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "Tree is empty.\n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("Tree is empty.\n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a");
	tree.insert("a");
	result_str = TEST_get_display(tree);
	test.simple_check("root: a\na \na \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b");
	tree.insert("b");
	result_str = TEST_get_display(tree);
	test.simple_check("root: a\na b \na b \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c");
	tree.insert("c");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c \nb a c \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d");
	tree.insert("d");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d \nb a c d \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e");
	tree.insert("e");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d e \nb a d c e \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e f");
	tree.insert("f");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d e f \nb a d c e f \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("display after insertion: a b c d e f g");
	tree.insert("g");
	result_str = TEST_get_display(tree);
	test.simple_check("root: b\na b c d e f g \nb a d c f e g \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: b");
	result_bool = tree.is_root(tree.search("b"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove non-element node");
	result_bool = tree.remove("k");
	test.simple_check(false, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove external node: g");
	result_bool = tree.remove("g");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: b\na b c d e f \nb a d c f e \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: b\na b c d e f \nb a d c f e \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: b");
	result_bool = tree.is_root(tree.search("b"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove root node: b");
	result_bool = tree.remove("b");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: c\na c d e f \nc a e d f \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: c\na c d e f \nc a e d f \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("check current root: c");
	result_bool = tree.is_root(tree.search("c"));
	test.simple_check(true, result_bool);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove internal node: e");
	result_bool = tree.remove("e");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: c\na c d f \nc a f d \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: c\na c d f \nc a f d \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove external node: d");
	result_bool = tree.remove("d");
	result_str = TEST_get_display(tree);
	if(result_bool && result_str == "root: c\na c f \nc a f \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: c\na c f \nc a f \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance - inorder y, x, z");
	tree.remove("a");
	tree.remove("b");
	tree.remove("c");
	tree.remove("e");
	tree.remove("f");
	tree.remove("g");
	tree.remove("k");
	tree.remove("m");
	tree.remove("n");
	tree.insert("c");
	tree.insert("a");
	tree.insert("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("b");
	tree.remove("c"); // clean up
	test.simple_check("root: b\na b c \nb a c \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove root when no right child");
	tree.insert("b");
	tree.insert("a");
	tree.remove("b");
	result_bool = tree.is_root(tree.search("a"));
	result_str = TEST_get_display(tree);
	tree.remove("a"); // clean up
	if(result_bool && result_str == "root: a\na \na \n")
		test.pass();
	else{
		test.fail();
		test.print_difference(true, result_bool);
		test.print_difference("root: a\na \na \n", result_str);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("remove internal node when no right child");
	tree.insert("c");
	tree.insert("b");
	tree.insert("d");
	tree.insert("a");
	tree.remove("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("c");
	tree.remove("d");
	test.simple_check("root: c\na c d \nc a d \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance after removing 1");
	tree.insert("c");
	tree.insert("a");
	tree.insert("g");
	tree.insert("b");
	tree.insert("e");
	tree.insert("h");
	tree.insert("d");
	tree.insert("f");
	tree.insert("i");

	tree.remove("b");
	result_str = TEST_get_display(tree);
	tree.remove("a");
	tree.remove("c");
	tree.remove("d");
	tree.remove("e");
	tree.remove("f");
	tree.remove("g");
	tree.remove("h");
	tree.remove("i");
	test.simple_check("root: c\na c d e f g h i \nc a g e d f h i \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("balance after removing 2");
	tree.insert("4");
	tree.insert("2");
	tree.insert("7");
	tree.insert("1");
	tree.insert("3");
	tree.insert("5");
	tree.insert("8");
	tree.insert("6");

	tree.remove("4");
	result_str = TEST_get_display(tree);
	tree.remove("1");
	tree.remove("2");
	tree.remove("3");
	tree.remove("5");
	tree.remove("6");
	tree.remove("7");
	tree.remove("8");
	test.simple_check("root: 5\n1 2 3 5 6 7 8 \n5 2 1 3 7 6 8 \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert l example (PPT 15) RST");
	tree.insert("d");
	tree.insert("g");
	tree.insert("l");

	result_str = TEST_get_display(tree);
	test.simple_check("root: g\nd g l \ng d l \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert o example (PPT 15) RCL");
	tree.insert("o");

	result_str = TEST_get_display(tree);
	test.simple_check("root: g\nd g l o \ng d l o \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert n example (PPT 15) RST");
	tree.insert("c");
	tree.insert("e");
	tree.insert("n");

	result_str = TEST_get_display(tree);
	test.simple_check("root: g\nc d e g l n o \ng d c e n l o \n", result_str);
	////////////////////////////////////////////////////////////////////////////		

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert r example (PPT 15) RCL");
	tree.insert("r");

	result_str = TEST_get_display(tree);
	test.simple_check("root: g\nc d e g l n o r \ng d c e n l o r \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert p example (PPT 15) RST");
	tree.insert("p");

	result_str = TEST_get_display(tree);
	test.simple_check("root: g\nc d e g l n o p r \ng d c e n l p o r \n", result_str);
	////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////
	test.problem("insert q example (PPT 15) RCL");
	tree.insert("q");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nc d e g l n o p q r \nn g d c e l p o r q \n", result_str);
	////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove c example (PPT 33)");
	tree.remove("c");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nd e g l n o p q r \nn g d e l p o r q \n", result_str);
	////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove l example (PPT 34)");
	tree.remove("l");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nd e g n o p q r \nn e d g p o r q \n", result_str);
	////////////////////////////////////////////////////////////////////////////	

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove q example (PPT 35)");
	tree.remove("q");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nd e g n o p r \nn e d g p o r \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove r example (PPT 36)");
	tree.remove("r");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nd e g n o p \nn e d g p o \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove o example (PPT 37)");
	tree.remove("o");

	result_str = TEST_get_display(tree);
	test.simple_check("root: n\nd e g n p \nn e d g p \n", result_str);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////	
	test.problem("remove p example (PPT 38)");
	tree.remove("p");

	result_str = TEST_get_display(tree);
	test.simple_check("root: e\nd e g n \ne d n g \n", result_str);
	////////////////////////////////////////////////////////////////////////////			

	test.end();
}

void TEST_YRB(){
	JTest test("RB-based Yimacs");
	test.start();

	////////////////////////////////////////////////////////////////////////////
	string single_example = "echo \"aaa bbb ccc\" > single.jtest";
	string short_example = "echo \"aaa bbb ccc\naaa ddd eee\nfff ddd eee\" > short.jtest";
	string long_example = "cp jtest.cpp jtest.jtest";
	string case_insensitive_example = "echo \"PaSs JTeSt\" > case.jtest";

	string result_str, result_output;

	system(single_example.c_str());
	system(short_example.c_str());
	system(case_insensitive_example.c_str());
	system(long_example.c_str());
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	string whitespaces[] = {" ", "\t", "\f", "\v", "\r"};

	test.problem("all whitespaces? ' ', \\t, \\r, \\f, \\v");
	bool isPass = true;
	string check_printed;
	string check_output;
	for(string white: whitespaces){
		for(string other: whitespaces){
			string whitespace_tester = "abc" + white + "def" + other + "ghi";
			string system_command = "echo \"" + whitespace_tester + "\" > whitespace.jtest";
			system(system_command.c_str());

			result_str = TEST_run("./yimacs_rb whitespace.jtest whitespace.joutput", "R abc xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> xyz" + white + "def" + other + "ghi\n\n";
			check_output = "xyz" + white + "def" + other + "ghi\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}

			result_str = TEST_run("./yimacs_rb whitespace.jtest whitespace.joutput", "R def xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> abc" + white + "xyz" + other + "ghi\n\n";
			check_output = "abc" + white + "xyz" + other + "ghi\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}

			result_str = TEST_run("./yimacs_rb whitespace.jtest whitespace.joutput", "R ghi xyz\nQ");
			result_output = TEST_get("whitespace.joutput");

			check_printed = "< "+whitespace_tester+"\n> abc" + white + "def" + other + "xyz\n\n";
			check_output = "abc" + white + "def" + other + "xyz\n";

			if(result_str != check_printed || result_output != check_output){
				isPass = false;
				break;
			}
		}

		if(!isPass) break;
	}

	if(isPass){
		test.pass();
	}
	else{
		test.fail();
		test.print_difference(check_printed, result_str);
		test.print_difference(check_output, result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace first for single line file");
	result_str = TEST_run("./yimacs_rb single.jtest single.joutput", "R aaa juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n" && result_output == "juan bbb ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n", result_str);
		test.print_difference("juan bbb ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace first for single line file");
	result_str = TEST_run("./yimacs_rb single.jtest single.joutput", "R aaa juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n" && result_output == "juan bbb ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n", result_str);
		test.print_difference("juan bbb ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace internal for single line file");
	result_str = TEST_run("./yimacs_rb single.jtest single.joutput", "R bbb juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> aaa juan ccc\n\n" && result_output == "aaa juan ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> aaa juan ccc\n\n", result_str);
		test.print_difference("aaa juan ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace last for single line file");
	result_str = TEST_run("./yimacs_rb single.jtest single.joutput", "R ccc juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> aaa bbb juan\n\n" && result_output == "aaa bbb juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> aaa bbb juan\n\n", result_str);
		test.print_difference("aaa bbb juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for single line file");
	result_str = TEST_run("./yimacs_rb single.jtest single.joutput", "R aaa bbb\nR bbb juan\nQ");
	result_output = TEST_get("single.joutput");
	if(result_str == "< aaa bbb ccc\n> bbb bbb ccc\n\n< bbb bbb ccc\n> juan juan ccc\n\n" && result_output == "juan juan ccc\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> bbb bbb ccc\n\n< bbb bbb ccc\n> juan juan ccc\n\n", result_str);
		test.print_difference("juan juan ccc\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many firsts for short file");
	result_str = TEST_run("./yimacs_rb short.jtest short.joutput", "R aaa juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa bbb ccc\n> juan bbb ccc\n\n< aaa ddd eee\n> juan ddd eee\n\n" && result_output == "juan bbb ccc\njuan ddd eee\nfff ddd eee\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa bbb ccc\n> juan bbb ccc\n\n< aaa ddd eee\n> juan ddd eee\n\n", result_str);
		test.print_difference("juan bbb ccc\njuan ddd eee\nfff ddd eee\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many internals for short file");
	result_str = TEST_run("./yimacs_rb short.jtest short.joutput", "R ddd juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa ddd eee\n> aaa juan eee\n\n< fff ddd eee\n> fff juan eee\n\n" && result_output == "aaa bbb ccc\naaa juan eee\nfff juan eee\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa ddd eee\n> aaa juan eee\n\n< fff ddd eee\n> fff juan eee\n\n", result_str);
		test.print_difference("aaa bbb ccc\naaa juan eee\nfff juan eee\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace many lasts for short file");
	result_str = TEST_run("./yimacs_rb short.jtest short.joutput", "R eee juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == "< aaa ddd eee\n> aaa ddd juan\n\n< fff ddd eee\n> fff ddd juan\n\n" && result_output == "aaa bbb ccc\naaa ddd juan\nfff ddd juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< aaa ddd eee\n> aaa ddd juan\n\n< fff ddd eee\n> fff ddd juan\n\n", result_str);
		test.print_difference("aaa bbb ccc\naaa ddd juan\nfff ddd juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for short file");
	result_str = TEST_run("./yimacs_rb short.jtest short.joutput", "R aaa ddd\nR ddd eee\nR eee juan\nQ");
	result_output = TEST_get("short.joutput");
	if(result_str == 
		"< aaa bbb ccc\n"\
		"> ddd bbb ccc\n\n"\
		"< aaa ddd eee\n"\
		"> ddd ddd eee\n\n"\
		"< ddd bbb ccc\n"\
		"> eee bbb ccc\n\n"\
		"< ddd ddd eee\n"\
		"> eee eee eee\n\n"\
		"< fff ddd eee\n"\
		"> fff eee eee\n\n"\
		"< eee bbb ccc\n"\
		"> juan bbb ccc\n\n"\
		"< eee eee eee\n"\
		"> juan juan juan\n\n"\
		"< fff eee eee\n"\
		"> fff juan juan\n\n" 
	&& result_output == "juan bbb ccc\njuan juan juan\nfff juan juan\n")
		test.pass();
	else{
		test.fail();
		test.print_difference(\
			"< aaa bbb ccc\n"\
			"> ddd bbb ccc\n\n"\
			"< aaa ddd eee\n"\
			"> ddd ddd eee\n\n"\
			"< ddd bbb ccc\n"\
			"> eee bbb ccc\n\n"\
			"< ddd ddd eee\n"\
			"> eee eee eee\n\n"\
			"< fff ddd eee\n"\
			"> fff eee eee\n\n"\
			"< eee bbb ccc\n"\
			"> juan bbb ccc\n\n"\
			"< eee eee eee\n"\
			"> juan juan juan\n\n"\
			"< fff eee eee\n"\
			"> fff juan juan\n\n" 
		,result_str);
		test.print_difference("juan bbb ccc\njuan juan juan\nfff juan juan\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("case insensitive test!");
	result_str = TEST_run("./yimacs_rb case.jtest case.joutput", "R pass pass\nQ");
	result_output = TEST_get("case.joutput");
	if(result_str == "< PaSs JTeSt\n> pass JTeSt\n\n" && result_output == "pass JTeSt\n")
		test.pass();
	else{
		test.fail();
		test.print_difference("< PaSs JTeSt\n> pass JTeSt\n\n", result_str);
		test.print_difference("pass JTeSt\n", result_output);
	}
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 1");
	TEST_run("./yimacs_rb jtest.jtest jtest.joutput", "R void juan\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "void", "juan");
	test.simple_check(result_str, result_output, true, false);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 2");
	TEST_run("./yimacs_rb jtest.jtest jtest.joutput", "R string something_very_long\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "string", "something_very_long");
	test.simple_check(result_str, result_output, true, false);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("replace large file 3");
	TEST_run("./yimacs_rb jtest.jtest jtest.joutput", "R == equal\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "==", "equal");
	test.simple_check(result_str, result_output, true, false);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for large file 1");
	TEST_run("./yimacs_rb jtest.jtest jtest.joutput", "R void ==\nR == equal\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "void", "==");
	replace_all(result_str, "==", "equal");
	test.simple_check(result_str, result_output, true, false);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	test.problem("multiple commands for large file 2");
	TEST_run("./yimacs_rb jtest.jtest jtest.joutput", "R aaa bbb\nR bbb ccc\nR ccc ==\nR == yeah!\nQ");
	result_str = TEST_get("jtest.jtest");
	result_output = TEST_get("jtest.joutput");
	replace_all(result_str, "aaa", "bbb");
	replace_all(result_str, "bbb", "ccc");
	replace_all(result_str, "ccc", "==");
	replace_all(result_str, "==", "yeah!");
	test.simple_check(result_str, result_output, true, false);
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	string remove_examples = "rm *.jtest *.joutput";
	system(remove_examples.c_str());
	////////////////////////////////////////////////////////////////////////////
	test.end();
}


