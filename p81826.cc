
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>

using namespace std;

int numcomb(int n, int cat) {
	switch (n) {
	case 0: return 1;
	case 1: return 2;
	case 2: return 3;
	case 3: return (cat < 0) ? 4 : 1;
	};

	// In any other case!
	switch (cat) {
	case -1:
		return numcomb(n, 2) + numcomb(n, 3) + numcomb(n, 5) + numcomb(n, 6);
	case 2: // 010
		return numcomb(n-1, 5);
	case 3: // 011
		return numcomb(n-1, 6);
	case 5: // 101
		return numcomb(n-1, 2) + numcomb(n-1, 3);
	case 6: // 110
		return numcomb(n-1, 5);
	};

	exit(-1);
}

int numcomb(int n) {
	return numcomb(n, -1);
}

unsigned long long table[4][151];

void filltable() {
	for (int i = 0; i < 4; i++) {
		table[i][0] = 1;
		table[i][1] = 2;
		table[i][2] = 3;
		table[i][3] = 1;
	}

	for (int i = 4; i < 151; i++) {
		table[0][i] = table[2][i-1];
		table[1][i] = table[3][i-1];
		table[2][i] = table[0][i-1] + table[1][i-1];
		table[3][i] = table[2][i-1];
	}

}

unsigned long long fastnc(int n) {
	if (n < 3)
		return table[0][n];
	return table[0][n] + table[1][n] + table[2][n] + table[3][n];
}

int main() {
	// do not contain two consecutive zeros nor three consecutive ones.

	// Cathegories (8)
	// 0 000XXXXX  Forbidden
	// 1 001XXXXX  Forbidden
	// 2 010XXXXX  OK, Starts with 0
	// 3 011XXXXX  OK, Starts with 0
	// 4 100XXXXX  Forbidden
	// 5 101XXXXX  OK, Starts with 1
	// 6 110XXXXX  OK, Starts with 11
	// 7 111XXXXX  Forbidden

	filltable();

	int n;
	while (cin >> n)
		cout << fastnc(n) << endl;

	return 0;
}

