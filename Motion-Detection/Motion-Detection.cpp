#include <iostream>
#include "Image.h"
#include "FileFinder.h"
#include "Comparer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool pick_accelerator()
{
	std::vector<accelerator> accs = accelerator::get_all();
	accelerator chosen_one;

	auto result = std::find_if(accs.begin(), accs.end(),
		[](const accelerator& acc)
		{
			return !acc.is_emulated &&
				acc.supports_double_precision &&
				!acc.has_display;
		});

	if (result != accs.end())
	{
		chosen_one = *(result);
	}

	std::wcout << chosen_one.description << std::endl;
	bool success = accelerator::set_default(chosen_one.device_path);
	return success;
}

int compare(const void* a, const void* b)
{
	const int* x = (int*)a;
	const int* y = (int*)b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;

	return 0;
}

int main()
{
	pick_accelerator();

	Color** l = LoadAllFiles(515);

	//std::qsort(l, l->Length, sizeof(float), compare);

	//float f = Comparer::noiseReduction(fs, l->Length);

	float* f = Comparer::computeDifference(l, 515);

	SaveToFile(f, 515);
}
