
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

class Node {
public:
	Node(unsigned id) : id(id), d(~0), visited(false) {}

	unsigned id;
	unsigned d; // Distance to that node (in # of unpainted nodes)
	bool visited;
	vector <unsigned> child;
};
class NodeSort {
public:
	bool operator()( Node* const & lhs, Node* const & rhs ) const {
		if (lhs->d != rhs->d)
			return lhs->d < rhs->d;
		return lhs->id < rhs->id;
	}
};

int main() {
	unsigned n, x, y;
	while (cin >> n >> x >> y) {
		vector <Node> nodes;
		nodes.reserve(n);
		for (unsigned i = 0; i < n; i++)
			nodes.push_back(Node(i));

		unsigned m;
		cin >> m;
		while (m--) {
			unsigned from, to;
			cin >> from >> to;

			nodes[from].child.push_back(to);
		}

		vector <bool> painted(n);
		cin >> m;
		while (m--) {
			unsigned l;
			cin >> l;

			// All nodes going to "l" are painted!
			painted[l] = true;
		}

		nodes[x].d = painted[x] ? 0 : 1;
		set <Node*, NodeSort> explored;
		explored.insert(&nodes[x]);

		unsigned nump = ~0;
		while (explored.size()) {
			Node* curr = *explored.begin();
			explored.erase(explored.begin());

			if (curr->visited)
				continue;
			curr->visited = true;

			if (curr->id == y) {
				nump = curr->d;
				break;
			}

			// Queue children for this node
			for (unsigned i = 0; i < curr->child.size(); i++) {
				Node * other = &nodes[curr->child[i]];
				// Calculate the new cost
				unsigned newcost = (painted[other->id] ? 0 : 1) + curr->d;

				if (newcost < other->d) {
					if (explored.find(other) != explored.end())
						explored.erase(other);

					other->d = newcost;
					explored.insert(other);
				}
			}
		}

		if (nump != ~0)
			cout << nump << endl;
		else
			cout << "impossible" << endl;
	}
}



