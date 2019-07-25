
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

map<char, int> dirmap = { {'N', 0}, {'E', 1}, {'S', 2}, {'W', 3} };

struct t_qe {
	unsigned x, y, d;
};

int main() {
	unsigned h, w;
	while (cin >> h >> w) {
		unsigned startx, starty;
		unsigned startd;

		vector <string> table(h);
		for (unsigned i = 0; i < h; i++)
			for (unsigned j = 0; j < w; j++) {
				char c;
				cin >> c;
				if (dirmap.find(c) != dirmap.end()) {
					startx = j; starty = i;
					startd = dirmap[c];
				}
				table[i] += c;
			}

		vector <bool> visited(w*h*4, false);

		list < t_qe > bfsq;

		bfsq.push_back({startx, starty, startd});

		while (bfsq.size()) {
			auto curr = *bfsq.begin();
			bfsq.pop_front();

			// Control already visited nodes
			if (visited[(curr.y * w + curr.x)*4 + curr.d])
				continue;
			visited[(curr.y * w + curr.x)*4 + curr.d] = true;

			// Expand nods from here by checking bounds
			const int alldir[4][2] = { { 0, -1}, { 1, 0}, { 0, 1}, { -1, 0} };

			unsigned x = curr.x + alldir[curr.d][0];
			unsigned y = curr.y + alldir[curr.d][1];
			if (table[y][x] == 'X') { // Bounce!
				for (unsigned i = 0; i < 4; i++) {
					unsigned nx = curr.x + alldir[i][0];
					unsigned ny = curr.y + alldir[i][1];

					if (table[ny][nx] != 'X')
						bfsq.push_back({nx, ny, i});
				}
			}
			else {
				bfsq.push_back({x, y, curr.d}); // Keep same direction bro!
			}
			table[curr.y][curr.x] = ' ';
		}

		for (unsigned i = 0; i < h; i++)
			cout << table[i] << endl;
		cout << endl;
	}	
}


