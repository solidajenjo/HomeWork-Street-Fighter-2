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
}


ModuleSceneHonda::~ModuleSceneHonda()
{
}

bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");
	graphics = App->textures->Load("honda_stage.png");
	App->player->Enable();
	//App->audio->PlayMusic("honda.ogg");
	return true;
}

update_status ModuleSceneHonda::Update()
{	
	App->renderer->Blit(graphics, -85, 178, &ground, 0.9f);
	App->renderer->Blit(graphics, -50, 48, &background, 0.55f);	
	App->renderer->Blit(graphics, -57, 28, &side, 0.55f);
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
