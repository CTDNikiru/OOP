#include "GDI.h"
#include <iostream>

using namespace std;

int main() {
	GDInterface paral1;
	GDInterface paral2;

	paral1 = paral1.getCoordsFromFile("input.txt", 0);
	paral2 = paral1.getCoordsFromFile("input.txt", 9);

	for (int i = 0; i < 3; i++) {
		int ParalWork = paral1.drawParal(i);
		if (ParalWork != 0) {
			if (ParalWork == -1) {
				cout << "not parallelogram. dot 'x' error\n";
			}
			else {
				cout << "not parallelogram. dot 'y' error\n";
			}
			exit(ParalWork);
		}
	}
	paral1.drawParal(paral2);
	paral1.changeCoords(3, 10);
	paral1.fileOut();
}