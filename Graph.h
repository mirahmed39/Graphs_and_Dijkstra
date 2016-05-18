/**
 * @ file       : Graph.h
 * @author      : Mir Ahmed
 * @description : The Graph class consists of vector of vertex pointers. It has a size that indicates
 				  many refernces to vertices it contains. One special operation this class performs is
 				  known as RunDijkstra. If Dijkstra is run on a graph starting from a specific vertex, it 
 				  calculates the shortest path from that starting vertex to all other vertices.
 * @date-created: 4-26-2016    
*/
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>
#include <iostream>
#include "Vertex.h"
#include <queue>
using namespace std;


class Graph {
public:
	Graph() : size_{0} {
	//nothing here.
	}
	
	Graph(const Graph &rhs) {
		vertices_ = rhs.vertices_;
		size_ = rhs.size_;
	}

	Graph(Graph &&rhs) { //move constructor
		vertices_ = std::move(rhs.vertices_);
		size_ = std::move(rhs.size_);
	}
	Graph& operator=(const Graph &rhs) { //copy assignment
		vertices_.clear();
		size_ = rhs.size_;
		vertices_ = rhs.vertices_;

		return *this;
	}
	Graph& operator=(Graph &&rhs) { // move assignment
		vertices_.clear();
		std::swap(vertices_, rhs.vertices_);
		std::swap(size_, rhs.size_);

		return *this;
	}
	~Graph() = default;
	bool isEmpty() const {
		return size_ == 0;
	}

	void SetSize(int size) {
		size_ = size;
	}

	int GetSize() const {
		return size_;
	}

	void Insert(Vertex *v) {
		vertices_.push_back(v);
		++size_;
	}

	void Insert(Vertex *&&v) {
		vertices_.push_back(std::move(v));
		++size_;
	}

	Vertex* GetVertex(int id) {
		for (unsigned int i = 0; i < vertices_.size(); ++i) {
			if (vertices_[i]->GetId() == id)
				return vertices_[i];
		}
	}

	vector<Vertex *>& GetVertices() {
		return vertices_;
	}

	double IsConnected(Vertex &v1, Vertex &v2) {
		double result;
		for(unsigned int i = 0; i < vertices_.size(); ++i) {
			if(vertices_[i]->GetId() == v1.GetId()) {
				result = vertices_[i]->FindAdjacent(v2);
				if (result < 0)
					result = -1;
				else 
					return result;
			}
		}
		return result; 
	}

	// Dijkstra's algorithm based on a priority queue.
	void RunDijkstra(Vertex &start_vertex) {
		for(auto v : vertices_) {
			// 999 here considered as infinity.
			v->SetDistance(999);
			v->SetKnown(false);
		}
		unsigned int i; // savesd the position of the starting vertex.
		for (i = 0; i < vertices_.size(); ++i) {
			if(vertices_[i]->GetId() == start_vertex.GetId())
				break;
		}
		std::priority_queue<Vertex*, vector<Vertex*>, Comparator> pq;
		vertices_[i]->SetDistance(0);
		for (unsigned int j = 0; j < vertices_.size(); ++j) {
			Vertex *ptr = vertices_[j];
			pq.push(ptr);
		}
		while (!pq.empty()) {
			Vertex *ptr = pq.top();
			pq.pop();
			auto adjacents = ptr->GetAdjacent();
			auto weights = ptr->GetWeight();
			for (unsigned int k = 0; k < adjacents.size(); ++k) {
				Vertex *current_adjacent_vertex = adjacents[k];
				double current_adjacent_weight = weights[k];
				double new_distance = current_adjacent_weight + ptr->GetDistance();
				if (new_distance < current_adjacent_vertex->GetDistance()) {
					current_adjacent_vertex->SetDistance(new_distance);
					current_adjacent_vertex->SetPath(ptr);
				}
			}
		}
	}

	void PrintPath(Vertex* v) const {
		if (v->GetPath() != nullptr) {
			PrintPath(v->GetPath());
			cout << " to ";
		}
		cout << v->GetId();
	}

	void PrintDistance(Vertex* v) {
		cout << v->GetDistance();
	}

	void PrintGraph() {
		for(unsigned int i = 0; i < vertices_.size(); ++i) {
			cout << "Vertex ";
			cout << vertices_[i]->GetId() << " ";
			cout << "adjacents: " << "";
			vertices_[i]->PrintAdjacent();
			cout << endl;
		}
	}

	//calculates the smallest outdegree of a vertex.
	int SmallestOutDegree() {
		int min = vertices_[0]->GetAdjacentSize();
		for (unsigned int i = 1; i < vertices_.size(); ++i){
			if (vertices_[i]->GetAdjacentSize() < min)
				min = vertices_[i]->GetAdjacentSize();
		}
		return min;
	}

	//calculates the largest outdegree of a vertex.
	int LargestOutDegree() {
		int max = vertices_[0]->GetAdjacentSize();
		for (unsigned int i = 1; i < vertices_.size(); ++i){
			if (vertices_[i]->GetAdjacentSize() > max)
				max = vertices_[i]->GetAdjacentSize();
		}
		return max;
	}

//calcualtes the total outdegrees of the vertices inside graph.
	int TotalOutDegrees() {
		int sum = 0;
		for (unsigned int i = 0; i < vertices_.size(); ++i)
			sum += vertices_[i]->GetAdjacentSize();
		return sum;
	}

private:
	size_t size_;
	vector<Vertex *> vertices_;
};

#include "Vertex.h"
#endif //_GRAPH_H_