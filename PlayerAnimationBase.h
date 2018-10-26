#ifndef __PLAYER_ANIMATION_BASE_H
#define __PLAYER_ANIMATION_BASE_H

#include <vector>
struct SDL_Rect;
struct SDL_Texture;
class Animation;

class PlayerAnimationBase
{
public:
	//methods
	PlayerAnimationBase(char* name);
	
	~PlayerAnimationBase() {};

	virtual bool setUp() {
		return true;
	};

	bool save();
	bool load();

	//members
	SDL_Texture* graphics = nullptr;
	SDL_Texture* sheetTexture = nullptr;

	SDL_Rect* sheetRect;
	
	//34 ANIMATIONS
	std::vector<Animation*> animations = std::vector<Animation*>(34);
	char* name;

	char* ANIM_NAMES[34] = { "IDLE","WALK","JUMP","FORWARD_JUMP","CROUCH","BLOCKING","BLOCKING_CROUCH",
		"L_PUNCH","M_PUNCH","H_PUNCH","F_L_PUNCH","F_M_PUNCH","F_J_PUNCH","L_KICK","M_KICK","H_KICK",
		"F_L_KICK","F_M_KICK","F_H_KICK","C_L_PUNCH","C_M_PUNCH","C_H_PUNCH","C_L_KICK","C_M_KICK",
		"C_H_KICK","J_PUNCH","J_KICK","SPECIAL_1","SPECIAL_2","HIT","FACE_HIT","CROUCH_HIT","KNOCK_DOWN",
		"VICTORY" };
	//TODO: Remove old animations
	Animation* idle;
	Animation* backward;
	Animation* forward;
	Animation* kick;
	Animation* punch;
	Animation* special;
	
	SDL_Rect* playerSpecialRect;
	SDL_Rect* specialRect;
	SDL_Rect* background;
};
#endif
