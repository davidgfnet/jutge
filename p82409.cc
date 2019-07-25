
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <string.h>

using namespace std;

unsigned long long parent(int n, int d) {
	if (d < 0)
		return 0;
	if (d > n)
		return 0;
	if (n == 0 && d == 0)
		return 1;
	return parent(n-1, d+1) + parent(n-1, d-1);
}

unsigned long long table[200][200];

void filltable() {
	memset(table, 0, sizeof(table));
	table[0][0] = 1;

	for (int i = 1; i < 200; i++) {
		for (int j = 199; j >= 0; j--) {
			table[i][j] += (j+1 < 200) ? table[i-1][j+1] : 0;
			table[i][j] += (j-1 >=  0) ? table[i-1][j-1] : 0;
		}
	}
}

int main() {
	filltable();

	int n;
	while (cin >> n) {
		cout << table[n][0] << endl;
	}
}

