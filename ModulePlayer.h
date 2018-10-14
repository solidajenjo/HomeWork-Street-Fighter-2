#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;
enum ryuActions
{
	KAME,
	PUNCH,
	KICK
};

enum kameStatus
{
	READY,
	CHARGING,
	CHARGED,
	RELEASED
};

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
	SDL_Rect ryuKameRect;
	SDL_Rect kameRect;
	SDL_Rect background;
	Animation idle;
	Animation backward;
	Animation forward;
	Animation charging;
	Animation kick;
	Animation punch;
	Animation kameBall;

	iPoint position;

private:
	int lastX = SCREEN_WIDTH / 2;
	float kameSpeed, kameAngle, kamePos, ryuPos, timer;
	bool playerBusy;
	unsigned int alAtaquerFX, noPuedeSerFX, epetecanFX;
	int speed = 4;
	ryuActions ryuAction;
	kameStatus kameStatus;
};

#endif // __MODULEPLAYER_H__