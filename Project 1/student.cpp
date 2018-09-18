#include <iostream>
#include "student.h"

// //****************************************************************
// //                   REQUIRED FUNCTIONALITY IN PROJECT
// //****************************************************************

// 1. You need to implement every detail of the function defined below
// 2. You additionally need to implement getInfo methods in each classes.
// 3. You additionally need to implement 'operator overloading' with '==' which compares two students whether all the members are the same

Manager::Manager()
: top(-1){
	for(int i=0; i<300; i++)
		students[i] = NULL;
}

Manager::~Manager(){
	for(int i=0; i<300; i++){
		if(students[i] != NULL){
			delete students[i];
		}
	}
}

int Manager::add_student(std::string name, int stunum, std::string labname)
{
	// Adds Grad_Student object with given argument
	// Returns the total number of objects in the student array after adding
	students[++top] = new Grad_Student(name, stunum, labname);
	std::cout << "add graduate student DONE" << std::endl;
	return top+1;
};

int Manager::add_student(std::string name, int stunum, int freshmenclass)
{
	// Creates Undergrad_Student object with given argument
	// Returns the total number of objects in the student array after adding
	students[++top] = new Undergrad_Student(name, stunum, freshmenclass);
	std::cout << "add undergraduate student DONE" << std::endl;
	return top+1;
};

// You need to implement operator overloading and use it in compare_student

bool Manager::compare_student(int index, std::string name, int stunum, int freshmenclass)
{
	// Compares whether the object with given index argument in the student array is the same to Undergrad_Student object with given arguments followed by index.
	// Returns true if they are the same, false otherwise

	Undergrad_Student given(name, stunum, freshmenclass);
	Undergrad_Student *ustu = (Undergrad_Student*)students[index];
	if(ustu != NULL && (*ustu) == given){
		std::cout << "compare to undergraduate student DONE" << std::endl;
		return true;
	}
	std::cout << "NOTHING found" << std::endl;
	return false;
};

bool Manager::compare_student(int index, std::string name, int stunum, std::string labname)
{
	// Compares whether the (index argument)th object in the student array is the same to Grad_Student object with given given argument follwed by index.
	// Returns true if they are the same, false otherwise
	
	Grad_Student given(name, stunum, labname);
	Grad_Student *gstu = (Grad_Student*)students[index];
	if(gstu != NULL && (*gstu) == given){
		std::cout << "compare to graduate student DONE" << std::endl;
		return true;
	}
	std::cout << "NOTHING found" << std::endl;
	return false;
};

int Manager::find_student(std::string name, int stunum, std::string labname)
{
	// Finds the Grad_Student object in the student array which is the same to Grad_Student object with given argument
	// This method should print all the information about matched object
	// Returns index of matched object (index of first object = 1), 0 if there's no match
	Grad_Student given(name, stunum, labname);
	for(int i=0; i<top+1; i++){
		Grad_Student *gstu = (Grad_Student*)students[i];
		if(gstu != NULL && (*gstu) == given){
			std::cout << "find graduate student DONE" << std::endl;
			given.getInfo();
			return i+1;
		}
	}
	std::cout << "NOTHING found" << std::endl;
	return 0;
};

int Manager::find_student(std::string name, int stunum, int freshmenclass)
{
	// Finds the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument
	// This method should prints all the information about matched object
	// Returns index of matched object (index of first object = 1), 0 if there's no match
	Undergrad_Student given(name, stunum, freshmenclass);
	for(int i=0; i<top+1; i++){
		Undergrad_Student *ustu = (Undergrad_Student*)students[i];
		if(ustu != NULL && (*ustu) == given){
			std::cout << "find undergraduate student DONE" << std::endl;
			given.getInfo();
			return i+1;
		}
	}
	std::cout << "NOTHING found" << std::endl;
	return 0;
};

