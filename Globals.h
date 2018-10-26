#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include "SDL/include/SDL_rect.h"

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

void log(const char file[], int line, const char* format, ...);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

enum playerActions
{
	SPECIAL,
	PUNCH,
	KICK
};

enum playerAnimations
{
	IDLE = 0,
	WALK,
	JUMP,
	FORWARD_JUMP,
	CROUCH,
	BLOCKING,
	BLOCKING_CROUCH,
	L_PUNCH,
	M_PUNCH,
	H_PUNCH,
	F_L_PUNCH,
	F_M_PUNCH,
	F_J_PUNCH,
	L_KICK,
	M_KICK,
	H_KICK,
	F_L_KICK,
	F_M_KICK,
	F_H_KICK,
	C_L_PUNCH,
	C_M_PUNCH,
	C_H_PUNCH,
	C_L_KICK,
	C_M_KICK,
	C_H_KICK,
	J_PUNCH,
	J_KICK,
	SPECIAL_1,
	SPECIAL_2,
	HIT,
	FACE_HIT,
	CROUCH_HIT,
	KNOCK_DOWN,
	VICTORY
};


// Deletes a buffer
#define RELEASE( x ) \
    {\
       if( x != nullptr )\
       {\
         delete x;\
	     x = nullptr;\
       }\
    }

// Deletes an array of buffers
#define RELEASE_ARRAY( x ) \
	{\
       if( x != nullptr )\
       {\
           delete[] x;\
	       x = nullptr;\
		 }\
	 }

// Configuration -----------
#define SCREEN_WIDTH 384
#define SCREEN_HEIGHT 224
#define SCREEN_SIZE 4
#define FULLSCREEN false
#define VSYNC true
#define TITLE "Street Fighter 1.99"
#define EDITOR_TITLE "M4trix Engine"
#define EDITOR_WIDTH 600
#define EDITOR_HEIGHT SCREEN_HEIGHT * SCREEN_SIZE

#define LEFT_BOUND 0
#define RIGHT_BOUND -700
#endif //__GLOBALS_H__