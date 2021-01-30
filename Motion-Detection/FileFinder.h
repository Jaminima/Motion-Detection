#pragma once
#include <string>
#include <filesystem>
#include "Image.h"
#include "Comparer.h"
#include "List.h"
#include "Const.h"

#include <iostream>
#include <thread>
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

void LoadFrame(Image** l, unsigned int i) {
	std::string file = imgpath + std::to_string(i) + ".png";
	Image* img = new Image(file.c_str(), px, py);

	l[i-1] = img;
}

Image** LoadAllFiles(const unsigned int imageCount) {
	Image **images = new Image*[imageCount];
	bool hasUnFilled = true;
	unsigned int i = 1;

	for (;fileExists(std::to_string(i)+".png"); i++) {
		images[i - 1] = 0x0;
		std::thread t(LoadFrame,images,i);
		t.detach();
	}

	while (hasUnFilled) {
		hasUnFilled = false;
		for (unsigned int j = 0; j < i; j++) { if (images[j] == 0x0) hasUnFilled = true; }
		this_thread::sleep_for(std::chrono::milliseconds(500)); 
	}

	return images;
}
