#include "Image.h"
#include "Const.h"

Image::~Image()
{
	delete[] ogdata;
}

Image::Image()
{
}

Image::Image(const char* fileString)
{
	ogdata = stbi_load(fileString, new int(px), new int(py), new int(4), 4);
	data = (Color*)ogdata;
}
