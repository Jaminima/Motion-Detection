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

	Image(const char* fileString);
};

