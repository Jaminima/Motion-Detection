#pragma once
#include "Color.h"

#include "stb_image.h"

class Image
{
public:
	Color* data;
	int x, y;

	Image(int x, int y);

	Image(char* fileString, int x, int y);
};

