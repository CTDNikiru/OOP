#pragma once
#pragma warning (disable : 4996)

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class GDInterface {
public:

#pragma region set_Methods
	void setCoords(POINT coords[4]) {
		coords_ = coords;
	}

	void setPenColor(COLORREF penColor) {
		penColor_ = penColor;
	}

	void setBrushColor(COLORREF brushColor) {
		brushColor_ = brushColor;
	}

	void setPenStyle(int penStyle) {
		penStyle_ = penStyle;
	}

	void setPenWidht(int penWidht) {
		penWidht_ = penWidht;
	}
#pragma endregion

#pragma region get_Methods
	POINT* getCoords() {
		return coords_;
	}

	COLORREF getPenColor() {
		return penColor_;
	}

	COLORREF getBrushColor() {
		return brushColor_;
	}


	int getPenStyle() {
		return penStyle_;
	}

	int getPenWidht() {
		return penWidht_;
	}
#pragma endregion

private:
	POINT* coords_;
	COLORREF penColor_;
	COLORREF brushColor_;

	int penStyle_;
	int penWidht_;
};


GDInterface getCoordsFromFile(string filename, int startLine) {

	GDInterface mass;
	string s;
	int R; int G; int B;
	int bufer;
	POINT* pointMass = new POINT[4];

	ifstream file(filename);

	for (int i = 0; i < startLine; i++)
		getline(file, s); //пропуск лайнов

	file >> bufer; //Запись в структуру мода кисти

	mass.setPenStyle(bufer);

	file >> bufer;

	mass.setPenWidht(bufer);

	file >> R; file >> G; file >> B;

	mass.setPenColor(RGB(R, G, B)); //запись цвета ручки

	file >> R; file >> G; file >> B;

	mass.setBrushColor(RGB(R, G, B));

	for (int i = 0; i < 4; i++) {
		file >> pointMass[i].x;
		file >> pointMass[i].y;
	}

	mass.setCoords(pointMass);

	file.close();
	return mass;
}


void StructureCheck(GDInterface paral) {
	try {
		if ((paral.getCoords()[1].y) - (paral.getCoords()[0].y) != (paral.getCoords()[3].y) - (paral.getCoords()[2].y)) {
			throw "not parallelogram. dot 'y' error";
		}

		if (paral.getCoords()[1].x - paral.getCoords()[0].x != paral.getCoords()[2].x - paral.getCoords()[3].x) {
			throw "not parallelogram. dot 'x' error";
		}
	}
	catch (const char* exeption) {
		cout << "Error: " << exeption;
		exit(0);
	};
}

//mode: 0 - simple, 1 - painted, 2 - Paral in Paral
void drawParal(GDInterface paral, GDInterface paral2, int mode) {
	HDC hdc = GetDC(GetConsoleWindow());

	HPEN myPen = CreatePen(paral.getPenStyle(), paral.getPenWidht(), paral.getPenColor());
	HPEN myPen2 = CreatePen(paral2.getPenStyle(), paral2.getPenWidht(), paral2.getPenColor());

	HBRUSH myBrush = CreateSolidBrush(paral.getBrushColor());
	HBRUSH myBrush2 = CreateSolidBrush(RGB(0,0,0));

	HPEN holdPen;
	HBRUSH holdBrush;

	switch (mode) {
	case 0:
		StructureCheck(paral);
		holdPen = SelectPen(hdc, myPen);
		do {
			Polygon(hdc, paral.getCoords(), 4);
		} while (getch() != 27);

		ReleaseDC(GetConsoleWindow(), hdc);
		break;

	case 1:
		StructureCheck(paral);
		holdPen = SelectPen(hdc, myPen);
		holdBrush = SelectBrush(hdc, myBrush);
		do {
			Polygon(hdc, paral.getCoords(), 4);
		} while (getch() != 27);

		ReleaseDC(GetConsoleWindow(), hdc);
		break;

	case 2:
		StructureCheck(paral2);
		do {
			holdPen = SelectPen(hdc, myPen);
			holdBrush = SelectBrush(hdc, myBrush);
			Polygon(hdc, paral.getCoords(), 4);
			holdPen = SelectPen(hdc, myPen2);
			holdBrush = SelectBrush(hdc, myBrush2);
			Polygon(hdc, paral2.getCoords(), 4);
		} while (getch() != 27);

		ReleaseDC(GetConsoleWindow(), hdc);
		break;
	}

	DeletePen(SelectPen(hdc, myPen));
	DeletePen(SelectPen(hdc, myPen2));
	DeleteBrush(SelectBrush(hdc, myBrush));
	DeleteBrush(SelectBrush(hdc, myBrush2));
}

