/**
 * @ file       : DisjSets.h
 * @author      : Mir Ahmed
 * @description : The following class does union find on a sets. It is well known for
 				  it's fast operation for union-find. This class is created to test whether
 				  a random graph is connected. If the random graph is connected, in other words,
 				  each vertex in the graph is at least connected to one other vertex, then union-find
 				  algorithm creates ONLY ONE SET with all the elements.
 * @date-created: 4-26-2016    
*/
#include <iostream>
#include <vector>
using namespace std;

class DisjSets {
 public:
	explicit DisjSets( unsigned int numElements ) {
		for (unsigned int i = 0; i <= numElements; ++i)
			s.push_back(-1);
	}
 	int find( int x ) const {
 		if( s[x] < 0 )
			return x;
 		else
			return find( s[x] );
 	}
	int find( int x ) {
		if( s[x] < 0 )
			return x;
 		else
			return find( s[x] );
	}
	void unionSets(int root1, int root2){
		if(s[root2] < s[root1])		//root2 is deeper
			s[root1] = root2;		//Make root2 new root
		else{
			if(s[root1] == s[root2])
				--s[root1];			//update height if same
			s[root2] = root1;		//ake root1 new root
		}
	}
	bool AllConnected() {
		for(unsigned int i = 1; i < s.size(); i++)
			if(s[i] == -1)
				return false;
		return true;
	}
	vector<int>& GetElements() {
		return s;
	}	

private:
	vector<int> s;
};
