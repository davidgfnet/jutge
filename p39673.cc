
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	std::vector <int> heap;
	heap.reserve(100000);

	int n;
	while (cin >> n)
		heap.push_back(n);

	std::sort(heap.begin(), heap.end());

	for (unsigned i = 0; i < heap.size(); i += 2) {
		if (i == heap.size()-1 || heap[i] != heap[i+1]) {
			cout << heap[i] << endl;
			break;
		}
	}
}

