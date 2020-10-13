#include "GDI.h"

int main() {
	POINT pointMass[4];
	POINT pointMass2[4];
	DrawSimpleRectangle(StructureCheck(getCoordsFromFile("input.txt", 0)));
	DrawPaintedRectangle(StructureCheck(getCoordsFromFile("input.txt", 0)));
	DrawRegInReg(StructureCheck(getCoordsFromFile("input.txt", 0)), StructureCheck(getCoordsFromFile("input.txt", 7)));
}