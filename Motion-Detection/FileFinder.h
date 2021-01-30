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

void SaveToFile(float* l, unsigned int size) {
	ofstream file;
	file.open("./Data.txt");

	for (unsigned int i=0;i<size;i++){
		file << to_string(l[i]) << "\n";
	}

	file.flush();
	file.close();
}

void LoadFrame(Color** l, unsigned int i) {
	std::string file = imgpath + std::to_string(i) + ".png";
	Image img = Image(file.c_str());

	l[i-1] = img.data;
}

Color** LoadAllFiles(const unsigned int imageCount) {
	Color **images = new Color*[imageCount];
	bool hasUnFilled = true;
	unsigned int i = 1;

	for (;/*fileExists(std::to_string(i)+".png")*/i<=imageCount; i++) {
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
