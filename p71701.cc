
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <string.h>

using namespace std;

const char table[3] = { '.', '.', 'K' };

void nreis(char * matrix, int n, int r, int ipos) {
	if (r == 0) {
		// Print setup
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int pos = i * n + j;
				char c = table[matrix[pos]];
				cout << c;
			}
			cout << endl;
		}
		cout << "----------" << endl;
	}
	else {
		// Look for all valid spots!
		if (ipos >= n*n) return;

		int i = ipos/n;
		int j = ipos%n;

		int pos = i * n + j;
		if (!matrix[pos]) {
			// i,j is a valid pos, mark it (and surrounding spots)
			char tmp[3][3];
			for (int m = -1; m <= 1; m++) {
				for (int l = -1; l <= 1; l++) {
					int row = (i+m);
					int col = (j+l);
					if (row < 0 || row >= n) continue;
					if (col < 0 || col >= n) continue;
					int pos2 = row * n + col;
					tmp[m+1][l+1] = matrix[pos2];
					matrix[pos2] = (m == 0 && l == 0) ? 2 : 1;
				}
			}

			// Just updated matrix, now recusrively call!
			nreis(matrix, n, r-1, pos+1);

			// Undo the matrix edit!
			for (int m = -1; m <= 1; m++) {
				for (int l = -1; l <= 1; l++) {
					int row = (i+m);
					int col = (j+l);
					if (row < 0 || row >= n) continue;
					if (col < 0 || col >= n) continue;
					int pos2 = row * n + col;
					matrix[pos2] = tmp[m+1][l+1];
				}
			}
		}

		// Do not update the matrix, just assume no king in this position!
		nreis(matrix, n, r, pos+1);


	}
}

int main() {
	int n, r;
	cin >> n >> r;

	char matrix[n][n];
	memset(matrix, 0, sizeof(matrix));

	nreis((char*)matrix, n, r, 0);
}

