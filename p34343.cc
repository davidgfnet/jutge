
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

//////////////////////
//     0   1   2   3  z
//  0  1   1   0   0
//  1  1   2   1
//  2  1   3
//  3  0
//  u

int catmap(int c) {
	switch (c) {
	case -1: return 0;
	case  2: return 1;
	case  3: return 2;
	case  5: return 3;
	case  6: return 4;
	};
}

long long table[100][100][5];

unsigned long long numcomb(int z, int u, int cat) {
	// Base cases
	if (z < 0 || u < 0)
		return 0;

	// empty, 0 1 01 10
	if (z < 2 and u < 2)
		return max(1, u+z);

	// Only ones or zeros
	if (z == 0)
		return (u < 3) ? 1 : 0;
	if (u == 0)
		return (z < 2) ? 1 : 0;

	// Corner boring cases
	if (z == 1 && u == 2) // 110 011 101
		return (cat  < 0) ? 3 :
		       (cat == 2) ? 0 :
		       (cat == 3) ? 1 :
		       (cat == 5) ? 1 :
		       (cat == 6) ? 1 : 0;
	if (z == 2 && u == 1) // 010
		return (cat == 2 || cat < 0) ? 1 : 0;

	// We covered n <= 3 already

	if (table[z][u][catmap(cat)] >= 0)
		return table[z][u][catmap(cat)];

	// In any other case!
	unsigned long long val = 0;
	switch (cat) {
	case -1:
		if (numcomb(z-2, u-1, -1) > 0)
			val += numcomb(z, u, 2);
		if (numcomb(z-1, u-2, -1) > 0)
			val += numcomb(z, u, 3) + numcomb(z, u, 5) + numcomb(z, u, 6);
		break;
	case 2: // 010
		if (numcomb(z-2, u-1, -1) > 0)
			val = numcomb(z-1, u, 5);
		break;
	case 3: // 011
		if (numcomb(z-1, u-2, -1) > 0)
			val = numcomb(z-1, u, 6);
		break;
	case 5: // 101
		if (numcomb(z-1, u-2, -1) > 0)
			val = numcomb(z, u-1, 2) + numcomb(z, u-1, 3);
		break;
	case 6: // 110
		if (numcomb(z-1, u-2, -1) > 0)
			val = numcomb(z, u-1, 5);
		break;
	};

	table[z][u][catmap(cat)] = val;

	return val;
}

unsigned long long numcomb(int z, int u) {
	return numcomb(z, u, -1);
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

	memset(table, ~0, sizeof(table));

	int z, u;
	while (cin >> z >> u)
		cout << numcomb(z, u) << endl;

	return 0;
}

