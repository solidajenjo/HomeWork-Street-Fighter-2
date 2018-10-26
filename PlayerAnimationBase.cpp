#include "PlayerAnimationBase.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include <string>

PlayerAnimationBase::PlayerAnimationBase(char * name)
{
	std::string path = std::string(name);
	path = "Graphics/" + path + ".png";
	sheetTexture = App->textures->Load(path.c_str());
	int w;
	int h;
	SDL_QueryTexture(sheetTexture, nullptr, nullptr, &w, &h);
	sheetRect = new SDL_Rect();
	sheetRect->x = 0;
	sheetRect->y = 500;
	sheetRect->w = w;
	sheetRect->h = 130;

	for (int i = 0; i < ANIM_NUM; ++i) animations[i] = new Animation();
}

bool PlayerAnimationBase::save()
{
	return true;
}

	bool PlayerAnimationBase::load()
{
	return true;
}
