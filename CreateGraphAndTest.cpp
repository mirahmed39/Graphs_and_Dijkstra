#include <iostream>
#include "Graph.h"
#include "Vertex.h"
#include <fstream>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

void CreateGraph(Graph &graph_obj, const string& filename);
void TestGraph(Graph &graph_obj, const string &query_file);
void RunDijkstra(Graph &graph_obj);

int main(int argc, char const *argv[])
{
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <QUERY FILE>" << endl;
		return 0;
	}
	string input_file(argv[1]);
	string query_file(argv[2]);
	Graph graph_obj;
	CreateGraph(graph_obj, input_file);
	TestGraph(graph_obj, query_file);

	return 0;
}

void CreateGraph(Graph &graph_obj, const string& filename) {
	ifstream file(filename);
	string line;
	int skip_first_line = 1;
	int number_of_vertices;
	int position = 0;
	while (getline(file, line)) {
		if (skip_first_line == 1) {
			stringstream ss1;
			ss1 << line;
			ss1 >> number_of_vertices;
			for (int i = 1; i <= number_of_vertices; ++i) {
				Vertex *ptr = new Vertex{i};
				graph_obj.Insert(ptr);
			}
			ss1.clear();
			skip_first_line = 0;
			continue;
		}
		int count_entry = 0;
		for (unsigned int i = 0; i < line.length(); ++i) {
			if (isspace(line[i]))
				++count_entry;
		}
		int id, adjacent_id;
		double weight;
		stringstream ss;
		int start_adjacent = 1;
		ss << line;
		ss >> id; // we actually do not need it, we have pre-created all the vertices.
		vector<Vertex *> vertices = graph_obj.GetVertices(); 
		while(start_adjacent <= count_entry) {
			ss >> adjacent_id; 
			ss >> weight;
			Vertex *ptr = vertices[adjacent_id - 1];
			//cout << ptr->GetId() << endl;
			vertices[position]->AddAdjacent(ptr, weight);
			//vertices[position]->PrintAdjacent();
			start_adjacent += 2;
	 	}
	 	position++;
	 	ss.clear();
	 }
	 file.close();
}

void TestGraph(Graph &graph_obj, const string &query_file) {
	ifstream file2(query_file);
	int id1, id2;
	while(file2 >> id1 >> id2) {
		Vertex v1{id1};
		Vertex v2{id2};
		double connected_weight = graph_obj.IsConnected(v1, v2);
		if (connected_weight > 0)
			cout << id1 <<  " " << id2 << " : Connected, weight of edge is " << connected_weight << endl;
		else
			cout <<  id1 <<  " " << id2 << " : Not Connected\n";
	}
	file2.close();
}

