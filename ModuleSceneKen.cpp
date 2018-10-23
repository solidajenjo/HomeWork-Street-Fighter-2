#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneKen::ModuleSceneKen(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// coordinates x,y,w,h from ken_stage.png
	foreground.x = 0;
	foreground.y = 0;
	foreground.w = 530;
	foreground.h = 200;
	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.push_back({848, 208, 40, 40});
	flag.frames.push_back({848, 256, 40, 40});
	flag.frames.push_back({848, 304, 40, 40});
	flag.speed = 0.08f;

	girl.frames.push_back({ 624, 16, 32, 56 });
	girl.frames.push_back({ 624, 80, 32, 56 });
	girl.frames.push_back({ 624, 144, 32, 56 });
	girl.speed = 0.04f;

	dudes.frames.push_back({ 552, 8, 63, 70 });
	dudes.frames.push_back({ 552, 72, 63, 70 });
	dudes.frames.push_back({ 552, 136, 63, 70 });
	dudes.speed = 0.04f;

	shitFace.frames.push_back({ 664, 16, 32, 56 });
	shitFace.frames.push_back({ 664, 80, 32, 56 });
	shitFace.speed = 0.04f;

	columbus.frames.push_back({ 704, 16, 48, 56 });
	columbus.frames.push_back({ 704, 80, 48, 56 });
	columbus.frames.push_back({ 704, 144, 48, 56 });
	columbus.speed = 0.04f;

	shitMan.frames.push_back({ 760, 16, 40, 40 });
	shitMan.frames.push_back({ 760, 64, 40, 40 });
	shitMan.frames.push_back({ 760, 112, 40, 40 });
	shitMan.speed = 0.04f;

	tinkyWinky.frames.push_back({ 808, 24, 48, 32 });
	tinkyWinky.frames.push_back({ 808, 72, 48, 32 });
	tinkyWinky.frames.push_back({ 808, 120, 48, 32 });
	tinkyWinky.speed = 0.04f;

	
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");
	
	graphics = App->textures->Load("ken_stage.png");


	App->player->Enable();
	App->audio->PlayMusic("ken.ogg");
	
	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	float tideMovement = sinf(SDL_GetTicks() / 200) * 3; // movement = (ticks / frequency) * amplitude;
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, -150, 0, &background, 0.35f); // sea and sky
	App->renderer->Blit(graphics, 410, 8, &(flag.GetCurrentFrame()), 0.35f); // flag animation
	App->renderer->Blit(graphics, -30, -26 + tideMovement, &foreground, 0.5f); // foreground

	App->renderer->Blit(graphics, 170, 103 + tideMovement, &(girl.GetCurrentFrame()), 0.5f); // gril animation
	App->renderer->Blit(graphics, 106, 95 + tideMovement, &(dudes.GetCurrentFrame()), 0.5f); // dudes animation
	App->renderer->Blit(graphics, 202, 103 + tideMovement, &(shitFace.GetCurrentFrame()), 0.5f); // shitFace animation
	App->renderer->Blit(graphics, 266, 95 + tideMovement, &(columbus.GetCurrentFrame()), 0.5f); // columbus animation
	App->renderer->Blit(graphics, 65, 22 + tideMovement, &(shitMan.GetCurrentFrame()), 0.5f); // shitMan animation
	App->renderer->Blit(graphics, 106, 22 + tideMovement, &(tinkyWinky.GetCurrentFrame()), 0.5f); // shitMan animation

	App->renderer->Blit(graphics, 0, 170, &ground);

	return UPDATE_CONTINUE;
}