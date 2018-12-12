/*
 * Skeleton code for project 4 in EE205 2018 FALL KAIST
 * Created by Joonki Hong
 */

#include "ADT_graph.h"
#include <iostream>

using namespace std;

/*
 * Tips!!!!
 *
 * 1. Search 'YOUR CODE GOES HERE' to find where to implement.
 * 2. Use commented Debug to get the insight of adjacency list structure.
 * 3. You can compile this file by 'g++ -c ADT_graph.cpp'.
 * 4. You can compile with main.cpp by 'g++ main.cpp ADT_graph.cpp' after you fill the blanks.
 */


/*
 * I know that this project is a little bit tough, but I beleive you can do this!!!
 * Feel free to ask TA!!!
 */


    // _    ____ _____   _   _           _
   // / \  |  _ \_   _| | \ | | ___   __| | ___
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|
                // |_____|

/*************************** ADT_Node ***************************/

/* Get node name */
template <class T>
string ADT_Node<T>::get_node_name(void) {
	return node_name;
}

/* Get node value */
template <class T>
T ADT_Node<T>::get_node_value(void) {
	return node_value;
}

/* Add new incidence collection */
template <class T>
int ADT_Node<T>::add_incidence(void){
	incidence = new ADT_Incidence<T>;
	return 1;
}

/* Remove incidence */
template <class T>
int ADT_Node<T>::remove_incidence(void){
	delete incidence;
	return 1;
}

/* erase one edge from incidence list */
template <class T>
int ADT_Node<T>::erase_edge_from_incidence(ADT_Edge<T>* edge) {
	incidence->remove_incidence_list(edge);
	return 1;
}

/* return the begining of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_begin(void){
	return incidence->get_begin();
}

/* return the end of incidence list */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::get_end(void){
	return incidence->get_end();
}

/* Call add_incidence_list in incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Node<T>::add_incidence_list(ADT_Edge<T>* edge){
	return incidence->add_incidence_list(edge);
}

/* Save the node position information */
template <class T>
int ADT_Node<T>::add_nodelist_info(typename list<ADT_Node<T>*>::iterator node_position){
	this->node_position = node_position;
	return 1;
}

/* Basic functionality of ADT_Node */
template <class T>
list<ADT_Edge<T>*> ADT_Node<T>::incidentEdges(void) {
	/* use incidentEdges in incidence list */

	return incidence->incidentEdges();
}

template <class T>
int ADT_Node<T>::isAdjacentTo(string node_name) {
	/* use isAdjacentTo() function in incidence list	 */

	return incidence->isAdjacentTo(node_name);
}

/* Constructor, initializing the node name and the node value, add new incidence collcetion*/
template <class T>
ADT_Node<T>::ADT_Node(string node_name, T node_value) {

	this->node_name = node_name;
	this->node_value = node_value;
	add_incidence();
	/* Debug */
	/* cout << "Test2: node name "<< get_node_name()<<", node_value "<<get_node_value() <<endl << endl; */
}

 // ___            _     _
// |_ _|_ __   ___(_) __| | ___ _ __   ___ ___
 // | || '_ \ / __| |/ _` |/ _ \ '_ \ / __/ _ \
 // | || | | | (__| | (_| |  __/ | | | (_|  __/
// |___|_| |_|\___|_|\__,_|\___|_| |_|\___\___|

           // _ _           _   _
  // ___ ___ | | | ___  ___| |_(_) ___  _ __
 // / __/ _ \| | |/ _ \/ __| __| |/ _ \| '_ \
// | (_| (_) | | |  __/ (__| |_| | (_) | | | |
 // \___\___/|_|_|\___|\___|\__|_|\___/|_| |_|

/*************************** Incidence Collection ***************************/

/* Add new edge connection in the incidence collection */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::add_incidence_list(ADT_Edge<T>* edge) {
	return incidence_list.insert(incidence_list.end(), edge); // pointer will be replaced later
}

