#pragma once
#include "Color.h"

#include "stb_image.h"

class Image
{
public:
	stbi_uc* ogdata;
	Color* data;
	int x, y;

	~Image();

	Image();

	Image(int x, int y);

	Image(const char* fileString, int x, int y);
};

