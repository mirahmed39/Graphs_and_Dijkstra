/**
 * @ file       : Vertex.h
 * @author      : Mir Ahmed
 * @description : The following class creates Vertext object that has an unique
 				  id, a vector that contains pointers to other vertices inside the
 				  graph which tells us about the connection between vertices, a vector
 				  of weights which contains the weights of the edges that connect vertices,
 				  a distance variable that tells us how far the vertex object is from another
 				  specified vertex, and a path_ that stores the reference to the previous 
 				  vertex connected to it.
 * @date-created: 4-21-2016    
*/
#ifndef _VERTEX_H_
#define _VERTEX_H_
#include <vector>
#include <iostream>
//#include <queue>

using namespace std;

class Vertex {
public:
	Vertex() {} // default constructor.
	Vertex(int id) : id_{id}, known_{false} {
		//nothing here.
	}

	Vertex(const Vertex &rhs) { // copy constructor
		id_ = rhs.id_;
		adj_ = rhs.adj_;
		weights_ = rhs.weights_;
	}

	Vertex(Vertex &&rhs) { //move constructor
		id_ = std::move(rhs.id_);
		adj_ = std::move(rhs.adj_);
		weights_ = std::move(rhs.weights_);
	}

	Vertex& operator=(const Vertex &rhs) { //copy assignment
		adj_.clear();
		weights_.clear();
		id_ = rhs.id_;
		adj_ = rhs.adj_;
		weights_ = rhs.weights_;

		return *this;
	}

	Vertex& operator=(Vertex &&rhs) {  // move assignment
		id_ = std::move(rhs.id_);
		std::swap(adj_, rhs.adj_);
		std::swap(weights_, rhs.weights_);

		return *this;
	}

	~Vertex() = default;

	int GetId() const {
		return id_;
	}

	bool GetKnown() const {
		return known_;
	}

	double GetDistance() const {
		return distance_;
	}

	vector<Vertex *>& GetAdjacent() {
		return adj_;
	}

	int GetAdjacentSize() const {
		return adj_.size();
	}

	vector<double>& GetWeight() {
		return weights_;
	}

	Vertex* GetPath() {
		return path_;
	}

	void SetId(const int &id) {
		id_ = id;
	}
	void SetKnown(bool var) {
		known_ = var;
	}

	void SetDistance(double &distance) {
		distance_ = distance;
	}

	void SetDistance(double &&distance) {
		distance_ = std::move(distance);
	}

	void SetPath(Vertex *path_ptr) {
		path_ = path_ptr;
	}

	// adds an adjacent vertex to the current one
	// vertex_ptr is the reference to the vertex that will be connected
	// weight is the weight between the two connected vertices.
	void AddAdjacent(Vertex *vertex_ptr, double weight) {
		adj_.push_back(vertex_ptr);
		weights_.push_back(weight);
	}

	bool HasAdjacent() {
		return adj_.size() > 0;
	}

	// returns true if the veretx has already the adjacent vertex.
	// ptr is the reference to the vertex that will be checked for duplicate.
	bool HasDuplicate(Vertex *ptr) {
		for (unsigned int i = 0; i < adj_.size(); ++i) {
			if (ptr->GetId() == adj_[i]->id_)
				return true;
		}
		return false;
	}

	double FindAdjacent(Vertex &v) {
		for (unsigned int i = 0; i < adj_.size(); ++i) {
			if(adj_[i]->id_ == v.id_)
				return weights_[i];
		}
		return -1;
	}

	void PrintAdjacent() {
		for(unsigned int i = 0; i < adj_.size(); ++i) {
			cout << adj_[i]->id_ << " ";
		}
	}
private:
	int id_;
	vector<Vertex *> adj_;
	vector<double> weights_;
	bool known_;
	double distance_;
	Vertex *path_ = nullptr;
};

// a comparator class for the priority queue which does the 
// comparison based on the distance each vertex has.
class Comparator
{
public:
	bool operator()(const Vertex *lhs, const Vertex *rhs) {
		return lhs->GetDistance() > rhs->GetDistance();
	}
};
#endif // _VERTEX_H_	