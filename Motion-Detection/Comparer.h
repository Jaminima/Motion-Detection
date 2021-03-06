#pragma once
#include "Image.h"
#include "Const.h"
#include <amp.h>
#include "List.h"

using namespace Concurrency;

static class Comparer
{
public:
	static float removeNoise(float f, float noiseReduction) {
		return f - noiseReduction;
	}

	static float noiseReduction(float** l, unsigned int length) {
		int ind = length * 0.75f;
		if (length % 2 != 0) return (*l[ind] + *l[ind + 1]) / 2;
		else return *l[ind];
	}

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
				diff[idx] = rgba1[idx] - rgba2[idx];
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

