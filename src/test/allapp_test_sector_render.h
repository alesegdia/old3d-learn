
#pragma once

#include "../app/allegroapp.h"
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <vector>

#include "../core/geometry.h"

// Writing a fast 3D graphics engine: www.gamers.org/dEngine/doom/papers/webview.ps.gz

typedef struct {
	vec3 pos;
	float angle = M_PI;
	float anglecos, anglesin;
} player;

class TestSectorRender : public AllegroApp {

public:

	TestSectorRender ( int sw, int sh )
		: AllegroApp( sw, sh )
	{

	}

	virtual ~TestSectorRender() {}

	float sw2, sh2;

	void Ready() {
		al_clear_to_color(al_map_rgb(255, 0, 255));
		al_set_target_bitmap(al_get_backbuffer(display));
		sector s;
		s.vertices.push_back(vec2(70,20));
		s.vertices.push_back(vec2(70,70));
		s.vertices.push_back(vec2(20,70));
		s.vertices.push_back(vec2(20,20));
		s.floor = 0;
		s.ceil = 20;
		sectors.push_back(s);
		red_color = al_map_rgb(184, 22, 22);
		grey_color = al_map_rgb(184, 184, 184);
		yellow_color = al_map_rgb(255, 255, 0);
		sw2 = screenWidth/2.f;
		sh2 = screenHeight/2.f;
		pl.pos.x = 50;
		pl.pos.y = 50;
	}

	void HandleKeyInput() {
		if(key[KEY_UP]) {
			pl.pos.y += cos(pl.angle);
			pl.pos.x += sin(pl.angle);
		}

		if(key[KEY_DOWN] ) {
			pl.pos.y -= cos(pl.angle);
			pl.pos.x -= sin(pl.angle);
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
		float pcos = cos(-pl.angle);
		float psin = sin(-pl.angle);
		al_set_target_bitmap(al_get_backbuffer(display));
		al_clear_to_color(al_map_rgb(128,0,0));
		for( sector s : sectors ) {
			for( int i = 0; i < s.vertices.size(); i++ ) {
				vec2 v1 = s.vertices[i];
				vec2 v2 = s.vertices[(i+1)%s.vertices.size()];
				float dx1 = v1.x - pl.pos.x, dy1 = v1.y - pl.pos.y;
				float dx2 = v2.x - pl.pos.x, dy2 = v2.y - pl.pos.y;
				float vtx1 = dx1 * pcos + dy1 * psin, vtz1 = dx1 * psin - dy1 * pcos;
				float vtx2 = dx2 * pcos + dy2 * psin, vtz2 = dx2 * psin - dy2 * pcos;
				if( vtz1 < 0 || vtz2 < 0 ) {
					al_draw_line( sw2 + vtx1, sh2 + vtz1, sw2 + vtx2, sh2 + vtz2, yellow_color, 1);
				}
			}
		}
		al_draw_filled_rectangle(sw2-2, sh2-2, sw2+2, sh2+2, red_color);
		al_flip_display();
	}

private:

	player pl;
	std::vector<sector> sectors;

	ALLEGRO_COLOR red_color;
	ALLEGRO_COLOR grey_color;
	ALLEGRO_COLOR yellow_color;

};

