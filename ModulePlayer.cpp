#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "PlayerAnimationBase.h"
#include "RyuAnimations.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{

}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Init()
{
	LOG("Loading player");

	playerBusy = false;
	playerPos = (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f;
	timer = 0;
	flipped = false;

	animSheet = new RyuAnimations("ryu");
	animSheet->setUp();

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(animSheet->graphics);
	//TODO Clean memory
	/*
	delete animSheet->forward;
	delete animSheet->backward;
	delete animSheet;
	*/
	return true;
}

// Update
update_status ModulePlayer::Update()
{
	if (!App->playerActivated) return UPDATE_CONTINUE;
	if (SDL_GetTicks() < timer) { //player is doing something
		switch (playerAction)
		{			
			case SPECIAL:
				App->renderer->Blit(animSheet->graphics, playerPos - 25, 120, animSheet->playerSpecialRect, 1.0f, flipped);
				break;
			case KICK:
				App->renderer->Blit(animSheet->graphics, playerPos - 20, 110, animSheet->kick->GetCurrentFrame(), 1.0f, flipped);
				break;
			case PUNCH:
				App->renderer->Blit(animSheet->graphics, playerPos - 20, 110, animSheet->punch->GetCurrentFrame(), 1.0f, flipped);
				break;			
			default:
				break;
		}
	}
	else {
		playerBusy = false;
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
			flipped = !flipped;
			Animation* aux = animSheet->forward;
			animSheet->forward = animSheet->backward;
			animSheet->backward = aux;
		}
		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
			timer = SDL_GetTicks() + 500;
			playerAction = SPECIAL;			
			kamePos = playerPos + 90;
			playerBusy = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		{
			playerAction = KICK;			
			timer = SDL_GetTicks() + 500;
			animSheet->kick->reset();
			playerBusy = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		{
			playerAction = PUNCH;			
			timer = SDL_GetTicks() + 500;
			animSheet->punch->reset();
			playerBusy = true;
		}
		if (!playerBusy)
		{
			/*
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
				App->renderer->camera.y += speed;

			if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
				App->renderer->camera.y -= speed;
			*/
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			{
				if (playerPos > LEFT_BOUND)
					playerPos -= speed * 0.5f;
				if (playerPos <= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
					App->renderer->camera.x += speed;
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				if (playerPos < -RIGHT_BOUND)
					playerPos += speed * 0.5f;
				if (playerPos >= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
					App->renderer->camera.x -= speed;
			}
			if (playerPos < lastX) // moving forward
			{
				App->renderer->Blit(animSheet->graphics, playerPos, 120, animSheet->forward->GetCurrentFrame(), 1.0f, flipped);
			}
			else if (playerPos > lastX) // moving backward
			{
				App->renderer->Blit(animSheet->graphics, playerPos, 120, animSheet->backward->GetCurrentFrame(), 1.0f, flipped);
			}
			else { //idle
				App->renderer->Blit(animSheet->graphics, playerPos, 120, animSheet->idle->GetCurrentFrame(), 1.0f, flipped);
			}		
		}
	}
	lastX = playerPos;	
	
	return UPDATE_CONTINUE;
}