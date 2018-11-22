all: yimacs_avl.o yimacs_rb.o avl_tree.o rb_tree.o linked_list.o jtest.o
	g++ -std=c++11 -o yimacs_avl yimacs_avl.o avl_tree.o linked_list.o
	g++ -std=c++11 -o yimacs_rb yimacs_rb.o rb_tree.o linked_list.o
	g++ -std=c++11 -o jtest jtest.o avl_tree.o rb_tree.o linked_list.o

yimacs_avl.o: yimacs_avl.cpp
	g++ -std=c++11 -c -o yimacs_avl.o yimacs_avl.cpp

yimacs_rb.o: yimacs_rb.cpp
	g++ -std=c++11 -c -o yimacs_rb.o yimacs_rb.cpp

avl_tree.o: avl_tree.cpp
	g++ -c -o avl_tree.o avl_tree.cpp

rb_tree.o: rb_tree.cpp
	g++ -c -o rb_tree.o rb_tree.cpp

linked_list.o: linked_list.cpp
	g++ -c -o linked_list.o linked_list.cpp

jtest.o: jtest.cpp
	g++ -std=c++11 -c -o jtest.o jtest.cpp

clean:
	rm yimacs_avl yimacs_rb jtest *.o