/* Remove an edge connection in the incidence collection */
template <class T>
int ADT_Incidence<T>::remove_incidence_list(ADT_Edge<T>* edge) {
	incidence_list.remove(edge);
	return 1;
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_begin(void){
	return incidence_list.begin();
}

template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Incidence<T>::get_end(void){
	return incidence_list.end();
}


template <class T>
int ADT_Incidence<T>::isAdjacentTo(string node_name) {
	/* check through incidence list for input node_name  */
	/* return 1 if you find it return 0 if you don't find it  */

	for(ADT_Edge<T>* edge: incidence_list){
		if(edge->get_first_node().get_node_name() == node_name || edge->get_second_node().get_node_name() == node_name)
			return 1;
	}
	return 0;
}

template <class T>
list<ADT_Edge<T>*> ADT_Incidence<T>::incidentEdges(void) {
	/* return list of incident edges */
	
	return incidence_list;
}



    // _    ____ _____   _____    _
   // / \  |  _ \_   _| | ____|__| | __ _  ___
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|
                // |_____|          |___/
/*************************** ADT_Edge ***************************/

/* Get edge name */
template <class T>
string ADT_Edge<T>::get_edge_name(void) {
	return edge_name;
}

/* Get edge value */
template <class T>
T ADT_Edge<T>::get_edge_value(void) {
	return edge_value;
}

/* Get first node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_first_node(void) {
	return *first_node;
}


/* Get second node */
template <class T>
ADT_Node<T> ADT_Edge<T>::get_second_node(void) {
	return *second_node;
}

/* Save pointer to the incidence collection of the first vertex and the second vertex */
template <class T>
int ADT_Edge<T>::add_incidence_info(typename list<ADT_Edge<T>*>::iterator first_incidence_position, typename list<ADT_Edge<T>*>::iterator second_incidence_position) {
	this->first_incidence_position = first_incidence_position;
	this->second_incidence_position = second_incidence_position;
	return 1;
}

/* Save the edge position information */
template <class T>
int ADT_Edge<T>::add_edgelist_info(typename list<ADT_Edge<T>*>::iterator edge_position) {
	this->edge_position = edge_position;
	return 1;
}

template <class T>
list<ADT_Node<T>*> ADT_Edge<T>::endVertices(void) {
	/* return a list that have pointer to the first node and second node of the edge */

	list<ADT_Node<T>*> result;
	result.push_back(first_node);
	result.push_back(second_node);
	return result;
}


template <class T>
string ADT_Edge<T>::opposite(string node_name) {
	/* return the opposite node of given vertex in string */
	/* if given vertex is not included in this edge return 0 */
	/* e.g. for edge A-B, given A, return B */
	/* e.g. for edge A-B, given C, return 0 */

	if(first_node->get_node_name() == node_name)
		return second_node->get_node_name();
	if(second_node->get_node_name() == node_name)
		return first_node->get_node_name();
	return 0;
}


template <class T>
int ADT_Edge<T>::isAdjacentTo(string edge_name) {
	/* check that the given edge is adjacent with first end node */
	/* check that the given edge is adjacent with second end node */
	/* return 1 if it is adjacent return 0 if not */

	for(ADT_Edge<T>* edge: first_node->incidentEdges()){
		if(edge->get_edge_name() == edge_name)
			return 1;
	}

	for(ADT_Edge<T>* edge: second_node->incidentEdges()){
		if(edge->get_edge_name() == edge_name)
			return 1;
	}
	return 0;
}


template <class T>
int ADT_Edge<T>::isIncidentOn(string node_name) {
	/* return 1 if given node is incident, return 0 if not  */
	/* check the first end node and the second end node  */

	if(first_node->get_node_name() == node_name || second_node->get_node_name() == node_name)
		return 1;
	return 0;
}


/* Constuctor, initializing edge name, edge value, and vertex name */
template <class T>
ADT_Edge<T>::ADT_Edge(string edge_name, T edge_value, ADT_Node<T> *first_node, ADT_Node<T> *second_node) {

	list<ADT_Edge<T>*> temp_list;

	this->edge_name = edge_name;
	this->edge_value = edge_value;
	this->first_node = first_node;
	this->second_node = second_node;

	/* Debug */
	/* cout << "Test5: edge name "<< get_edge_name() <<", edge value " <<get_edge_value() << endl <<endl; */
}


    // _    ____ _____   _   _           _      _ _     _
   // / \  |  _ \_   _| | \ | | ___   __| | ___| (_)___| |_
  // / _ \ | | | || |   |  \| |/ _ \ / _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |\  | (_) | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_| \_|\___/ \__,_|\___|_|_|___/\__|
                // |_____|
/*************************** ADT_Nodelist ***************************/

/* Add new node in the nodelist */
template <class T>
typename list<ADT_Node<T>*>::iterator ADT_Nodelist<T>::add_node_list(ADT_Node<T> *vertex) {
	return node_list.insert(node_list.end(),vertex);
}

/* Remove a node in the nodelist */
template <class T>
int ADT_Nodelist<T>::remove_node_list(ADT_Node<T> *vertex) {
	node_list.remove(vertex);
	return 1;
}


template <class T>
ADT_Node<T>* ADT_Nodelist<T>::search_vertex(string vertex) {
	/* return pointer to a node that has given node name */
	/* if there is no such node, return NULL */

	for(ADT_Node<T>* node: node_list){
		if(node->get_node_name() == vertex){
			return node;
		}
	}
	return NULL;
}

template <class T>
int	ADT_Nodelist<T>::print_all_vertices(void){
	/* print all vertices' name in the nodelist */

	for(ADT_Node<T>* node: node_list){
		cout << node->get_node_name() << endl;
	}

	return 1;
}

/* Return node list */
template <class T>
list<ADT_Node<T>*> ADT_Nodelist<T>::get_node_list(void) {
	return node_list;
}


    // _    ____ _____   _____    _            _ _     _
   // / \  |  _ \_   _| | ____|__| | __ _  ___| (_)___| |_
  // / _ \ | | | || |   |  _| / _` |/ _` |/ _ \ | / __| __|
 // / ___ \| |_| || |   | |__| (_| | (_| |  __/ | \__ \ |_
// /_/   \_\____/ |_|___|_____\__,_|\__, |\___|_|_|___/\__|
                // |_____|          |___/
/*************************** ADT_Edgelist ***************************/

/* Add new edge in the edgelist */
template <class T>
typename list<ADT_Edge<T>*>::iterator ADT_Edgelist<T>::add_edge_list(ADT_Edge<T> *edge) {
	return edge_list.insert(edge_list.end(),edge);
}

/* Remove a edge in the edgelist */
template <class T>
int ADT_Edgelist<T>::remove_edge_list(ADT_Edge<T> *edge) {
	edge_list.remove(edge);
	return 1;
}


template <class T>
ADT_Edge<T>* ADT_Edgelist<T>::search_edge(string edge) {
	/* return pointer to certain edge that has given edge name */
	/* if there is no such edge, return NULL */

	for(ADT_Edge<T>* edge_object: edge_list){
		if(edge_object->get_edge_name() == edge){
			return edge_object;
		}
	}
	return NULL;
}

template <class T>
int	ADT_Edgelist<T>::print_all_edges(void){
	/* print all edges' name in the edgelist */

	for(ADT_Edge<T>* edge: edge_list){
		cout << edge->get_edge_name() << endl;
	}

	return 1;
}
/* Return edge list */
template <class T>
list<ADT_Edge<T>*> ADT_Edgelist<T>::get_edge_list(void) {
	return edge_list;
}


    // _    ____ _____   ____                 _
   // / \  |  _ \_   _| / ___|_ __ __ _ _ __ | |__
  // / _ \ | | | || |  | |  _| '__/ _` | '_ \| '_ \
 // / ___ \| |_| || |  | |_| | | | (_| | |_) | | | |
// /_/   \_\____/ |_|___\____|_|  \__,_| .__/|_| |_|
                // |_____|             |_|

/*************************** ADT_Graph ***************************/

template <class T>
int ADT_Graph<T>::vertices(void) {
	return ADT_nodelist->print_all_vertices();
}


template <class T>
int ADT_Graph<T>::edges(void) {
	return ADT_edgelist->print_all_edges();
}


template <class T>
int ADT_Graph<T>::insertVertex(string node_name, T node_value) {

	/* 1. make new node object */
	/* 2. add new node object to nodelist */
	/* 3. add nodelist info to node object */

	ADT_Node<T>* node = new ADT_Node<T>(node_name, node_value);
	typename list<ADT_Node<T>*>::iterator iter = ADT_nodelist->add_node_list(node);
	node->add_nodelist_info(iter);

	return 1;

	/* Debug */
	/* cout << "Test3: node iterator is working??? " << (*node_iterator)->get_node_name() << endl << endl; */
}


template <class T>
int ADT_Graph<T>::insertEdge(string vertex_name1, string vertex_name2, string edge_name, T edge_value) {

	ADT_Node<T> *first_node, *second_node;
	typename list<ADT_Edge<T>*>::iterator edge_iterator, first_edge_iterator, second_edge_iterator;

	/* 1. Find corresponding ADT_Node with vertex name */
	/* 2. Make new edge and add it to edge list */
	/* 3. Add edge to incidence collection of the first and second vertex */
	/* 4. Add reverse connection to incidence collection */

	first_node = ADT_nodelist->search_vertex(vertex_name1);
	second_node = ADT_nodelist->search_vertex(vertex_name2);

	ADT_Edge<T>* edge = new ADT_Edge<T>(edge_name, edge_value, first_node, second_node);

	first_edge_iterator = first_node->add_incidence_list(edge);
	second_edge_iterator = second_node->add_incidence_list(edge);
	edge->add_incidence_info(first_edge_iterator, second_edge_iterator);

	edge_iterator = ADT_edgelist->add_edge_list(edge);
	edge->add_edgelist_info(edge_iterator);

	/* Debug */
	/* cout << "Test4: search_vertex??? "<< first_node->get_node_name() <<" "<< second_node->get_node_name() << endl <<endl; */
	/* cout << "Test6: edge iterator is working ??? "<< (*edge_iterator)->get_edge_name() <<" "<< (*edge_iterator)->get_edge_value() << endl <<endl; */

	return 1;
}


template <class T>
int ADT_Graph<T>::eraseVertex(string node_name) {
	/* 1. Use search_vertex() to find corresponding node pointer */
	/* 2. Erase all edges in incidence collection */
	/* 3. Remove node from nodelist */
	/* 4. Remove node */

	ADT_Node<T>* node = ADT_nodelist->search_vertex(node_name);

	list<ADT_Edge<T>*> edges = node->incidentEdges();
	for(ADT_Edge<T> *edge: edges){
		string opposite_name = edge->opposite(node_name);
		ADT_Node<T>* opposite = ADT_nodelist->search_vertex(opposite_name);
		opposite->erase_edge_from_incidence(edge);

		ADT_edgelist->remove_edge_list(edge);
	}

	ADT_nodelist->remove_node_list(node);
	
	node->remove_incidence();
	delete node;

	return 1;
}


template <class T>
int ADT_Graph<T>::eraseEdge(string edge_name) {
	/* find correstponding edge and call eraseEdge agian */

	ADT_Edge<T>* edge = ADT_edgelist->search_edge(edge_name);
	return eraseEdge(edge);
}


template <class T>
int ADT_Graph<T>::eraseEdge(ADT_Edge<T>* erase_edge) {

	/* 1. Erase edge in the first node incidence collection */
	/* 2. Erase edge in the second node incidence collection */
	/* 3. Erase edge from the edgelist */
	/* 4. Erase edge  */

	ADT_Node<T> first_node = erase_edge->get_first_node();
	first_node.erase_edge_from_incidence(erase_edge);

	ADT_Node<T> second_node = erase_edge->get_second_node();
	second_node.erase_edge_from_incidence(erase_edge);

	ADT_edgelist->remove_edge_list(erase_edge);

	delete erase_edge;

	return 1;
}

template <class T>
ADT_Nodelist<T> ADT_Graph<T>::get_ADT_nodelist(void) {
	return *ADT_nodelist;
}

template <class T>
ADT_Edgelist<T> ADT_Graph<T>::get_ADT_edgelist(void) {
	return *ADT_edgelist;
}

template <class T>
ADT_Graph<T>::ADT_Graph(string graph_name) {
	graph_name = graph_name;
	ADT_nodelist = new ADT_Nodelist<T>;
	ADT_edgelist = new ADT_Edgelist<T>;

	/* Debug */
	/* cout<<"Test1: graph name is "<<graph_name<<endl<<endl; */

}

template class ADT_Graph<int>;
template class ADT_Node<int>;
template class ADT_Edge<int>;
template class ADT_Edgelist<int>;
template class ADT_Nodelist<int>;
