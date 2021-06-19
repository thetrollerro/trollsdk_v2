#pragma once
#include <cstdint>
#include <d3d9.h>

class color {
public:
	int r, g, b, a;

	color() {
		r = g = b = a = 255;
	}

	color(int _r, int _g, int _b, int _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	color(int _r, int _g, int _b) {
		r = _r;
		g = _g;
		b = _b;
		a = 255;
	}

	color(float _r, float _g, float _b, float _a) {
		r = static_cast<int>(_r * 255.0f);
		g = static_cast<int>(_g * 255.0f);
		b = static_cast<int>(_b * 255.0f);
		a = static_cast<int>(_a * 255.0f);
	}

	color(float _color[4]) {
		r = static_cast<int>(_color[0] * 255.0f);
		g = static_cast<int>(_color[1] * 255.0f);
		b = static_cast<int>(_color[2] * 255.0f);
		a = static_cast<int>(_color[3] * 255.0f);
	}

	color(float _color[3], float alpha = 1.f) {
		r = static_cast<int>(_color[0] * 255.0f);
		g = static_cast<int>(_color[1] * 255.0f);
		b = static_cast<int>(_color[2] * 255.0f);
		a = static_cast<int>(alpha * 255.0f);
	}

	std::uint32_t to_d3d(void) {
		return D3DCOLOR_RGBA(this->r, this->g, this->b, this->a);
	}

	inline static color blend(color a, color b, float multiplier, bool include_alpha = true) {
		return color(
			a.r + static_cast<int>(multiplier * (b.r - a.r)),
			a.g + static_cast<int>(multiplier * (b.g - a.g)),
			a.b + static_cast<int>(multiplier * (b.b - a.b)),
			include_alpha ? a.a + static_cast<int>(multiplier * (b.a - a.a)) : a.a
		);
	}
};
