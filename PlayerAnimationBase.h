#ifndef __PLAYER_ANIMATION_BASE_H
#define __PLAYER_ANIMATION_BASE_H

#include "SDL/include/SDL.h"
#include "Animation.h"


class PlayerAnimationBase
{
public:
	//methods
	PlayerAnimationBase() {};
	~PlayerAnimationBase() {};

	virtual bool setUp() {
		return true;
	};

	//members
	SDL_Texture* graphics = nullptr;

	SDL_Rect playerSpecialRect;
	SDL_Rect specialRect;
	SDL_Rect background;
	Animation idle;
	Animation* backward;
	Animation* forward;
	Animation kick;
	Animation punch;
	Animation special;
	
};
#endif
