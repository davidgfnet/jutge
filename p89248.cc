
#include <string.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <map>

using namespace std;

void f(char * arr, int pos, int mpos, int cmap) {
	if (pos == mpos)
		cout << std::string(arr, mpos) << endl;
	else {
		for (int i = 0; i < cmap; i++) {
			char c = 'a' + i;
			if (pos == 1 && arr[pos-1] == c)
				continue;
			if (pos >= 2 && (arr[pos-1] == c || arr[pos-2] == c))
				continue;

			arr[pos] = c;
			f(arr, pos+1, mpos, cmap);
		}
	}
}

int main() {
	int n, x;
	cin >> n >> x;

	char arr[n];
	f(arr, 0, n, x);
}


