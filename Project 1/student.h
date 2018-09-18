// //***************************************************************
// //                   CLASS USED IN PROJECT
// //****************************************************************

class Student{
	// ******Modify here******
	// You need to properly define member variable in Student class
 private:
 protected:
 	std::string name;
 	int stunum;

 public:
	// ******Modify here******
	// You need to implement get function which prints out every information about student argument in pure virtual function here
 	virtual ~Student(){}

	virtual void getInfo() = 0;
};

class Grad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Grad_Student class
 private:
 	std::string labname;
 protected:
 public:	
	// ******Modify here******
	// You need to implement get function in detail
	Grad_Student(std::string name, int stunum, std::string labname);

	void getInfo();

	friend bool operator==(const Student& x, const Student& y);
};

class Undergrad_Student: public Student{
	// ******Modify here******
	// You need to properly define member variable in Undergrad_Student class
 private:
 	int freshmenclass;
 protected:
 public:
	// ******Modify here******
	// You need to implement get function in detail
	Undergrad_Student(std::string name, int stunum, int freshmenclass);

	void getInfo();

	friend bool operator==(const Student& x, const Student& y);
};

class Manager{
	// ******Modify here******
	// You need to properly define member variable in Manager class
 private:
 	Student *students[300];
 	int top;
 protected:
 public:
	// ******Modify here******
	// You need to implement every methods in Manager class
 	Manager();
 	~Manager();

	int add_student(std::string name, int stunum, std::string labname);
	int add_student(std::string name, int stunum, int freshmenclass);
	bool compare_student(int index, std::string name, int stunum, std::string labname);
	bool compare_student(int index, std::string name, int stunum, int freshmenclass);
	int find_student(std::string name, int stunum, std::string labname);
	int find_student(std::string name, int stunum, int freshmenclass);
	int delete_student(std::string name, int stunum, std::string labname);
	int delete_student(std::string name, int stunum, int freshmenclass);
	int print_all();

};
