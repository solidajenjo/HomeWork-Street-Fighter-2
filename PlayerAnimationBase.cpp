#include "PlayerAnimationBase.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

PlayerAnimationBase::PlayerAnimationBase(char * name)
{
	sheetTexture = App->textures->Load("Graphics/ryu.png");		//TODO: Pick constructor name	
	int w;
	int h;
	SDL_QueryTexture(sheetTexture, nullptr, nullptr, &w, &h);
	sheetRect = new SDL_Rect();
	sheetRect->x = 0;
	sheetRect->y = 0;
	sheetRect->w = w;
	sheetRect->h = h;
}

bool PlayerAnimationBase::save()
{
	return true;
}

	bool PlayerAnimationBase::load()
{
	return true;
}
