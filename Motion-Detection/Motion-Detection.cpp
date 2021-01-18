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

int main()
{
	pick_accelerator();

	List* l = FindAndCompareFiles();

	float f = Comparer::noiseReduction(l);

	SaveToFile(l, f);
}
