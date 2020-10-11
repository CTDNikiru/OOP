#include "GDI.h"

int main() {
	POINT pointMass[4];
	POINT pointMass2[4];
	GDInterface::DrawSimpleRectangle(GDInterface::getCoordsFromFile("input.txt", 0));
	GDInterface::DrawPaintedRectangle(GDInterface::getCoordsFromFile("input.txt", 0));
	GDInterface::DrawRegInReg(GDInterface::getCoordsFromFile("input.txt", 0), GDInterface::getCoordsFromFile("input.txt", 7));
}