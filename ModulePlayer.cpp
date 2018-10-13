#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA
ModulePlayer::ModulePlayer(bool start_enabled) : Module(start_enabled)
{
	position.x = 100;
	position.y = 216;

	// idle animation (arcade sprite sheet)
	idle.frames.push_back({7, 14, 60, 90});
	idle.frames.push_back({95, 15, 60, 89});
	idle.frames.push_back({184, 14, 60, 90});
	idle.frames.push_back({276, 11, 60, 93});
	idle.frames.push_back({366, 12, 60, 92});
	idle.speed = 0.2f;
	
	// walk backward animation (arcade sprite sheet)
	backward.frames.push_back({542, 131, 61, 87});
	backward.frames.push_back({628, 129, 59, 90});
	backward.frames.push_back({713, 128, 57, 90});
	backward.frames.push_back({797, 127, 57, 90});
	backward.frames.push_back({883, 128, 58, 91});
	backward.frames.push_back({974, 129, 57, 89});
	backward.speed = 0.1f;

	// TODO 8: setup the walk forward animation from ryu4.png

	forward.frames.push_back({ 0, 131, 65, 90 });
	forward.frames.push_back({ 75, 129, 63, 90 });
	forward.frames.push_back({ 160, 128, 65, 90 });
	forward.frames.push_back({ 255, 127, 65, 90 });
	forward.frames.push_back({ 340, 128, 65, 91 });
	forward.frames.push_back({ 425, 129, 62, 90 });
	forward.speed = 0.1f;

	charging.frames.push_back({ 578, 1814, 95, 90 });
	charging.frames.push_back({ 242, 1549, 95, 90 });
	charging.frames.push_back({ 577, 1814, 95, 90 });
	charging.speed = 0.3f;

	kick.frames.push_back({ 0, 650, 80, 105 });
	kick.frames.push_back({ 80, 650, 80, 105 });
	kick.frames.push_back({ 160, 650, 100, 105 });
	kick.frames.push_back({ 80, 650, 80, 105 });
	kick.frames.push_back({ 0, 650, 80, 105 });
	kick.speed = 0.2f;

	punch.frames.push_back({ 245, 261, 80, 105 });
	punch.frames.push_back({ 325, 261, 84, 105 });
	punch.frames.push_back({ 426, 261, 120, 105 });
	punch.frames.push_back({ 325, 261, 84, 105 });
	punch.frames.push_back({ 245, 261, 80, 105 });
	punch.speed = 0.2f;

	kameBall.frames.push_back({ 491, 1554, 54, 51 });
	kameBall.frames.push_back({ 545, 1554, 68, 51 });
	kameBall.speed = 0.1f;

	kameRect.x = 0;
	kameRect.y = 0;
	kameRect.w = 512;
	kameRect.h = 512;

	background.x = 0;
	background.y = 0;
	background.w = 1024;
	background.h = 469;

	ryuKameRect.x = 350;
	ryuKameRect.y = 1547;
	ryuKameRect.w = 120;
	ryuKameRect.h = 92;	

}

ModulePlayer::~ModulePlayer()
{
	// Homework : check for memory leaks
}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("ryu4.png"); // arcade version
	kameEffect = App->textures->Load("effect.png");
	kameEffectCharged = App->textures->Load("effect2.png");
	blackFilter = App->textures->Load("blackFilter.png");
	blueFilter = App->textures->Load("blueFilter.png");

	alAtaquerFX = App->audio->LoadFx("alAtaque.wav");
	noPuedeSerFX = App->audio->LoadFx("noPuedeSer.wav");
	epetecanFX = App->audio->LoadFx("epetecan.wav");
	playerBusy = false;
	ryuPos = (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f;
	timer = 0;
	kameStatus = READY;

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update
update_status ModulePlayer::Update()
{
	// TODO 9: Draw the player with its animation
	// make sure to detect player movement and change its
	// position while cycling the animation(check Animation.h)
	if (SDL_GetTicks() < timer) { //ryu is doing something
		switch (ryuAction)
		{
			case KAME:
				App->renderer->Blit(graphics, ryuPos - 5, 120, &ryuKameRect);
				break;
			case KICK:
				if (!kick.isFinished())
					App->renderer->Blit(graphics, ryuPos, 110, &(kick.GetCurrentFrame()));
				else
					timer = SDL_GetTicks();
				break;
			case PUNCH:
				if (!punch.isFinished())
					App->renderer->Blit(graphics, ryuPos, 110, &(punch.GetCurrentFrame()));
				else
					timer = SDL_GetTicks();
				break;
		}
	}
	else { //ryu controls
		playerBusy = false;
		if ((kameStatus == READY || kameStatus == RELEASED) && App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		{
			ryuAction = KICK;
			kameStatus = READY;
			timer = SDL_GetTicks() + 1000;
			kick.reset();
			playerBusy = true;
		}
		if ((kameStatus == READY || kameStatus == RELEASED) && App->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		{
			ryuAction = PUNCH;
			kameStatus = READY;
			timer = SDL_GetTicks() + 1000;
			punch.reset();
			playerBusy = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN)
		{
			kameSpeed = 0;
			kameAngle = 0;
			kameStatus = CHARGING;
			App->audio->PlayFx(alAtaquerFX);
		}
		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_UP)
		{
			if (kameStatus == CHARGED)
			{
				App->audio->PlayFx(epetecanFX);
				timer = SDL_GetTicks() + 1000;
				ryuAction = KAME;
				kameStatus = RELEASED;
				kamePos = ryuPos + 90;
				playerBusy = true;
			}
			else if (kameStatus == CHARGING)
			{
				App->audio->PlayFx(noPuedeSerFX);
				playerBusy = false;
				kameStatus = READY;
			}
		}

		if ((kameStatus == CHARGED || kameStatus == CHARGING) && App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT) {
			if (kameSpeed < 5) kameSpeed += 0.04f;
			else kameStatus = CHARGED;
			kameAngle += kameSpeed;
			App->renderer->Blit(blackFilter, 0, 0, &background);
			App->renderer->Blit(graphics, ryuPos, 120, &(charging.GetCurrentFrame()));			
			App->renderer->Blit(kameEffect, ryuPos - 240, -102, &kameRect, 1.0f, kameAngle);
			if (kameStatus == CHARGED && (rand() % 100 > 50)) App->renderer->Blit(kameEffectCharged, ryuPos - 240, -102, &kameRect, 1.0f, kameAngle);
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
				if (ryuPos > LEFT_BOUND)
					ryuPos -= speed * 0.5f;
				if (ryuPos <= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
					App->renderer->camera.x += speed;			
			}
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			{
				if (ryuPos < -RIGHT_BOUND)
					ryuPos += speed * 0.5f;
				if (ryuPos >= (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f)
					App->renderer->camera.x -= speed;
			}
			if (ryuPos < lastX) // moving forward
			{
				App->renderer->Blit(graphics, ryuPos, 120, &(forward.GetCurrentFrame()));
			}
			else if (ryuPos > lastX) // moving backward
			{
				App->renderer->Blit(graphics, ryuPos, 120, &(backward.GetCurrentFrame()));
			}
			else { //idle
				App->renderer->Blit(graphics, ryuPos, 120, &(idle.GetCurrentFrame()));
			}
			lastX = ryuPos;
		}
	}
	if (kameStatus == RELEASED) {
		kamePos += 4;
		App->renderer->Blit(graphics, kamePos, 130, &(kameBall.GetCurrentFrame()));
	}
	return UPDATE_CONTINUE;
}