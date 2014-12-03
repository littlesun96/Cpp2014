#ifndef EDGE_H
#define EDGE_H

#include "Graph.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <functional>

template<typename NodePayLoad, typename EdgePayLoad>
class Graph;

template<typename NodePayLoad, typename EdgePayLoad>
class Node;

template<typename NodePayLoad, typename EdgePayLoad>
class Edge {
	
	friend class Graph<NodePayLoad, EdgePayLoad>;

private:
	Node<NodePayLoad, EdgePayLoad>* vertFrom;
	Node<NodePayLoad, EdgePayLoad>* vertTo;
	EdgePayLoad weight;

public:
	//constructor
	Edge(Node<NodePayLoad, EdgePayLoad>* vertFrom, Node<NodePayLoad, EdgePayLoad>* vertTo, EdgePayLoad weight);
	
	// destructor
	~Edge() {
	}

	// Returns start node
	Node<NodePayLoad, EdgePayLoad>* getVertFrom() const;

	// Returns end node
	Node<NodePayLoad, EdgePayLoad>* getVertTo() const;

	// Return weight
	EdgePayLoad getWeight() const;

	// Return true if these nodes are connected by this edge
	bool connects(Node<NodePayLoad, EdgePayLoad>* nodeFirst, Node<NodePayLoad, EdgePayLoad>* nodeSecond) const;
};


#endif