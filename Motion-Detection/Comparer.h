#pragma once
#include "Const.h"
#include "Image.h"
#include <amp.h>

using namespace Concurrency;

static class Comparer
{
public:

	/*static float getDifference(array_view<Image, 1> imageView, index<1> idx) restrict(amp) {
		Image i1 = imageView[idx],
			i2 = imageView[idx+1];

		float diff = 0;
		
		for (unsigned int x = 0, y = 0; y <= i1.y;) {
			diff += i1.data[y, x] - i2.data[y, x];

			x++;
			if (x == i1.x) { x = 0; y++; }
		}

		return diff;
	}*/

	static float* computeDifference(Color** images, unsigned int size) {
		array_view<Color, 2> imageView(size,py*px,images);

		float* diffs = (float*)malloc(sizeof(float) * size);
		array_view<float, 1> diff(size, diffs);

		parallel_for_each(
			imageView.extent,
			[=](index<2> idx) restrict(amp)
			{
				//diff[idx] = getDifference(imageView,idx);
			}
		);

		diff.synchronize();

		return diffs;
	}
};

