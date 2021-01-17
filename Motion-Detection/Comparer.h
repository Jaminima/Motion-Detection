#pragma once
#include "Image.h"
#include <amp.h>

using namespace Concurrency;

static class Comparer
{
public:
	static float getDifference(Image *image1, Image *image2) {
		int x = image1->x, y = image1->y;
		int size = x * y;

		array_view<Color, 2> rgba1(y, x, image1->data);
		array_view<Color, 2> rgba2(y, x, image2->data);

		float *diffs = (float*)malloc(sizeof(float) * size);
		array_view<float, 2> diff(y, x, diffs);

		parallel_for_each(
			rgba1.extent,
			[=](index<2> idx) restrict(amp)
			{
				Color d = rgba1[idx] - rgba2[idx];
				diff[idx] = d.rgba;
			}
		);

		diff.synchronize();

		float diffAvg = 0;
		for (int i = 0; i < size; i++) diffAvg += diffs[i];
		diffAvg /= size;

		delete[] diffs;

		return diffAvg;
	}
};

