
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

// http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
char get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, 
    float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}

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
		s.floor = -400;
		s.ceil = 400;
		sectors.push_back(s);
		sw2 = screenWidth/2.f;
		sh2 = screenHeight/2.f;
		pl.pos.x = 50;
		pl.pos.y = 50;
		red_color = al_map_rgb(184, 22, 22);
		grey_color = al_map_rgb(184, 184, 184);
		yellow_color = al_map_rgb(255, 255, 0);
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
		al_clear_to_color(al_map_rgb(128,0,0));
		al_set_target_bitmap(al_get_backbuffer(display));
		for( sector s : sectors ) {
			for( int i = 0; i < s.vertices.size(); i++ ) {
				vec2 v1 = s.vertices[i];
				vec2 v2 = s.vertices[(i+1)%s.vertices.size()];
				float dx1 = v1.x - pl.pos.x, dy1 = v1.y - pl.pos.y;
				float dx2 = v2.x - pl.pos.x, dy2 = v2.y - pl.pos.y;
				float vtx1 = dx1 * pcos + dy1 * psin, vtz1 = dx1 * psin - dy1 * pcos;
				float vtx2 = dx2 * pcos + dy2 * psin, vtz2 = dx2 * psin - dy2 * pcos;
				al_draw_line( sw2 + vtx1, sh2 + vtz1, sw2 + vtx2, sh2 + vtz2, yellow_color, 1);
				if( vtz1 < 0 || vtz2 < 0 ) {

					float i1x, i1y, i2x, i2y;
					char i1 = get_line_intersection( vtx1,vtz1, vtx2,vtz2, -0.000001f,0.000001f, -2000.f,5.f, &i1x,&i1y );
					char i2 = get_line_intersection( vtx1,vtz1, vtx2,vtz2,  0.000001f,0.000001f,  2000.f,5.f, &i2x,&i2y );

					// endpoint 1
					if( vtz1 >= 0 ) {
						if( i1 == 1 ) 	{  vtx1 = i1x; vtz1 = -i1y; }
						else {  vtx1 = i2x; vtz1 = -i2y; }
					}
					// endpoint 2
					if( vtz2 >= 0 ) {
						if( i1 == 1 ) 	{ vtx2 = i1x; vtz2 = -i1y; }
						else 	 		{ vtx2 = i2x; vtz2 = -i2y; }
					}
					float x1, x2, y1a, y1b, y2a, y2b;
					float fov = 512; // higher -> less FOV
					for( float f = s.floor; f < s.ceil; f = f + 1 ) {
						x1 = -vtx1 * fov / vtz1; y1a = f / vtz1; y1b = f / vtz1;
						x2 = -vtx2 * fov / vtz2; y2a = f / vtz2; y2b = f / vtz2;
						al_draw_line( sw2 + x1, sh2 + y1a, sw2 + x2, sh2 + y2a, yellow_color, 1);
						al_draw_line( sw2 + x1, sh2 + y1b, sw2 + x2, sh2 + y2b, yellow_color, 1);
						al_draw_line( sw2 + x1, sh2 + y1a, sw2 + x1, sh2 + y1b, yellow_color, 1);
						al_draw_line( sw2 + x2, sh2 + y2a, sw2 + x2, sh2 + y2b, yellow_color, 1);
					}
				}
			}
		}
		al_draw_filled_rectangle(sw2-2, sh2-2, sw2+2, sh2+2, red_color);
	}

private:

	player pl;
	std::vector<sector> sectors;

	ALLEGRO_COLOR red_color;
	ALLEGRO_COLOR grey_color;
	ALLEGRO_COLOR yellow_color;

};

