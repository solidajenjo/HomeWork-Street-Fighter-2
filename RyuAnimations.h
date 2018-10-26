#pragma once
#include "PlayerAnimationBase.h"


class RyuAnimations :
	public PlayerAnimationBase
{
public:
	RyuAnimations(char* name);
	~RyuAnimations();

	bool setUp();
};

