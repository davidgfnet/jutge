
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Node {
public:
	Node() : visited(false), cost(~0), steps(~0) {}

	std::vector<Node*> nb;
	std::vector<int> edges;
	bool visited;
	unsigned cost, steps;
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
		nodes[from].steps = 0;
		std::set < std::pair< std::pair<int, int>, Node*> > queue;
		queue.emplace(make_pair(make_pair(0,0), &nodes[from]));

		while (queue.size()) {
			// Extract next candidate
			Node * curr = queue.begin()->second;
			curr->visited = true;
			queue.erase(make_pair(make_pair(curr->cost, curr->steps), curr));

			// Visit neighbours
			for (unsigned i = 0; i < curr->nb.size(); i++) {
				if (!curr->nb[i]->visited) {
					// Recalculate the cost
					unsigned newcost = curr->cost + curr->edges[i];
					unsigned newsteps = curr->steps + 1;
					if (newcost < curr->nb[i]->cost or
						(newcost == curr->nb[i]->cost and newsteps < curr->nb[i]->steps)) {

						// Remove and readd node (2 log n)
						queue.erase(make_pair(make_pair(curr->nb[i]->cost, curr->nb[i]->steps), curr->nb[i]));
						curr->nb[i]->cost = newcost;
						curr->nb[i]->steps = newsteps;
						queue.emplace(make_pair(make_pair(curr->nb[i]->cost, curr->nb[i]->steps), curr->nb[i]));
					}
				}
			}
		}

		// Just lookup "to" cost
		if (nodes[to].visited)
			cout << "cost " << nodes[to].cost << ", " << nodes[to].steps << " step(s)" << endl;
		else
			cout << "no path from " << from << " to " << to << endl;
	}
}

