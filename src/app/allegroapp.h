#include <allegro5/allegro.h>

class AllegroApp {
public:
	AllegroApp ( int screen_width, int screen_height );
	virtual ~AllegroApp ();

private:

	void Init();

	int screenWidth, screenHeight;

	const int FPS = 60;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	bool redraw = true;
	bool doexit = false;

};

