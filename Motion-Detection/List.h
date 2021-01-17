#pragma once
#include <iostream>

class Item {
public:
	Item* Next = 0x0;
	void* Obj = 0x0;

	Item(void* Obj) {
		this->Obj = Obj;
	}
};

class List {
public:
	Item* Head = 0x0;
	int Length = 0;

	void Add(void* Obj) {
		Item* Temp = new Item(Obj);
		Temp->Next = Head;
		Head = Temp;

		Length++;
	}

	void** ToArray() {
		void** Arr = (void**)malloc(sizeof(void*) * Length);

		int i = 0;
		Item* I = Head;
		while (I != 0x0) {
			Arr[i] = I->Obj;

			I = I->Next;
			i++;
		}

		return Arr;
	}
};