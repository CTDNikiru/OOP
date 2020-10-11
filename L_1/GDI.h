#pragma once

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#pragma warning (disable : 4996)

class GDInterface {

public:

	struct GDIRect {
		POINT coords[4];
		COLORREF color;
		COLORREF BrushColor;
		int BrushMode;
	};

	static GDIRect* getCoordsFromFile(string filename, int startLine) {
		try {
			GDIRect* mass = new GDIRect;
			string s;
			int n = 0;
			int counter = 0;
			HWND hWnd = GetConsoleWindow();
			RECT rc;
			GetClientRect(hWnd, &rc);
			ifstream file(filename);

			if (!file.is_open())
				throw "Missing Input.txt";

			for (int i = 0; i < startLine; i++)
				getline(file, s); //пропуск лайнов

			file >> mass->BrushMode; //Запись в структуру мода кисти

			int R; int G; int B;
			file >> R; file >> G; file >> B;
			mass->color = RGB(R, G, B); //запись цвета ручки
			file >> R; file >> G; file >> B;
			mass->BrushColor = RGB(R, G, B);

			for (int i = 0; i < 4; i++) {
				file >> mass->coords[i].x;

				if (mass->coords[i].x < 0 || mass->coords[i].x > rc.right)
					throw "Incorrect dot input";

				file >> mass->coords[i].y;

				if (mass->coords[i].y < 0 || mass->coords[i].y > rc.bottom)
					throw "Incorrect dot input";
			}

			if (mass->coords[0].y != mass->coords[1].y || mass->coords[2].y != mass->coords[3].y) {
				throw "Incorrect dots";
			}

			if (mass->coords[0].x + mass->coords[1].x != mass->coords[2].x + mass->coords[3].x) {
				throw "Incorrect dots";
			}

			if (mass->coords[0].x > mass->coords[1].x || mass->coords[3].x > mass->coords[2].x) {
				throw "Incorrect dots";
			}

			file.close();
			return mass;
		}
		catch (const char* exeption) {
			cout << exeption;
			exit(0);
		};
	}

	static void DrawSimpleRectangle(GDIRect* MainStruct) {

		HDC hdc = GetDC(GetConsoleWindow());
		SetBkColor(hdc, RGB(0, 0, 0));

		HPEN CreatedPen = CreatePen(MainStruct->BrushMode, 5, MainStruct->color);
		HPEN holdPen = SelectPen(hdc, CreatedPen);

		HBRUSH CreatedBrush = CreateSolidBrush(GetBkColor(hdc));
		HBRUSH holdBrish = SelectBrush(hdc, CreatedBrush);

		do {

			Polygon(hdc, MainStruct->coords, 4);

		} while (getch() != 27);

		SelectPen(hdc, holdPen);

		DeletePen(holdPen);

		ReleaseDC(GetConsoleWindow(), hdc);

	}

	static void DrawPaintedRectangle(GDIRect* MainStruct)

	{
		HDC hdc = GetDC(GetConsoleWindow());

		SetBkColor(hdc, RGB(0, 0, 0));

		HPEN CreatedPen = CreatePen(MainStruct->BrushMode, 5, MainStruct->color);

		HPEN holdPen = SelectPen(hdc, CreatedPen);

		HBRUSH CreatedBrush = CreateSolidBrush(MainStruct->BrushColor);

		HBRUSH holdBrush = SelectBrush(hdc, CreatedBrush);

		do {

			Polygon(hdc, MainStruct->coords, 4);

		} while (getch() != 27);

		SelectPen(hdc, holdPen);

		SelectBrush(hdc, holdBrush);

		DeletePen(CreatedPen);

		DeleteBrush(CreatedBrush);

		ReleaseDC(GetConsoleWindow(), hdc);
	}

	static void DrawRegInReg(GDIRect* MainStruct, GDIRect* ExtraStruct) {

		HDC hdc = GetDC(GetConsoleWindow());

		//SetBkColor(hdc, MainStruct->BrushColor);

		HPEN hRedPen = CreatePen(MainStruct->BrushMode, 5, MainStruct->color);

		HPEN hOldPen = SelectPen(hdc, hRedPen);

		HBRUSH hGreenBrush = CreateSolidBrush(MainStruct->BrushColor);

		do {

			Polygon(hdc, MainStruct->coords, 4);

			HBRUSH hOldBrush = SelectBrush(hdc, hGreenBrush);

			Polygon(hdc, ExtraStruct->coords, 4);

		} while (getch() != 27);

		SelectPen(hdc, hOldPen);

		DeletePen(hRedPen);

		ReleaseDC(GetConsoleWindow(), hdc);

	}

};