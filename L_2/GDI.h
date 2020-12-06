#pragma once

#pragma region includesNDwarnings
#pragma warning (disable : 4996)

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>
#pragma endregion

using namespace std;

class GDInterface {
public:

#pragma region Methods

	//получение данных из файла
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

		mass.setPenWidht(bufer); //толщина кисти

		file >> R; file >> G; file >> B;

		mass.setPenColor(RGB(R, G, B)); //запись цвета ручки

		file >> R; file >> G; file >> B;

		mass.setBrushColor(RGB(R, G, B)); //цвет парала

		for (int i = 0; i < 4; i++) {
			file >> pointMass[i].x;
			file >> pointMass[i].y;
		}

		mass.setCoords(pointMass);

		file.close();
		return mass;
	}

	//проверка структуры
	int structureCheck(POINT* coords) {
		if ((coords[1].y) - (coords[0].y) != (coords[3].y) - (coords[2].y)) {
			return -2;
				//"not parallelogram. dot 'y' error";
		}

		if (coords[1].x - coords[0].x != coords[2].x - coords[3].x) {
			
				//"not parallelogram. dot 'x' error";
			return -1;
		}
		return 0;
	}

	//mode: 0 - simple, 1 - painted
	int drawParal(int mode) {
		HDC hdc = GetDC(GetConsoleWindow());

		HPEN myPen = CreatePen(penStyle_, penWidht_, penColor_);
		HBRUSH myBrush = CreateSolidBrush(brushColor_);

		HPEN holdPen;
		HBRUSH holdBrush;
		if (structureCheck(coords_) != 0) {
			return structureCheck(coords_);
		}
		switch (mode) {
		case 0:
			holdPen = SelectPen(hdc, myPen);
			do {
				Polygon(hdc, coords_, 4);
			} while (getch() != 27);

			ReleaseDC(GetConsoleWindow(), hdc);
			break;

		case 1:
			holdPen = SelectPen(hdc, myPen);
			holdBrush = SelectBrush(hdc, myBrush);
			do {
				Polygon(hdc, coords_, 4);
			} while (getch() != 27);

			ReleaseDC(GetConsoleWindow(), hdc);
			break;

			DeletePen(SelectPen(hdc, myPen));
			DeleteBrush(SelectBrush(hdc, myBrush));
		}
		return 0;
	}

	//mode: Paral in Paral
	int drawParal(GDInterface paral2) {
		HDC hdc = GetDC(GetConsoleWindow());

		HPEN myPen = CreatePen(penStyle_, penWidht_, penColor_);
		HPEN myPen2 = CreatePen(paral2.getPenStyle(), paral2.getPenWidht(), paral2.getPenColor());

		HBRUSH myBrush = CreateSolidBrush(brushColor_);
		HBRUSH myBrush2 = CreateSolidBrush(RGB(0, 0, 0));

		HPEN holdPen;
		HBRUSH holdBrush;
		if (structureCheck(coords_) != 0) {
			return structureCheck(coords_);
		}
		if (structureCheck(paral2.getCoords()) != 0) {
			return structureCheck(paral2.getCoords());
		}
			
		do {
			holdPen = SelectPen(hdc, myPen);
			holdBrush = SelectBrush(hdc, myBrush);
			Polygon(hdc, coords_, 4);
			holdPen = SelectPen(hdc, myPen2);
			holdBrush = SelectBrush(hdc, myBrush2);
			Polygon(hdc, paral2.getCoords(), 4);
		} while (getch() != 27);

		ReleaseDC(GetConsoleWindow(), hdc);

		DeletePen(SelectPen(hdc, myPen));
		DeletePen(SelectPen(hdc, myPen2));
		DeleteBrush(SelectBrush(hdc, myBrush));
		DeleteBrush(SelectBrush(hdc, myBrush2));
		return 0;
	}

	//0 - left, 1 - right, 2 - up, 3- down
	void changeCoords(int direction, int value) {
		switch (direction) {
		case 0:
			for (int i = 0; i < 4; i++) {
				coords_[i].x -= value;
			}
			break;
		case 1:
			for (int i = 0; i < 4; i++) {
				coords_[i].x += value;
			}
			break;
		case 2:
			for (int i = 0; i < 4; i++) {
				coords_[i].y += value;
			}
			break;
		case 3:
			for (int i = 0; i < 4; i++) {
				coords_[i].y -= value;
			}
			break;
		}
	}

	//вывод класса в файл
	void fileOut() {
		ofstream out("out.txt");

		//мод кисти
		//толщина ручки
		//цвет ручки
		//цвет кисти
		//координаты в формате x, y
		
		out << penStyle_ << endl;
		out << penWidht_ << endl;
		out << (int)GetRValue(penColor_) << " " << (int)GetGValue(penColor_) << " " << (int)GetBValue(penColor_) << endl;
		out << (int)GetRValue(brushColor_) << " " << (int)GetGValue(brushColor_) << " " << (int)GetBValue(brushColor_) << endl;

		for (int i = 0; i < 4; i++) {
			out << coords_[i].x << " " << coords_[i].y << endl;
		}
	}

#pragma endregion

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

#pragma region Private_params
private:
	POINT* coords_;
	COLORREF penColor_;
	COLORREF brushColor_;

	int penStyle_;
	int penWidht_;
#pragma endregion

};




