#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Graph.h"
#include "Vertex.h"
#include "DisjSets.h"
using namespace std;

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <maximum_number_of_nodes>" << endl;
		return 0;
	}
	else {
		const int max_value = atoi(argv[1]);
		srand(time(0));
		Graph graph_obj;
		DisjSets set(max_value);
		//populating the graph.
		for (int i = 1; i <= max_value; ++i) {
			Vertex *ptr = new Vertex{i};
			graph_obj.Insert(ptr);
		}
		int number_of_edges = 0;
		auto vertices = graph_obj.GetVertices();
		while (true) {
			const int random_number1 = rand() % max_value + 1;
			const int random_number2 = rand() % max_value + 1;
			if (random_number1 != random_number2) {
				int position_for_vertex1 = random_number1 - 1;
				int position_for_vertex2 = random_number2 - 1;
				Vertex *ptr1 = vertices[position_for_vertex1];
				Vertex *ptr2 = vertices[position_for_vertex2];
				if (!ptr1->HasDuplicate(ptr2)) {
					vertices[position_for_vertex1]->AddAdjacent(ptr2, 1);
					vertices[position_for_vertex2]->AddAdjacent(ptr1, 1);
					++number_of_edges;
					set.unionSets(random_number1, random_number2);
				}
			}
			// this one checks whether all the vertices are connected. If they are, we are done.
			if (set.AllConnected())
				break;
		}
		cout << "Number of edges: " << number_of_edges << endl;
		cout << "Smallest Out Degree: " << graph_obj.SmallestOutDegree() << endl;
		cout << "Largest Out Degree : " << graph_obj.LargestOutDegree() << endl;
		cout << "Average Out Degree : " <<  graph_obj.TotalOutDegrees() / max_value << endl;

		return 0;
	}
}