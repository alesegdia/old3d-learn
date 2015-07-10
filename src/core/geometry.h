
#pragma once

#include <vector>

struct vec2 {
	float x, y;
	vec2() : x(0), y(0) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}
};

struct vec3 {
	float x, y, z;
	vec3() : x(0), y(0), z(0) {}
};

struct line {
	vec2 a, b;
};

struct sector {

	std::vector<vec2> vertices;
	float floor, ceil;

};
