student : main.o student.o
	g++ -o student main.o student.o

main.o : main.cpp
	g++ -c -o main.o main.cpp

student.o : student.cpp
	g++ -c -o student.o student.cpp

clean :
	rm student *.o