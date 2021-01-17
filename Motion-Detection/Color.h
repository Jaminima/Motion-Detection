#pragma once

class Color
{
public:
	unsigned int rgba = 0;

	void SetR(unsigned int r) restrict(amp, cpu) { rgba = rgba | ((r & 0xFF)); }
	void SetG(unsigned int g) restrict(amp, cpu) { rgba = rgba | ((g & 0xFF) << 8); }
	void SetB(unsigned int b) restrict(amp, cpu) { rgba = rgba | ((b & 0xFF) << 16); }

	unsigned int GetR()restrict(amp, cpu) { return (rgba) & 0xFF; }
	unsigned int GetG()restrict(amp, cpu) { return (rgba >> 8) & 0xFF; }
	unsigned int GetB()restrict(amp, cpu) { return (rgba >> 16) & 0xFF; }

	Color() restrict(amp,cpu) {}

	Color(unsigned int r, unsigned int g, unsigned int b) restrict(amp, cpu)
	{
		rgba |= ((b & 0xFF) << 16) | ((g & 0xFF) << 8) | ((r & 0xFF));
	}

	Color operator-(Color c) restrict(amp, cpu)
	{
		unsigned int b1 = (rgba >> 16) & 0xFF,
			g1 = (rgba >> 8) & 0xFF,
			r1 = rgba & 0xFF;

		unsigned int b2 = (c.rgba >> 16) & 0xFF,
			g2 = (c.rgba >> 8) & 0xFF,
			r2 = c.rgba & 0xFF;

		return Color(r1 - r2, g1 - g2, b1 - b2);
	}
};

