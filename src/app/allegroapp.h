#include <allegro5/allegro.h>

class AllegroApp {
public:
	AllegroApp ( int screen_width, int screen_height );
	virtual ~AllegroApp ();

	int Exec();

private:

	int Init();

protected:

	enum MYKEYS {
		KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SLEFT, KEY_SRIGHT
	};

	void HandleEvent(ALLEGRO_EVENT& ev);
	virtual void Draw();
	virtual void Ready();
	virtual void HandleKeyInput();

	int screenWidth, screenHeight;

	const int FPS = 60;

	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;
	ALLEGRO_COLOR red_color;
	ALLEGRO_COLOR grey_color;
	ALLEGRO_COLOR yellow_color;

	bool redraw = true;
	bool doexit = false;

	bool key[6] = { false, false, false, false, false, false };

};

