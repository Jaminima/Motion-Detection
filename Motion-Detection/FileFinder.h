#pragma once
#include <string>
#include <filesystem>
#include "Image.h"
#include "Comparer.h"
#include "List.h"
#include "Const.h"

#include <iostream>
#include <fstream>
using namespace std;

const std::string imgpath = "./Images/";

inline bool fileExists(const std::string& name) {
	std::string file = imgpath + name;
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

void SaveToFile(List* l, float noiseReduction) {
	ofstream file;
	file.open("./Data.txt");

	Item* i = l->Head;
	float* p;
	while (i != 0x0) {
		p = (float*)i->Obj;
		file << to_string(Comparer::removeNoise(*p, noiseReduction)) << "\n";
		i = i->Next;
	}

	file.flush();
	file.close();
}

List* FindAndCompareFiles() {
	List* l = new List();
	Image *lastimg = new Image((imgpath + "1.png").c_str(),px,py);

	for (unsigned int i = 2;fileExists(std::to_string(i)+".png"); i++) {
		std::string file = imgpath + std::to_string(i) + ".png";
		Image *img = new Image(file.c_str(),px,py);

		float diff = Comparer::getDifference(img, lastimg);

		printf("%i,%f\n", i, diff);
		l->Add(new float (diff));

		delete lastimg;
		lastimg = img;
	}

	return l;
}
