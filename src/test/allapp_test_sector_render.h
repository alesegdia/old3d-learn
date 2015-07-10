
#pragma once

#include "../app/allegroapp.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <vector>

#include "../core/geometry.h"

typedef struct {
	vec3 pos;
	float angle = M_PI;
} player;

class TestSectorRender : public AllegroApp {

public:

	TestSectorRender ( int sw, int sh )
		: AllegroApp( sw, sh )
	{

	}

	virtual ~TestSectorRender() {}

	void Ready() {
		sector s;
		s.vertices.add(vec2(70,20));
		s.vertices.add(vec2(70,70));
		s.vertices.add(vec2(20,70));
		s.vertices.add(vec2(20,20));
		s.floor = 0;
		s.ceil = 20;
	}

	void HandleKeyInput() {
		if(key[KEY_UP]) {
			pl.pos.y -= sin(pl.angle);
			pl.pos.x -= cos(pl.angle);
		}

		if(key[KEY_DOWN] ) {
			pl.pos.y += sin(pl.angle);
			pl.pos.x += cos(pl.angle);
		}

		if(key[KEY_LEFT]) {
			pl.angle -= 0.05;
		}

		if(key[KEY_RIGHT] ) {
			pl.angle += 0.05;
		}

		if(key[KEY_SLEFT]) {
			pl.pos.y -= sin(pl.angle+M_PI/2);
			pl.pos.x -= cos(pl.angle+M_PI/2);
		}

		if( key[KEY_SRIGHT] ) {
			pl.pos.y += sin(pl.angle+M_PI/2);
			pl.pos.x += cos(pl.angle+M_PI/2);
		}
	}

	void Draw() {
		for( sector s : sectors ) {

		}
	}

private:

	player pl;
	std::vector<sector> sectors;

};

