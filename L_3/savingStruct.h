#pragma once
#include "GDI.h"
#include <fstream>

using namespace std;

class SavingClass {
public:
	SavingClass(GDInterface paral, string name) {
		save->forvard = NULL;
		save->paral_ = paral;
		save->name_ = name;
	}

	void append(GDInterface paral, string name) {

		auto head = save;
		save->forvard = new SavingStruct();
		save = save->forvard;
		save->paral_ = paral;
		save->name_ = name;
		save = head;

	}

	GDInterface find(string name) {
		SavingStruct* head = save;
		while (save->forvard != NULL) {
			if (save->name_ != name) {
				save = save->forvard;
			}
			else {
				return save->paral_;
			}
		}
		save = head;
		return GDInterface();
	}

	void saveInFile() {
		ofstream out("AllOut.txt");

		SavingStruct* head = save;
		int counter = 0;
		while (save != nullptr) {
			counter++;
			save = save->forvard;
		}
		save = head;

		out << counter << endl;

		for (int i = 0; i < counter; i++) {
			out << save->paral_.getPenStyle() << endl;
			out << save->paral_.getPenWidht()<< endl;
			out << (int)GetRValue(save->paral_.getPenColor()) << " " << (int)GetGValue(save->paral_.getPenColor()) << " " << (int)GetBValue(save->paral_.getPenColor()) << endl;
			out << (int)GetRValue(save->paral_.getBrushColor()) << " " << (int)GetGValue(save->paral_.getBrushColor()) << " " << (int)GetBValue(save->paral_.getBrushColor()) << endl;

			for (int i = 0; i < 4; i++) {
				out << save->paral_.getCoords()[i].x << " " << save->paral_.getCoords()[i].y << endl;
			}
			save = save->forvard;
		}
	}

private:
	struct SavingStruct
	{
		SavingStruct* forvard = NULL;
		GDInterface paral_;
		string name_;

	}* save = new SavingStruct;
};