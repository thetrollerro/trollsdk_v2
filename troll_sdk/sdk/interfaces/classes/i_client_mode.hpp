#pragma once
#include "../../math/vector.hpp"

struct view_setup_t {
	__int32 x; // 0x0000
	__int32 x_old; // 0x0004
	__int32 y; // 0x0008
	__int32 y_old; // 0x000C
	__int32 width; // 0x0010
	__int32 width_old; // 0x0014
	__int32 height; // 0x0018
	__int32 height_old; // 0x001C
	char pad_0x0020[ 0x90 ]; // 0x0020
	float fov; // 0x00B0
	float viewmodel_fov; // 0x00B4
	vec3_t origin; // 0x00B8
	vec3_t angles; // 0x00C4
	char pad_0x00D0[ 0x7C ]; // 0x00D0
};

class i_client_mode {
public:
	/* do class later */
};