int Manager::delete_student(std::string name, int stunum, std::string labname)
{
	// Deletes the Grad_Student object in the student array which is the same to Grad_Student object with given argument, does nothing if there's no matching
	// Returns the total number of objects in the student array after deleting
	Grad_Student given(name, stunum, labname);
	for(int i=0; i<top+1; i++){
		Grad_Student *gstu = (Grad_Student*)students[i];
		if(gstu != NULL && (*gstu) == given){
			delete students[i];

			for(int j=i+1; j<top+1; j++){
				students[j-1] = students[j];
			}
			students[top--] = NULL;

			break;
		}
	}
	std::cout << "delete graduate student DONE" << std::endl;
	return 0;
};

int Manager::delete_student(std::string name, int stunum, int freshmenclass)
{
	// Deletes the Undergrad_Student object in the student array which is the same to Undergrad_Student object with given argument, does nothing if there's no matching
	// Returns the total number of objects in the student array after deleting
	Undergrad_Student given(name, stunum, freshmenclass);
	for(int i=0; i<top+1; i++){
		Undergrad_Student *ustu = (Undergrad_Student*)students[i];
		if(ustu != NULL && (*ustu) == given){
			delete students[i];

			for(int j=i+1; j<top+1; j++){
				students[j-1] = students[j];
			}
			students[top--] = NULL;

			break;
		}
	}
	std::cout << "delete undergraduate student DONE" << std::endl;
	return 0;
};

int Manager::print_all()
{
	// Prints the all the information of existing object in the student array
	// Returns the total number of objects in the student array
	for(int i=0; i<top+1; i++){
		students[i]->getInfo();
		std::cout << std::endl;
	}
	std::cout << "print all DONE" << std::endl;
	return 0;
};

bool operator== (const Student& x, const Student& y)
{
	// operating overloading part. 
	// Check whether two students x, y have same information or not. 
	// Return true if two students are same, false otherwise.
	// p.s. this function must be used in at least "find_student ()" and "compare_student ()"
	if(typeid(x) == typeid(y)){
		if(typeid(x) == typeid(Grad_Student)){
			const Grad_Student *gx = dynamic_cast<const Grad_Student*>(&x);
			const Grad_Student *gy = dynamic_cast<const Grad_Student*>(&y);
			if(gx->name == gy->name && gx->stunum == gy->stunum && gx->labname == gy->labname)
				return true;
		}
		else if(typeid(x) == typeid(Undergrad_Student)){
			const Undergrad_Student *ux = dynamic_cast<const Undergrad_Student*>(&x);
			const Undergrad_Student *uy = dynamic_cast<const Undergrad_Student*>(&y);
			if(ux->name == uy->name && ux->stunum == uy->stunum && ux->freshmenclass == uy->freshmenclass)
				return true;
		}
	}
	return false;
}

///////////////////////////////////////////////////////////
// STUDENTS
///////////////////////////////////////////////////////////

Grad_Student::Grad_Student(std::string name, int stunum, std::string labname){
	this->name = name;
	this->stunum = stunum;
	this->labname = labname;
}

void Grad_Student::getInfo(){
	std::cout<<"===== Graduate Student ====="<<std::endl;
	std::cout<<"Name : "<<name<<std::endl;
	std::cout<<"Student Number : "<<stunum<<std::endl;
	std::cout<<"Lab Name : "<<labname<<std::endl;
	std::cout<<std::endl;
}

Undergrad_Student::Undergrad_Student(std::string name, int stunum, int freshmenclass){
	this->name = name;
	this->stunum = stunum;
	this->freshmenclass = freshmenclass;
	std::cout<<std::endl;
}

void Undergrad_Student::getInfo(){
	std::cout<<"===== Undergraduate Student ====="<<std::endl;
	std::cout<<"Name : "<<name<<std::endl;
	std::cout<<"Student Number : "<<stunum<<std::endl;
	std::cout<<"Freshman Class : "<<freshmenclass<<std::endl;
}