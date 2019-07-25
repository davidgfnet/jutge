
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

// Up 
long long table[32][32][3];

unsigned long long numcomb(int z, int u, int res) {
	// Base cases
	if (z < 0 || u < 0)
		return 0;

	if (z == 0 && u == 0)
		return 1;

	// For base cases just bruteforce them!
	int n = z+u;
	if (n <= 3) {
		int val = 0;
		for (int i = 0; i < ((n >= 3) ? 2 : 1); i++) {
			for (int j = 0; j < ((n >= 2) ? 2 : 1); j++) {
				for (int k = 0; k < 2; k++) {
					int num = (i << 2) | (j << 1) | k;
					if (i + j + k == u &&
						num % 3 == res) {

						val++;
					}
				}
			}
		}
		return val;
	}


	// We covered n <= 3 already
	if (table[z][u][res] >= 0)
		return table[z][u][res];

	// If we remove a zero, just pass res, since the res won't change!
	// If we remove a one, residue changes! Calculate n and follow rule
	int cres = (n % 2 == 0) ? 2 : 1;
	int tres = (res - cres + 3) % 3; // Target res for removing a one!

	// In any other case!
	unsigned long long val = 0;
	// Remove a zero and a one
	val += numcomb(z-1, u, res);
	val += numcomb(z, u-1, tres);

	table[z][u][res] = val;

	return val;
}

unsigned long long numcomb(int z, int u) {
	// Multiples of 3 (residue == 0)
	return numcomb(z, u, 0);
}

int main() {
	// do not contain two consecutive zeros nor three consecutive ones.

	memset(table, ~0, sizeof(table));

	int z, u;
	while (cin >> z >> u)
		cout << numcomb(z, u) << endl;

	return 0;
}

