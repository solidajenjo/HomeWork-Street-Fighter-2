#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* kameEffect = nullptr;
	SDL_Texture* kameEffectCharged = nullptr;
	SDL_Texture* blackFilter = nullptr;
	SDL_Texture* blueFilter = nullptr;
	SDL_Rect kameRect;
	SDL_Rect background;
	Animation idle;
	Animation backward;
	Animation forward;
	Animation charging;
	iPoint position;

private:
	int lastX = SCREEN_WIDTH / 2;
	float kameSpeed, kameAngle;
	bool kameCharged, playerBusy;
	unsigned int alAtaquerFX, noPuedeSerFX, epetecanFX;
	int speed = 4;
};

#endif // __MODULEPLAYER_H__