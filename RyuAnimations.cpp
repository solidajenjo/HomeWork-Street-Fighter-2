#include "RyuAnimations.h"
#include "Application.h"
#include "ModuleTextures.h"


RyuAnimations::RyuAnimations() 
{
}


RyuAnimations::~RyuAnimations()
{
}

bool RyuAnimations::setUp()
{
	graphics = App->textures->Load("ryu4.png"); // arcade version

	//TODO remake animations w/ editor
	// idle animation (arcade sprite sheet)
	idle.frames.push_back({ 7, 10, 60, 96 });
	idle.frames.push_back({ 95, 10, 60, 96 });
	idle.frames.push_back({ 184, 10, 60, 96 });
	idle.frames.push_back({ 276, 10, 60, 96 });
	idle.frames.push_back({ 366, 10, 60, 96 });
	idle.speed = 0.1f;

	backward = new Animation();
	// walk backward animation (arcade sprite sheet)
	backward->frames.push_back({ 542, 131, 61, 87 });
	backward->frames.push_back({ 628, 129, 59, 90 });
	backward->frames.push_back({ 713, 128, 57, 90 });
	backward->frames.push_back({ 797, 127, 57, 90 });
	backward->frames.push_back({ 883, 128, 58, 91 });
	backward->frames.push_back({ 974, 129, 57, 89 });
	backward->speed = 0.1f;

	forward = new Animation();
	forward->frames.push_back({ 0, 131, 65, 90 });
	forward->frames.push_back({ 75, 129, 63, 90 });
	forward->frames.push_back({ 160, 128, 65, 90 });
	forward->frames.push_back({ 255, 127, 65, 90 });
	forward->frames.push_back({ 340, 128, 65, 91 });
	forward->frames.push_back({ 425, 129, 62, 90 });
	forward->speed = 0.1f;

	kick.frames.push_back({ 0, 650, 80, 105 });
	kick.frames.push_back({ 80, 650, 80, 105 });
	kick.frames.push_back({ 160, 650, 100, 105 });
	kick.frames.push_back({ 80, 650, 80, 105 });
	kick.frames.push_back({ 0, 650, 80, 105 });
	kick.speed = 0.1f;

	punch.frames.push_back({ 245, 261, 80, 105 });
	punch.frames.push_back({ 325, 261, 84, 105 });
	punch.frames.push_back({ 426, 261, 120, 105 });
	punch.frames.push_back({ 325, 261, 84, 105 });
	punch.frames.push_back({ 245, 261, 80, 105 });
	punch.speed = 0.1f;

	special.frames.push_back({ 491, 1554, 54, 51 });
	special.frames.push_back({ 545, 1554, 68, 51 });
	special.speed = 0.1f;

	specialRect.x = 0;
	specialRect.y = 0;
	specialRect.w = 512;
	specialRect.h = 512;

	playerSpecialRect.x = 350;
	playerSpecialRect.y = 1547;
	playerSpecialRect.w = 120;
	playerSpecialRect.h = 92;

	return true;
}
