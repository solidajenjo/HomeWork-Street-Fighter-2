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

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	PlayerAnimationBase* animSheet;
private:
	int lastX = 100;
	float kameSpeed, kameAngle, kamePos, playerPos, timer;
	bool playerBusy, flipped;
	int speed = 4;
	playerActions playerAction;	
};

#endif // __MODULEPLAYER_H__