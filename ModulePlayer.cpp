#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
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

	charging.frames.push_back({ 241, 1549, 95, 90 });
	charging.frames.push_back({ 242, 1549, 95, 90 });
	charging.frames.push_back({ 240, 1549, 95, 90 });
	charging.speed = 0.3f;
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
	bool chargingKame = false;
	if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_REPEAT) {
		App->renderer->Blit(graphics, (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f, 120, &(charging.GetCurrentFrame()));				
		chargingKame = true;
	}
	if (!chargingKame)
	{
		int speed = 4;

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			App->renderer->camera.y += speed;

		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			App->renderer->camera.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
			App->renderer->camera.x += speed;

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
			App->renderer->camera.x -= speed;

		if (App->renderer->camera.x < lastX) // moving forward
		{
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f, 120, &(forward.GetCurrentFrame()));
		}
		else if (App->renderer->camera.x > lastX) // moving backward
		{
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f, 120, &(backward.GetCurrentFrame()));
		}
		else { //idle
			App->renderer->Blit(graphics, (SCREEN_WIDTH / 4) - App->renderer->camera.x * 0.5f, 120, &(idle.GetCurrentFrame()));
		}
	}
	lastX = App->renderer->camera.x;

	return UPDATE_CONTINUE;
}