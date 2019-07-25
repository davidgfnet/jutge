
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <list>

using namespace std;

class Node {
public:
	Node(int id) : id(id), deps(0) {}

	std::vector<Node*> nb;
	unsigned id;
	unsigned deps;
};
class NodeComp {
public:
	bool operator() (Node * const &lhs, Node * const &rhs) const {
		return lhs->id < rhs->id;
	}
};

int main() {
	int n, m;
	while (cin >> n >> m) {
		vector<Node> nodes;
		nodes.reserve(n);
		
		vector <unsigned> solution;
		solution.reserve(n);

		// Priority list of nodes
		set <Node*, NodeComp> pend;

		for (unsigned i = 0; i < n; i++) {
			nodes.push_back(Node(i));
			pend.insert(&nodes[i]);
		}

		while (m--) {
			int from, to;
			cin >> from >> to;
			nodes[from].nb.push_back(&nodes[to]);
			nodes[to].deps++;

			// "to" node cannot be a starting node!
			if (pend.find(&nodes[to]) != pend.end())
				pend.erase(&nodes[to]);
		}

		// Keep iterating!
		while (pend.size()) {
			Node * curr = *pend.begin();
			pend.erase(curr);

			cout << curr->id;

			for (unsigned i = 0; i < curr->nb.size(); i++) {
				// Remove this edge!
				if (--curr->nb[i]->deps == 0)
					pend.insert(curr->nb[i]);
			}

			if (pend.size()) cout << " ";
		}

		cout << endl;
	}
}

