
#include <iostream>
#include <algorithm>

using namespace std;

// (n over 2) -> n! / (2! * (n-2)! -> n(n+1) / 2

int maino2() {
	int valor, ndiam;
	while (cin >> valor >> ndiam) {
		if (valor == 0)
			return 0;

		int dval[ndiam];
		for (int i = 0; i < ndiam; i++) {
			cin >> dval[i];
		}

		bool found = false;
		for (int i = 0; i < ndiam - 1; i++) {
			for (int j = i + 1; j < ndiam; j++) {
				int value = dval[i] + dval[j];
				if (value == valor) {
					found = true;
					break;
				}
			}
		}

		if (found)
			cout << "married" << endl;
		else
			cout << "single" << endl;
	}
}

// nlogn solution: sort the list
// We sort the list, then for each number we do a dicotomical search for the other number

bool search(int * vec, int target, int max) {
	if (max == 1)
		return *vec == target;

	int mid = max/2;
	if (target < vec[mid])
		return search(vec, target, mid);

	return search(&vec[mid], target, max-mid);
}

int main() {
	int valor, ndiam;
	while (cin >> valor >> ndiam) {
		if (valor == 0)
			return 0;

		int dval[ndiam];
		for (int i = 0; i < ndiam; i++) {
			cin >> dval[i];
		}

		// Sort the list
		std::sort(&dval[0], &dval[ndiam]);

		bool found = false;
		for (int i = 0; i < ndiam - 1; i++) {
			// Now we are looking for number in i+1..end
			int target = valor - dval[i];
			found = search(&dval[i+1], target, ndiam-(i+1));
			if (found)
				break;
		}

		if (found)
			cout << "married" << endl;
		else
			cout << "single" << endl;
	}
}





