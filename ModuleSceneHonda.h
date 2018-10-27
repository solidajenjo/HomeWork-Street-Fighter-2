#ifndef __MODULESCENEHONDA_H__
#define __MODULESCENEHONDA_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
class ModuleSceneHonda : public Module
{
public:

	ModuleSceneHonda(bool start_enabled);
	~ModuleSceneHonda();
	bool Init();
	update_status Update();
	bool CleanUp();
public:

	SDL_Texture * graphics = nullptr;
	SDL_Rect ground;
	SDL_Rect background;
	SDL_Rect side;
	SDL_Rect ceiling;
	SDL_Rect pool;

	Animation water;
	Animation fuji;

};

#endif // __MODULESCENEHONDA_H__