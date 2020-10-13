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

	struct GDIRect {
		POINT coords[4];
		COLORREF color;
		COLORREF BrushColor;
		int BrushMode;
	};

	static GDIRect* getCoordsFromFile(string filename, int startLine) {

			GDIRect* mass = new GDIRect;
			string s;
			int R; int G; int B;

			HWND hWnd = GetConsoleWindow();
			RECT rc;

			GetClientRect(hWnd, &rc);
			ifstream file(filename);

			for (int i = 0; i < startLine; i++)
				getline(file, s); //пропуск лайнов

			file >> mass->BrushMode; //Запись в структуру мода кисти

			file >> R; file >> G; file >> B;
			mass->color = RGB(R, G, B); //запись цвета ручки

			file >> R; file >> G; file >> B;
			mass->BrushColor = RGB(R, G, B);

			for (int i = 0; i < 4; i++) {

				file >> mass->coords[i].x;
				file >> mass->coords[i].y;

			}

			file.close();
			return mass;
	}

	static GDIRect* StructureCheck(GDIRect* MainStruct) {
		try {
			if ((MainStruct->coords[1].y) - (MainStruct->coords[0].y) != (MainStruct->coords[3].y) - (MainStruct->coords[2].y)) {
				throw "not parallelogram. dot 'y' error";
			}

			if (MainStruct->coords[1].x - MainStruct->coords[0].x != MainStruct->coords[2].x - MainStruct->coords[3].x) {
				throw "not parallelogram. dot 'x' error";
			}
		}
		catch (const char* exeption) {
			cout << "Error: " << exeption;
			exit(0);
		};

		return MainStruct;
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
		DeletePen(CreatedPen);

		SelectBrush(hdc, holdBrush);
		DeleteBrush(CreatedBrush);

		ReleaseDC(GetConsoleWindow(), hdc);
	}

	static void DrawRegInReg(GDIRect* MainStruct, GDIRect* ExtraStruct) {

		HDC hdc = GetDC(GetConsoleWindow());

		//SetBkColor(hdc, MainStruct->BrushColor);

		HPEN hRedPen = CreatePen(MainStruct->BrushMode, 5, MainStruct->color);

		HPEN hOldPen = SelectPen(hdc, hRedPen);

		HBRUSH hGreenBrush = CreateSolidBrush(MainStruct->BrushColor);

		HBRUSH CreatedBrush = CreateSolidBrush(RGB(0,0,0));

		HBRUSH holdBrush_1;
		HBRUSH holdBrush_2;

		do {
			holdBrush_1 = SelectBrush(hdc, hGreenBrush);

			Polygon(hdc, MainStruct->coords, 4);

			holdBrush_2 = SelectBrush(hdc, CreatedBrush);

			Polygon(hdc, ExtraStruct->coords, 4);

		} while (getch() != 27);

		SelectPen(hdc, hOldPen);
		DeletePen(hRedPen);

		ReleaseDC(GetConsoleWindow(), hdc);
	}