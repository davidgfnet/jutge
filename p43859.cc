
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Node {
public:
	Node() : visited(false), cost(~0) {}

	std::vector<Node*> nb;
	std::vector<int> edges;
	bool visited;
	unsigned cost;
};

int main() {
	int n, e;
	while (cin >> n >> e) {
		std::vector<Node> nodes(n);
		while (e--) {
			int from, to, val;
			cin >> from >> to >> val;
			nodes[from].nb.push_back(&nodes[to]);
			nodes[from].edges.push_back(val);
		}

		// Read path from, to
		int from, to;
		cin >> from >> to;

		nodes[from].cost = 0;
		std::set < std::pair<int, Node*> > queue;
		queue.emplace(make_pair(0, &nodes[from]));

		while (queue.size()) {
			// Extract next candidate
			Node * curr = queue.begin()->second;
			curr->visited = true;
			queue.erase(make_pair(curr->cost, curr));

			// Visit neighbours
			for (unsigned i = 0; i < curr->nb.size(); i++) {
				if (!curr->nb[i]->visited) {
					// Recalculate the cost
					unsigned newcost = curr->cost + curr->edges[i];
					if (newcost < curr->nb[i]->cost) {
						// Remove and readd node (2 log n)
						queue.erase(make_pair(curr->nb[i]->cost, curr->nb[i]));
						curr->nb[i]->cost = newcost;
						queue.emplace(make_pair(curr->nb[i]->cost, curr->nb[i]));
					} 
				}
			}
		}

		// Just lookup "to" cost
		if (nodes[to].visited)
			cout << nodes[to].cost << endl;
		else
			cout << "no path from " << from << " to " << to << endl;
	}
}

