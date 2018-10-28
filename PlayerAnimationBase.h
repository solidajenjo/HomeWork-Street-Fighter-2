#ifndef __PLAYER_ANIMATION_BASE_H
#define __PLAYER_ANIMATION_BASE_H

#include <vector>
#include "Globals.h"

struct SDL_Rect;
struct SDL_Texture;
class Animation;

class PlayerAnimationBase
{
public:
	//methods
	PlayerAnimationBase(const char* name, bool& ok);
	
	~PlayerAnimationBase();

	bool setUp(const char* name);
	bool save(const char* filename) const;
	bool load(const char* filename);

	//members
	SDL_Texture* sheetTexture = nullptr;
	SDL_Rect* sheetRect = nullptr;

	int sheetWidth;
	int sheetHeight;

	//34 ANIMATIONS
	std::vector<Animation*> animations = std::vector<Animation*>(ANIM_NUM);
	char* name = nullptr;
	char sheetFileName[50];

	char* ANIM_NAMES[ANIM_NUM] = { "IDLE","WALK","JUMP","FORWARD_JUMP","CROUCH","BLOCKING","BLOCKING_CROUCH",
		"L_PUNCH","M_PUNCH","H_PUNCH","F_L_PUNCH","F_M_PUNCH","F_J_PUNCH","L_KICK","M_KICK","H_KICK",
		"F_L_KICK","F_M_KICK","F_H_KICK","C_L_PUNCH","C_M_PUNCH","C_H_PUNCH","C_L_KICK","C_M_KICK",
		"C_H_KICK","J_PUNCH","J_KICK","SPECIAL_1","SPECIAL_2","HIT","FACE_HIT","CROUCH_HIT","KNOCK_DOWN",
		"VICTORY" };

	//TODO: Remove old animations

};
#endif
