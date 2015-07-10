
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
} player;

class TestSectorRender : public AllegroApp {

public:

	TestSectorRender ( int sw, int sh )
		: AllegroApp( sw, sh )
	{

	}

	virtual ~TestSectorRender() {}

	void HandleKeyInput() {

	}

private:

	player pl;

};

