
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

using namespace std;

class Node {
public:
	Node() : visited(false), colored(false) {}

	std::vector<Node*> nb;
	unsigned id;
	bool visited, colored;
};


int main() {
	int n, e;
	while (cin >> n >> e) {
		std::vector<Node> nodes(n);
		while (e--) {
			int from, to;
			cin >> from >> to;

			// Add edges (undirected graph!)
			nodes[from].nb.push_back(&nodes[to]);
			nodes[to].nb.push_back(&nodes[from]);
		}

		// Do a BFS and color!
		list <Node*> queue;
		queue.push_back(&nodes[0]);

		bool color_ok = true;
		while (queue.size()) {
			Node * curr = queue.back();
			queue.pop_back();

			curr->visited = true;

			for (auto node: curr->nb) {
				if (node->visited and not (curr->colored xor node->colored))
					color_ok = false;
				if (!node->visited) {
					queue.push_back(node);
					node->colored = not curr->colored;
				}
			}
		}

		bool connex = true;
		for (auto node: nodes)
			if (!node.visited)
				connex = false;
		
		if (!connex)
			cout << "NC" << endl;
		else if (color_ok)
			cout << "yes" << endl;
		else
			cout << "no" << endl;

	}
}


