#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneHonda.h"
#include "SDL/include/SDL.h"


ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 393;
	ground.w = 849;
	ground.h = 69;

	background.x = 125;
	background.y = 177;
	background.w = 667;
	background.h = 130;

	side.x = 118;
	side.y = 156;
	side.w = 81;
	side.h = 187;

	ceiling.x = 79;
	ceiling.y = 0;
	ceiling.w = 782;
	ceiling.h = 60;

	pool.x = 310;
	pool.y = 311;
	pool.w = 339;
	pool.h = 58;

	water.frames.push_back({ 8, 448, 284, 8 });
	water.frames.push_back({ 296, 448, 284, 12 });
	water.frames.push_back({ 588, 448, 284, 19 });
	water.speed = 0.1f;

	fuji.frames.push_back({224, 64, 224, 104});
	fuji.frames.push_back({ 456, 64, 224, 104 });	
	fuji.speed = 0.05f;

}


ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");
	graphics = App->textures->Load("honda_stage.png");
	App->player->Enable();
	App->audio->PlayMusic("honda.ogg");
	return true;
}

update_status ModuleSceneHonda::Update()
{	
	App->renderer->Blit(graphics, -85, 178, &ground, 0.9f);	
	App->renderer->Blit(graphics, -50, 48, &background, 0.55f);	
	App->renderer->Blit(graphics, 137, 55, &(fuji.GetCurrentFrame()), 0.55f);
	App->renderer->Blit(graphics, -57, 28, &side, 0.55f);
	App->renderer->Blit(graphics, 90, 121, &pool, 0.6f);
	App->renderer->Blit(graphics, 116, 134, &(water.GetCurrentFrame()), 0.6f);
	App->renderer->Blit(graphics, -120, -8, &ceiling, 0.69f);
	return UPDATE_CONTINUE;
}

bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();

	return true;
}
