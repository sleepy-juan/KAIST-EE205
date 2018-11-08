all: yimacs_avl.o avl_tree.o linked_list.o jtest.o
	g++ -std=c++11 -o yimacs_avl yimacs_avl.o avl_tree.o linked_list.o
	g++ -std=c++11 -o jtest jtest.o avl_tree.o linked_list.o

yimacs_avl.o: yimacs_avl.cpp
	g++ -std=c++11 -c -o yimacs_avl.o yimacs_avl.cpp

avl_tree.o: avl_tree.cpp
	g++ -c -o avl_tree.o avl_tree.cpp

linked_list.o: linked_list.cpp
	g++ -c -o linked_list.o linked_list.cpp

jtest.o: jtest.cpp
	g++ -std=c++11 -c -o jtest.o jtest.cpp

clean:
	rm yimacs_avl jtest *.o