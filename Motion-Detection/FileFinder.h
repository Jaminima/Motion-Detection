#pragma once
#include <string>
#include <filesystem>
#include "Image.h"
#include "Comparer.h"

const std::string imgpath = "./Images/";

inline bool fileExists(const std::string& name) {
	std::string file = imgpath + name;
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

void FindAndCompareFiles() {
	Image *lastimg = new Image((imgpath + "1.png").c_str(),1920,1080);

	for (unsigned int i = 2;fileExists(std::to_string(i)+".png"); i++) {
		std::string file = imgpath + std::to_string(i) + ".png";
		Image *img = new Image(file.c_str(),1920,1080);

		float diff = Comparer::getDifference(img, lastimg);

		printf("Frame %i Diff %f\n", i, diff);

		delete lastimg;
		lastimg = img;
	}
}
