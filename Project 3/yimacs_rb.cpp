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

using namespace std;

/* Use these functions to replace words in a string.
* Make sure you add -std=c++11 option when you compile.
*/
void replace_all(string& str, const string& from, const string& to) {

    std::regex reg1("^" + from + " ");
    str = string(std::regex_replace(str, reg1, to + " "));

    std::regex reg2(" " + from + "$");
    str = string(std::regex_replace(str, reg2, " " + to));

    std::regex reg3(" " + from + " ");
    str = string(std::regex_replace(str, reg3, " " + to + " "));
    str = string(std::regex_replace(str, reg3, " " + to + " "));

    std::regex reg4("^" + from + "$");
    str = string(std::regex_replace(str, reg4, to));
}


int main(int argc, char* argv[])
{

}
