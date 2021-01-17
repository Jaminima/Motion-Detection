#include "Image.h"

Image::~Image()
{
	delete[] ogdata;
}

Image::Image()
{
}

Image::Image(int x, int y)
{
	this->x = x;
	this->y = y;
	data = new Color[x*y];
}

Image::Image(const char* fileString, int x, int y)
{
	this->x = x;
	this->y = y;
	ogdata = stbi_load(fileString, &x, &y, new int(4), 4);
	data = (Color*)ogdata;
}
