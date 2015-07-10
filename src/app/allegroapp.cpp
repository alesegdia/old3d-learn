#include "allegroapp.h"
#include <stdio.h>

AllegroApp::AllegroApp( int screen_width, int screen_height )
	: screenWidth(screen_width), screenHeight(screen_height)
{

}

AllegroApp::~AllegroApp() {

}

int AllegroApp::Init() {
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

	display = al_create_display(screenWidth, screenHeight);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	al_clear_to_color(al_map_rgb(255, 0, 255));
	al_set_target_bitmap(al_get_backbuffer(display));

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

	Ready();

	return 0;
}

void AllegroApp::HandleEvent(ALLEGRO_EVENT& ev) {
	if(ev.type == ALLEGRO_EVENT_TIMER) {
		HandleKeyInput();
		redraw = true;
	}
	else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		doexit = true;
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
}

void AllegroApp::Draw() {

}

void AllegroApp::Ready() {

}

void AllegroApp::HandleKeyInput() {

}

int AllegroApp::Exec() {
	int retcode = Init();
	if( retcode != 0 ) return retcode;

	while(!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		HandleEvent(ev);

		if( redraw && al_is_event_queue_empty(event_queue) ) {
			redraw = false;
			Draw();
		}
	}

}


