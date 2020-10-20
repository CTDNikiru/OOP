#include "GDI.h"
#include <iostream>

using namespace std;

int main() {
	GDInterface paral1;
	GDInterface paral2;

	paral1 = getCoordsFromFile("input.txt", 0);
	paral2 = getCoordsFromFile("input.txt", 8);

	for(int i = 0; i<3; i++)
		drawParal(paral1, paral2,i);
}