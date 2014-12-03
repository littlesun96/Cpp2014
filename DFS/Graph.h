#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Node.h"

#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <stack>
#include <functional>

template<typename NodePayLoad, typename EdgePayLoad>
class Edge;

template<typename NodePayLoad, typename EdgePayLoad>
class Node;

template<typename NodePayLoad, typename EdgePayLoad>
class Graph {
	friend class Node<NodePayLoad, EdgePayLoad>;

	friend class Edge<NodePayLoad, EdgePayLoad>;

public:
	typedef Node<NodePayLoad, EdgePayLoad>* NodeHandle;
	typedef Edge<NodePayLoad, EdgePayLoad>* EdgeHandle;
	typedef std::function<void(NodeHandle const &)> NodeVisitor;
	typedef std::function<void(EdgeHandle const &)> EdgeVisitor;
private:
	std::vector<NodeHandle> vertexes;
	std::vector<EdgeHandle> edges;
public:

	//Constructor
	Graph() {
	}

	//Destructor
	~Graph() {
	}

	/*Loads graph from file like this:
	nodesCount " " edgesCount
	firstNodeInform " " secondNodeInform " " ... " " nodesCountNodeInform
	{
	first node index " " second node index " " edge weight
	...
	} edgesCount - 1 strings of information about edges*/
	void loadFromFile(std::string const &fileName);

	// Returns NodeHandle by numb in vector of nodes
	NodeHandle getNodeHandleById(size_t numb) const {
		return vertexes[numb];
	}

	// Saves graph to file like in loading
	void saveToFile(std::string const & fileName);

	// Adds node to graph
	NodeHandle addNode(NodePayLoad const &);

	// Adds edge to graph
	void addEdge(NodeHandle const & a, NodeHandle const & b, EdgePayLoad const &);

	// Make visitor function for every node
	void forEachNode(std::function<void(NodeHandle const &)> const & visitor) const;

	// Returns count of nodes
	size_t getNodesCount() const;

	// Make visitor function for every edge that contains source node
	void forEachEdge(NodeHandle const & source, EdgeVisitor const & visitor);

	// Returns another end of edge
	NodeHandle move(NodeHandle const & origin, EdgeHandle const &  edge);

	// Returns inform from node
	NodePayLoad & operator[](NodeHandle const & node);

	// Dfs
	void dfs(NodeVisitor const & startNode, NodeVisitor const & endNode, NodeVisitor const & discoverNode);
};

#endif
