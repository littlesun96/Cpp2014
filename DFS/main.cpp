#include "gtest.h"

#include "Graph.cpp"
#include "Node.cpp"
#include "Edge.cpp"

using namespace std;


namespace {
	int n = 50, n_max = -999;
	vector<int> num;
	Graph<int, int>::NodeHandle currentNode;
	Graph<int, int> graph, graph1;
	int currentColor;
	vector<int> colors;
	bool flag;


	void edgeClear(Graph<int, int>::EdgeHandle const & edge) {
		num.push_back(graph[edge->getVertFrom() == currentNode ? edge->getVertTo() : edge->getVertTo()]);
	}


	void myClear(Graph<int, int>::NodeHandle const &source) {
		num.clear();
		currentNode = source;
		graph.forEachEdge(source, edgeClear);
	}


	void edgeClear1(Graph<int, int>::EdgeHandle const &edge) {
		EXPECT_EQ(edge->getVertFrom(), graph.move(edge->getVertTo(), edge));
		EXPECT_EQ(edge->getVertTo(), graph.move(edge->getVertFrom(), edge));
	}

	void nodeVisitor(Graph<int, int>::NodeHandle const &source) {
		graph.forEachEdge(source, edgeClear1);
	}

	void startNode(Graph<int, int>::NodeHandle const &source) {
		colors[source->getNumb()] == n_max ? (colors[source->getNumb()] = currentColor) : (currentColor = colors[source->getNumb()]);
	}

	void discoverNode(Graph<int, int>::NodeHandle const &source) {
		if (colors[source->getNumb()] == n_max) {
			colors[source->getNumb()] = (currentColor + 1) % 2;
		}
		else if (colors[source->getNumb()] == currentColor) {
			flag = false;
		}
	}

	void endNode(Graph<int, int>::NodeHandle const &source) {
		currentColor = n_max;
	}

	bool myCheck() {
		currentColor = 0;
		for (size_t i = 0; i < graph.getNodesCount(); i++) {
			colors.push_back(n_max);
		}
		flag = true;
		graph.dfs(startNode, endNode, discoverNode);
		return flag;
	}
}

TEST(myGraphCheck, First) {
	int check = 999;
	graph = Graph<int, int>();
	for (int i = 0; i < check; i++)
		graph.addNode((i + 2) * 673 / 111);
	EXPECT_EQ(check, (int)graph.getNodesCount());
}

TEST(myGraphCheck, Second) {
	graph = Graph<int, int>();
	for (int i = 0; i < n; i++) {
		graph.addNode(i);
	}
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n; j++) {
			graph.addEdge(graph.getNodeHandleById(i), graph.getNodeHandleById(j), 0);
		}
	}
	EXPECT_EQ(n, (int)graph.getNodesCount());
	graph.forEachNode(myClear);
}

TEST(myGraphCheck, Third) {
	graph = Graph<int, int>();
	for (int i = 0; i < n; i++) {
		graph.addNode(i);
	}
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n; j++) {
			graph.addEdge(graph.getNodeHandleById(i), graph.getNodeHandleById(j), 0);
		}
	}
	graph.saveToFile("graph_test.txt");
	graph1 = Graph<int, int>();
	graph1.loadFromFile("graph_test.txt");
	EXPECT_EQ(n, (int)graph1.getNodesCount());
	graph.forEachNode(myClear);
}


TEST(myGraphCheck, Fouth) {
	graph = Graph<int, int>();
	Graph<int, int>::NodeHandle current;
	Graph<int, int>::NodeHandle prev;
	prev = graph.addNode(0);
	for (int i = 0; i < n - 1; i++) {
		current = graph.addNode(0);
		graph.addEdge(current, prev, 0);
		prev = current;
	}
	EXPECT_EQ(true, myCheck());
}


