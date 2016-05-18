#include <iostream>
#include <fstream>
#include "Vertex.h"
#include "Graph.h"
#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;

void CreateGraph(Graph &graph_obj, const string& filename);

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_FILE> <STARTING VERTEX>" << endl;
		return 0;
	}
	else {
		const string filename(argv[1]);
		int start_dijkstra= atoi(argv[2]);
		Graph graph_obj;
		CreateGraph(graph_obj, filename);
		auto vertices = graph_obj.GetVertices();
		Vertex v{start_dijkstra};
		graph_obj.RunDijkstra(v);
		for (unsigned int i = 1; i < vertices.size(); ++i) {
			cout << vertices[i]->GetId() << ": ";
			graph_obj.PrintPath(vertices[i]);
			cout << ". Total Cost: ";
			graph_obj.PrintDistance(vertices[i]);
			cout << endl;
		}
	}

	return 0;
	
}

void CreateGraph(Graph &graph_obj, const string& filename) {
	ifstream file(filename);
	string line;
	int skip_first_line = 1;
	int number_of_vertices;
	int position = 0;
	if (!file.good()) {
		cerr << "Error Opening file\n";
	}
	else {
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
}

