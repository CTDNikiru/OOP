#pragma once
#include "GDI.h"
#include <fstream>
#include <vector>

using namespace std;

class SavingClass {
public:
	SavingClass(GDInterface paral, int name) {
		save->forvard = NULL;
		save->paral_ = paral;
		save->name_ = name;
		save->back = NULL;
	}

	~SavingClass(){
		auto tail = save;
		while (save) {
			tail = save->forvard;
			delete save;
			save = tail;
		}
	}

	int append(GDInterface paral, int name) {

		auto head = save;

		while (save->forvard != NULL) {
			if (save->name_ != name) {
				save = save->forvard;
			}
			else {
				save = head;
				return -1;
			}
		}
		auto tail = save;
		save->forvard = new SavingStruct();
		save = save->forvard;
		save->back = tail;
		save->paral_ = paral;
		save->name_ = name;
		save = head;

		return 0;

	}

	GDInterface find(int name) {
		SavingStruct* head = save;
		while (save->forvard != NULL) {
			if (save->name_ != name) {
				save = save->forvard;
			}
			else {
				save = head;
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
		save = head;
	}

	

	vector<GDInterface> getAll() {
		vector<GDInterface> result;
		SavingStruct* head = save;
		while (save != nullptr) {
			result.push_back(save->paral_);
			save = save->forvard;
		}
		save = head;
		return result;
	}

	void Del(int x) {
		if ((save->back == nullptr) && (save->forvard != nullptr) && save->name_ == x) {                     
			auto temp = save;	                        
			save = save->forvard;
			save->back = NULL;
			delete temp;		                            	                                
			return;		                               
		}
		else if(save->forvard == nullptr && save->name_ == x){
			auto temp = save;	                           
			save = save->back;	                                
			save->forvard = NULL;	                                
			delete temp;
			return;		                                   
		}
		else {
			SavingStruct* head = save;
			while (save->forvard != NULL) {
				if (save->name_ != x) {
					save = save->forvard;
				}
				else {
					auto temp = save;
					auto temp2 = save;
					temp2->back->forvard = temp->forvard;
					temp2->forvard->back = temp->back;
					delete temp, temp2;
				}
			}
			save = head;

		}                                  
	}

private:
	struct SavingStruct
	{
		SavingStruct* forvard = nullptr;
		GDInterface paral_;
		int name_;
		SavingStruct* back = nullptr;

	}* save = new SavingStruct;
};