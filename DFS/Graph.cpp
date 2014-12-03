#include "Graph.h"

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::loadFromFile(std::string const & fileName) {
	std::ifstream fin(fileName);
	size_t n = 0;
	size_t m = 0;
	fin >> n >> m;
	NodePayLoad inform;

	for (size_t i = 0; i < n; i++) {
		fin >> inform;
		this->addNode(inform);
	}

	int x = 0;
	int y = 0;
	EdgePayLoad weight;

	for (size_t i = 0; i < m; i++) {
		fin >> x >> y >> weight;
		this->addEdge(vertexes[x - 1], vertexes[y - 1], weight);
	}

	fin.close();
}

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::saveToFile(std::string const & fileName) {
	std::ofstream fout(fileName);
	fout << vertexes.size() << " " << edges.size() << std::endl;

	for (auto & node : vertexes) {
		fout << node->getInform() << " ";
	}

	fout << std::endl;

	for (auto &edge : edges) {
		fout << edge->vertFrom->getNumb() + 1 << " " << edge->vertTo->getNumb() + 1 << " " << edge->getWeight() << std::endl;
	}

	fout.close();
}

template<typename NodePayLoad, typename EdgePayLoad>
typename Graph<NodePayLoad, EdgePayLoad>::NodeHandle Graph<NodePayLoad, EdgePayLoad>::addNode(NodePayLoad const &inform) {
	vertexes.push_back(new Node<NodePayLoad, EdgePayLoad>(vertexes.size(), inform));
	return vertexes[vertexes.size() - 1];
}

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::addEdge(NodeHandle const &a, NodeHandle const &b, EdgePayLoad const &weight) {
	if (a == b)
		return;

	Edge<NodePayLoad, EdgePayLoad>* edge1 = new Edge<NodePayLoad, EdgePayLoad>(a, b, weight);
	Edge<NodePayLoad, EdgePayLoad>* edge2 = new Edge<NodePayLoad, EdgePayLoad>(b, a, weight);
	edges.push_back(edge1);
	a->vecOfEd->push_back(edge1);
	b->vecOfEd->push_back(edge2);
}

template<typename NodePayLoad, typename EdgePayLoad>
size_t Graph<NodePayLoad, EdgePayLoad>::getNodesCount() const {
	return vertexes.size();
}

template<typename NodePayLoad, typename EdgePayLoad>
NodePayLoad &Graph<NodePayLoad, EdgePayLoad>::operator[](NodeHandle const &  node) {
	return node->getInform();
}

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::forEachNode(std::function<void(NodeHandle const &)> const & visitor) const {
	for (auto &node : vertexes) {
		visitor(node);
	}
}

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::forEachEdge(NodeHandle const & source, EdgeVisitor const & visitor) {
	for (auto & edge : (*source->vecOfEd)) {
		visitor(edge);
	}
}

template<typename NodePayLoad, typename EdgePayLoad>
typename Graph<NodePayLoad, EdgePayLoad>::NodeHandle Graph<NodePayLoad, EdgePayLoad>::move(NodeHandle const & origin, EdgeHandle const & edge) {
	return edge->vertFrom == origin ? edge->vertTo : edge->vertFrom;
}

template<typename NodePayLoad, typename EdgePayLoad>
void Graph<NodePayLoad, EdgePayLoad>::dfs(NodeVisitor const & startNode, NodeVisitor const & endNode, NodeVisitor const &discoverNode) {
	std::vector<bool> used(vertexes.size());
	
	for (auto &node : vertexes)
		used.push_back(false);

	NodeHandle currentNode;

	for (auto &node : vertexes) {
		if (!used[node->getNumb()]) {
			std::stack<NodeHandle> stack;
			stack.push(node);

			while (!stack.empty()) {
				currentNode = stack.top();
				stack.pop();
				startNode(currentNode);
	
				for (auto k = vertexes[currentNode->getNumb()]->vecOfEd->begin(); k != vertexes[currentNode->getNumb()]->vecOfEd->end(); k++) {
					discoverNode((*k)->vertTo);
					if (!used[(*k)->vertTo->getNumb()]) {
						used[(*k)->vertTo->getNumb()] = true;
						stack.push((*k)->vertTo);
					}
				}
				endNode(currentNode);
			}
		}
	}

}
