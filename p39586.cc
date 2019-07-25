
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

using namespace std;

class Node {
public:
	Node(int id) : id(id), visited(false), cost(~0) {}

	int id;
	vector<Node*> nb;
	vector<int> edges;
	bool visited;
	unsigned cost;
	list <int> back_paths;
};

unsigned numWays (vector<int> & ways_table, const vector<Node> & nodes, unsigned id, unsigned from) {
	if (from == id)
		return 1;

	unsigned n = 0;
	for (auto node: nodes[id].back_paths) {
		if (ways_table[nodes[node].id] < 0)
			ways_table[nodes[node].id] = numWays(ways_table, nodes, nodes[node].id, from);
		n += ways_table[nodes[node].id];
	}
	return n;
}

int main() {
	int n, e;
	while (cin >> n >> e) {
		vector<Node> nodes;
		nodes.reserve(n);
		for (unsigned i = 0; i < n; i++)
			nodes.push_back(Node(i));

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
		set < pair< int, Node*> > queue;
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
						// The cost decreased, remove any backlinks we might have!
						curr->nb[i]->back_paths.clear();
						curr->nb[i]->back_paths.push_back(curr->id);
						queue.emplace(make_pair(curr->nb[i]->cost, curr->nb[i]));
					}
					else if (newcost == curr->nb[i]->cost)
						// There is a path with the same cost as we have!
						curr->nb[i]->back_paths.push_back(curr->id);
				}
			}
		}

		// Seems we cannot use recursive function, so let's go back to dynamic programming :(
		vector <int> ways_table(n, -1);
		ways_table[from] = 1;
/*
		for (auto node: nodes)
			node.visited = false;
		list<Node*> queued;
		queued.push_back(&nodes[from]);

		// Do a BFS and update way count
		while (queued.size()) {
			Node * curr = queued.front();
			queued.pop_front();

			int total = 0;
			for (auto node: curr->back_paths) {
				total += ways_table[node];
				queued.push_back(&nodes[node]);
			}
			ways_table[curr->id] += total;
			cout << curr->id << " " << total << endl;
		}*/

		int nw = numWays (ways_table, nodes, to, from);

		// Just lookup "to" cost
		if (nodes[to].visited)
			cout << "cost " << nodes[to].cost << ", " << nw << " way(s)" << endl;
		else
			cout << "no path from " << from << " to " << to << endl;
	}
}

