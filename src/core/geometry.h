
struct vec2 {
	float x, y;
};

struct vec3 {
	float x, y, z;
};

struct line {
	vec2 a, b;
};

struct sector {

	vec2 pos;
	float floor, ceil;

	sector( const vec2& pos, float floor, float ceil ) {
		this->pos = pos;
		this->floor = floor;
		this->ceil = ceil;
	}

};
