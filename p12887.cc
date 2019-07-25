
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

using namespace std;

class Node {
public:
	Node(int id) : id(id), visited(false), cost(~0) {}

	std::vector<Node*> nb;
	std::vector<int> edges;
	unsigned id;
	bool visited;
	unsigned cost;
};

int main() {
	int n, e;
	while (cin >> n >> e) {
		std::vector<Node> nodes;
		nodes.reserve(n);
		for (unsigned i = 0; i < n; i++)
			nodes.push_back(Node(i));

		while (e--) {
			int from, to, val;
			cin >> from >> to >> val;
			from--; to--;

			// Add edges (undirected graph!)
			nodes[from].nb.push_back(&nodes[to]);
			nodes[from].edges.push_back(val);
			nodes[to].nb.push_back(&nodes[from]);
			nodes[to].edges.push_back(val);
		}

		// Build the minimum spanning tree
		std::set < std::pair<int, Node*> > queue;
		nodes[0].cost = 0;
		queue.emplace(make_pair(0, &nodes[0]));

		unsigned mst_total = 0;
		while (queue.size()) {
			Node * curr = queue.begin()->second;
			queue.erase(make_pair(curr->cost, curr));

			if (!curr->visited) {
				curr->visited = true;

				// Visit neighbours and update their costs accordingly
				int idx = -1;
				unsigned min_cost = ~0;
				for (unsigned i = 0; i < curr->nb.size(); i++) {
					if (!curr->nb[i]->visited) {
						if (curr->nb[i]->cost > curr->edges[i]) {
							queue.erase(make_pair(curr->nb[i]->cost, curr->nb[i]));
							curr->nb[i]->cost = curr->edges[i];
							queue.emplace(make_pair(curr->nb[i]->cost, curr->nb[i]));
						}
					}
					else {
						if (curr->edges[i] < min_cost) {
							min_cost = curr->edges[i];
							idx = i;
						}
					}
				}

				// Also select an edge that doesn't point to a visited guy
				// that has minimum cost
				if (idx >= 0) {
					mst_total += min_cost;
				}
			}
		}

		cout << mst_total << endl;
	}
}

