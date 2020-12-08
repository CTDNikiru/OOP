#include "GDI.h"
#include <iostream>
#include "savingStruct.h"

using namespace std;

int main() {
	GDInterface paral1;
	GDInterface paral2;

	const int standartParalStdCount = 7;

	paral1 = paral1.getCoordsFromFile("input.txt", 0);
	paral2 = paral2.getCoordsFromFile("input.txt", 1+standartParalStdCount);

	SavingClass* sw = new SavingClass(paral1, 1);

	sw->append(paral2, 2);
	
	cout << sw->getAll().size() << "\n";
	sw->Del(1);
	cout << sw->getAll().size() << "\n";
}