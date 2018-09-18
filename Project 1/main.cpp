#include <iostream>
#include <stdexcept>
#include <string>
#include "student.h"



// //****************************************************************
// //                   MAIN FUNCTION IN PROJECT
// //****************************************************************

int main()
{
  std::string command;
  Manager myman;
  std::string isgrad;
  std::string name;
  std::string stunum;
  std::string labname;
  std::string freshmenclass;
  int index;
  bool isLast=true;

  while(isLast){
	std::cout << "\n\n\n*---------------------Welcome to Student Management System---------------------*" << std::endl;

	std::cout << "What do you want to do?\n1. Add student:a\n2. Compare student:c \n3. Find student:f\n4. Delete student:d\n5. Print all student:p\n6. Quit:q" << std::endl;

	// ******Modify here****** 
	//You need to handle wrong argument format
	std::cin >> command;
	if(command != "a" && command != "c" && command != "f" && command != "d" && command != "p" && command != "q"){
		std::cout << "Invalid Argument" << std::endl;
		continue;
	}

	switch(command[0])
	  {
	  case 'a':{
		// Type of student you want to add (Graduate student or Undergraduate student)
		std::cout << "Add student executed\n\nType\nUndergraduate:0 Graduate:1"<< std::endl;
		
		// ******Modify here****** 
		//You need to handle wrong argument format
		std::cin >> isgrad;
		if (isgrad == "1"){
			std::cout << "\nFormat: [name stunum labname]" << std::endl;
		  
		  	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> labname;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos)
			 	myman.add_student(name, std::stoi(stunum), labname);	
			else
				std::cout<<"Invalid Argument"<<std::endl;

		}

		else if (isgrad == "0"){
		  	std::cout << "\nFormat: [name stunum freshmenclass] " << std::endl;
		  
		  	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> freshmenclass;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos && freshmenclass.find_first_not_of("0123456789") == std::string::npos)
				myman.add_student(name, std::stoi(stunum), std::stoi(freshmenclass));		
			else
				std::cout<<"Invalid Argument"<<std::endl;  
		}
		
	  }break;

	  case 'c':{
		std::cout << "Compare student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
		
		// ******Modify here****** 
		//You need to handle wrong argument format
		std::cin >> isgrad;
		if (isgrad == "1"){
			std::cout << "\nTarget student\nFormat: [index name stunum labname]" << std::endl;
		  
			// ******Modify here****** 
			//You need to handle wrong argument format
		 	std::cin >> index >> name >> stunum >> labname;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos)
		  		myman.compare_student(index, name, std::stoi(stunum), labname);
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}

		else if (isgrad == "0"){
			std::cout << "\nTarget student\nFormat: [index name stunum freshmenclass] " << std::endl;
		  	std::cin >> index >> name >> stunum >> freshmenclass;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos && freshmenclass.find_first_not_of("0123456789") == std::string::npos)
		  		myman.compare_student(index, name, std::stoi(stunum), std::stoi(freshmenclass));
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}
	  }break;

	  case 'f':{
		std::cout << "Find student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;
		
		// ******Modify here****** 
		//You need to handle wrong argument format
		std::cin >> isgrad;

		if (isgrad == "1"){
		  	std::cout << "\nFormat: [name stunum labname]" << std::endl;

		 	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> labname;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos)
		  		myman.find_student(name, std::stoi(stunum), labname);
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}
		else if (isgrad == "0"){
		  	std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;

		 	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> freshmenclass;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos && freshmenclass.find_first_not_of("0123456789") == std::string::npos)
		  		myman.find_student(name, std::stoi(stunum), std::stoi(freshmenclass));
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}
	  }break;


	  case 'd':{
		std::cout << "Delete student executed\n\nType\nUndergraduate:0 Graduate:1" << std::endl;

		// ******Modify here****** 
		//You need to handle wrong argument format
		std::cin >> isgrad;

		if (isgrad == "1"){
		 	std::cout << "\nFormat: [name stunum labname]" << std::endl;
		  
		  	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> labname;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos)
		  		myman.delete_student(name, std::stoi(stunum), labname);
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}
		else if (isgrad == "0"){
		  	std::cout << "\nFormat: [name stunum freshmenclass]" << std::endl;
		  
		  	// ******Modify here****** 
		  	//You need to handle wrong argument format
		  	std::cin >> name >> stunum >> freshmenclass;
		  	if(stunum.find_first_not_of( "0123456789" ) == std::string::npos && freshmenclass.find_first_not_of("0123456789") == std::string::npos)
		  		myman.delete_student(name, std::stoi(stunum), std::stoi(freshmenclass));
		  	else
				std::cout<<"Invalid Argument"<<std::endl;
		}
	  }break;

	  case 'p':{
		std::cout << "Print all executed" << std::endl;
		myman.print_all();
	  }break;

	  case 'q':{
	  std::cout << "Quit" << std::endl;
	  isLast = false;
	  }break;

	  default:{
		std::cout << "Invalid argument" << std::endl;
	  }break;
	  }
  }
  return 0;
}

