#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 4;
const int BOUNCER_HALF_SIZE = BOUNCER_SIZE / 2;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SLEFT, KEY_SRIGHT
};

float cross(float x1, float y1, float x2, float y2) {
	return x1 * y2 - y1 * x2;
}

void intersect( float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float* x, float* y ) {
	*x = cross(x1,y1,x2,y2);
	*y = cross(x3,y3,x4,y4);
	float det = cross(x1-x2,y1-y2,x3-x4,y3-y4);
	*x = cross(*x, x1-x2, *y, x3-x4)/det;
	*y = cross(*x, y1-y2, *y, y3-y4)/det;
}

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *sub_bmp1 = NULL;
	ALLEGRO_BITMAP *sub_bmp2 = NULL;
	ALLEGRO_BITMAP *sub_bmp3 = NULL;
	float px = 50;
	float py = 50;
	float vx1 = 70, vy1 = 20;
	float vx2 = 70, vy2 = 70;
	bool key[6] = { false, false, false, false };
	bool redraw = true;
	bool doexit = false;
	float angle = M_PI;

	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	sub_bmp1 = al_create_sub_bitmap(al_get_backbuffer(display), 0, 				0,	SCREEN_W/3, SCREEN_H);
	sub_bmp2 = al_create_sub_bitmap(al_get_backbuffer(display), SCREEN_W/3, 	0, 	SCREEN_W/3, SCREEN_H);
	sub_bmp3 = al_create_sub_bitmap(al_get_backbuffer(display), 2*SCREEN_W/3, 	0, 	SCREEN_W/3, SCREEN_H);
	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));
	ALLEGRO_COLOR red_color = al_map_rgb(184, 22, 22);
	ALLEGRO_COLOR grey_color = al_map_rgb(184, 184, 184);
	ALLEGRO_COLOR yellow_color = al_map_rgb(255, 255, 0);

	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0,0,0));
	al_start_timer(timer);

	while(!doexit)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER) {
			if(key[KEY_UP] && py >= 4.0) {
				py -= sin(angle);
				px -= cos(angle);
			}

			if(key[KEY_DOWN] && py <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				py += sin(angle);
				px += cos(angle);
			}

			if(key[KEY_LEFT] && px >= 4.0) {
				angle -= 0.05;
			}

			if(key[KEY_RIGHT] && px <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				angle += 0.05;
			}

			if(key[KEY_SLEFT]) {
				py -= sin(angle+M_PI/2);
				px -= cos(angle+M_PI/2);
			}

			if( key[KEY_SRIGHT] ) {
				py += sin(angle+M_PI/2);
				px += cos(angle+M_PI/2);
			}

			redraw = true;
		}
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;

				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = true;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;

				case ALLEGRO_KEY_Q: 
					key[KEY_SLEFT] = true;
					break;

				case ALLEGRO_KEY_E:
					key[KEY_SRIGHT] = true;
					break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;

				case ALLEGRO_KEY_LEFT: 
					key[KEY_LEFT] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;

				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;

				case ALLEGRO_KEY_Q:
					key[KEY_SLEFT] = false;
					break;

				case ALLEGRO_KEY_E:
					key[KEY_SRIGHT] = false;
					break;
			}
		}

		if(redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;

			al_set_target_bitmap(al_get_backbuffer(display));
			al_clear_to_color(al_map_rgb(0,0,0));

			al_set_target_bitmap(sub_bmp1);
			al_draw_filled_rectangle(px-BOUNCER_HALF_SIZE, py-BOUNCER_HALF_SIZE, px+BOUNCER_HALF_SIZE, py+BOUNCER_HALF_SIZE, red_color);
			al_draw_line(px, py, px - cos(angle)*10, py - sin(angle)*10, grey_color, 1);
			al_draw_line(vx1, vy1, vx2, vy2, yellow_color, 1);

			al_set_target_bitmap(sub_bmp2);
			float tx1, tx2, tz1, tz2, ty1, ty2;
			tx1 = vx1 - px, ty1 = vy1 - py;
			tx2 = vx2 - px, ty2 = vy2 - py;
			tz1 = tx1 * cos(angle) + ty1 * sin(angle);
			tz2 = tx2 * cos(angle) + ty2 * sin(angle);
			tx1 = tx1 * sin(angle) - ty1 * cos(angle);
			tx2 = tx2 * sin(angle) - ty2 * cos(angle);

			al_draw_line(50 + tx1, 50 + tz1, 50 + tx2, 50 + tz2, yellow_color, 1);
			al_draw_filled_rectangle(50 - BOUNCER_HALF_SIZE, 50 - BOUNCER_HALF_SIZE, 50 + BOUNCER_HALF_SIZE, 50 + BOUNCER_HALF_SIZE, red_color);
			al_draw_line(50, 50, 50, 40, grey_color, 1);

			al_set_target_bitmap(sub_bmp3);

			if ( tz1 > 0 || tz2 > 0 ) {
				float ix1, ix2, iz1, iz2;
				intersect(tx1,tz1,tx2,tz2,-0.0001,0.0001,-20,5,&ix1,&iz1);
				intersect(tx1,tz1,tx2,tz2,0.0001,0.0001,20,5,&ix2,&iz2);
				if( tz1 <= 0 ) {
					if( iz1 > 0 ) {
						tx1 = ix1;
						tz1 = iz1;
					} else {
						tx1 = ix2; tz1 = iz2;
					}
				}
				if( tz2 <= 0 ) {
					if( iz1 > 0 ) {
						tx2 = ix1; tz2 = iz1;
					} else {
						tx2 = ix2; tz2 = iz2;
					}
				}
				float x1, x2, y1a, y1b, y2a, y2b;
				x1 = -tx1 * 16 /tz1; y1a = -50 / tz1; y1b = 50 / tz1;
				x2 = -tx2 * 16 /tz2; y2a = -50 / tz2; y2b = 50 / tz2;
				al_draw_line( 50 + x1, 50 + y1a, 50 + x2, 50 + y2a, yellow_color, 1);
				al_draw_line( 50 + x1, 50 + y1b, 50 + x2, 50 + y2b, yellow_color, 1);
				al_draw_line( 50 + x1, 50 + y1a, 50 + x1, 50 + y1b, yellow_color, 1);
				al_draw_line( 50 + x2, 50 + y2a, 50 + x2, 50 + y2b, yellow_color, 1);
			}

			al_flip_display();
		}
	}

	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0;
}

