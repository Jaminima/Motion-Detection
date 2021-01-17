#include "Image.h"

Image::Image(int x, int y)
{
	this->x = x;
	this->y = y;
	data = new Color[x*y];
}

Image::Image(char* fileString, int x, int y)
{
	this->x = x;
	this->y = y;
	data = (Color *)stbi_load(fileString, &x, &y, new int(4), 4);
}
