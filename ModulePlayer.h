#ifndef __MODULEPLAYER_H__
#define __MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Point.h"

struct SDL_Texture;

class PlayerAnimationBase;

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

private:
	int lastX = SCREEN_WIDTH / 2;
	float kameSpeed, kameAngle, kamePos, playerPos, timer;
	bool playerBusy, flipped;
	int speed = 4;
	playerActions playerAction;
	PlayerAnimationBase* animSheet;
};

#endif // __MODULEPLAYER_H__