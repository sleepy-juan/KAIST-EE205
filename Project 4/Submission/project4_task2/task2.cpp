/*
    task2.cpp
    - task2, project 4, Data Structure

    Author @ Juan Lee(juanlee@kaist.ac.kr)
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <list>
#include <queue>
using namespace std;

#include "ADT_graph.h"

//--------------------------------------------------
// declarations
void findMST(ADT_Graph<int> *graph, string outputfile);
void findShortestPath(ADT_Graph<int> *graph, string inputfile, string outputfile);
void _findShortestPath(ADT_Graph<int> *graph, ofstream *output, string from, string to);

// Compare function set for priority queue
struct cmp{
    bool operator()(ADT_Edge<int> *e1, ADT_Edge<int> *e2){
        if(e1->get_edge_value() != e2->get_edge_value())
            return e1->get_edge_value() > e2->get_edge_value();
        
        string fe1 = e1->get_first_node().get_node_name();
        if(e1->get_second_node().get_node_name() < fe1)
            fe1 = e1->get_second_node().get_node_name();
        
        string fe2 = e2->get_first_node().get_node_name();
        if(e2->get_second_node().get_node_name() < fe2)
            fe2 = e2->get_second_node().get_node_name();
        
        return fe1 > fe2;
    }
};

//--------------------------------------------------
// main function
int main(int argc, char *argv[]){
    string line;
    ADT_Graph<int> *graph = new ADT_Graph<int>("graph");

    ifstream input(argv[1]);
    if(input.is_open()){
        getline(input, line);       // "Node"
        while(true){
            getline(input, line);
            if(line == "") break;

            graph->insertVertex(line, 0);   // any value
        }

        getline(input, line);       // "Edge"
        while(!input.eof()){
            getline(input, line);
            if(line == "") break;

            string node1, node2;
            int weight;

            stringstream ss(line);
            ss>>node1>>node2>>weight;

            graph->insertEdge(node1, node2, node1 + "-" + node2, weight);
        }
    }
    input.close();

    findMST(graph, argv[4]);
    findShortestPath(graph, argv[2], argv[3]);

    delete graph;
    return 0;
}

void findMST(ADT_Graph<int> *graph, string outputfile){
    map<string, int> clusters;          // store cluster
    
    // initialze clusters
    list<ADT_Node<int>*> nodes = graph->get_ADT_nodelist().get_node_list();
    int num_node = 0;
    for(ADT_Node<int>* node: nodes){
        clusters[node->get_node_name()] = num_node++;
    }

    // initialize edges
    priority_queue<ADT_Edge<int>*, vector<ADT_Edge<int>*>, cmp> edges;
    list<ADT_Edge<int>*> graph_edges = graph->get_ADT_edgelist().get_edge_list();
    for(ADT_Edge<int>* edge: graph_edges){
        edges.push(edge);
    }

    // storing
    priority_queue<ADT_Edge<int>*, vector<ADT_Edge<int>*>, cmp> connected;

    // Kruskal
    int num_edge = 0;
    while(num_node - 1 > num_edge){
        ADT_Edge<int> *edge = edges.top();
        edges.pop();

        ADT_Node<int> first = edge->get_first_node();
        ADT_Node<int> second = edge->get_second_node();

        if(clusters[first.get_node_name()] != clusters[second.get_node_name()]){
            connected.push(edge);

            int fid = clusters[first.get_node_name()];
            int sid = clusters[second.get_node_name()];
            for(auto iter = clusters.begin(); iter != clusters.end(); iter++){
                if(iter->second == sid){
                    clusters[iter->first] = fid;
                }
            }

            num_edge++;
        }
    }

    // store output
    ofstream output(outputfile);
    while(!connected.empty()){
        ADT_Edge<int> *edge = connected.top();
        connected.pop();

        if(edge->get_first_node().get_node_name() < edge->get_second_node().get_node_name()){
            output << edge->get_first_node().get_node_name() << " ";
            output << edge->get_second_node().get_node_name() << " ";
        }
        else{
            output << edge->get_second_node().get_node_name() << " ";
            output << edge->get_first_node().get_node_name() << " ";
        }
        output << edge->get_edge_value() << endl;
    }
    output.close();
}

void findShortestPath(ADT_Graph<int> *graph, string inputfile, string outputfile){
    ifstream input(inputfile);
    ofstream output(outputfile);
    string line;
    if(input.is_open()){
        while(!input.eof()){
            getline(input, line);
            if(line == "") break;

            stringstream ss(line);
            string from, to;
            ss>>from>>to;

            _findShortestPath(graph, &output, from, to);
        }
    }
    input.close();
    output.close();
}

void _findShortestPath(ADT_Graph<int> *graph, ofstream *output, string from, string to){
    map<string, bool> visited;
    map<string, int> distance;
    map<string, string> parent;

    // initialize
    list<ADT_Node<int>*> nodes = graph->get_ADT_nodelist().get_node_list();
    int num_node = nodes.size();
    for(ADT_Node<int>* node: nodes){
        visited[node->get_node_name()] = false;
        distance[node->get_node_name()] = -1;
        parent[node->get_node_name()] = "";
    }
    
    // for the very first node
    distance[from] = 0;

    // Dijkstra
    for(int index = 0; index < num_node; index++){
        // find min
        int minDist = -1;
        string minNode;
        for(auto iter = distance.begin(); iter != distance.end(); iter++){
            if((minDist == -1 && iter->second != -1) || (minDist != -1 && iter->second != -1 && minDist > iter->second)){
                if(!visited[iter->first]){
                    minDist = iter->second;
                    minNode = iter->first;
                }
            }
        }

        // visit
        visited[minNode] = true;
        ADT_Node<int> *found = graph->get_ADT_nodelist().search_vertex(minNode);
        for(ADT_Edge<int> *edge: found->incidentEdges()){
            string opposite = edge->opposite(minNode);

            int new_value = minDist + edge->get_edge_value();
            if(distance[opposite] == -1 || distance[opposite] > new_value){
                distance[opposite] = new_value;
                parent[opposite] = minNode;
            }
        }
    }

    string cursor = to;
    string result = to_string(distance[to]);
    while(cursor != from){
        result = cursor + " " + result;
        cursor = parent[cursor];
    }
    (*output) << from << " " << result << endl;
}