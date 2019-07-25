
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <string.h>

using namespace std;

int main() {
	int n, m;
	while (cin >> n >> m) {
		char mapa[n][m];

		// Girem el mapa aixi la pos inicial es 0,0
		// Hem de anar sempre cap avall a la dreta i a mes sortir del mapa
		// vol dir acbaar a una posicio >=n o >=m
		for (int i = n-1; i >= 0; i--) {
			for (int j = m-1; j >= 0; j--) {
				cin >> mapa[i][j];
			}
		}

		unsigned int cost[n+2][m+2];
		memset(cost, 0, sizeof(cost));

		cost[0][0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (mapa[i][j] == '*')
					cost[i][j] = 0;
				else if (mapa[i][j] == 'R') {
					cost[i][j+1] += cost[i][j];
					cost[i+1][j] += cost[i][j];
					cost[i+1][j+1] += cost[i][j];
				}
				else if (mapa[i][j] == 'C') {
					cost[i+2][j+1] += cost[i][j];
					cost[i+1][j+2] += cost[i][j];
				}
			}
		}

		// Total num ways is:
		unsigned int total = 0;
		for (int i = 0; i < n+2; i++)
			for (int j = m; j < m+2; j++)
				total += cost[i][j];
		for (int i = n; i < n+2; i++)
			for (int j = 0; j < m; j++)
				total += cost[i][j];

		cout << total << endl;
	}
}

