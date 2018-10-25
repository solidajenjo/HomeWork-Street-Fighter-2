#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "../Engine---Master/glew-2.1.0/include/GL/glew.h"
#include "SubModuleEditor.h"
#include "SubModuleEditorFPS.h"
#include "SubModuleEditorConsole.h"
#include "SubModuleEditorMenu.h"


ModuleRender::ModuleRender()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH * SCREEN_SIZE;
	camera.h = SCREEN_HEIGHT* SCREEN_SIZE;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	editorSubmodules.push_back(new SubModuleEditorFPS());
	editorSubmodules.push_back(new SubModuleEditorMenu());
	editorSubmodules.push_back(new SubModuleEditorConsole());
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}


	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == nullptr)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->window->editorWindow);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		LOG("Error initializating GLEW");
		ret = false;
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(App->window->editorWindow, context);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();

	return ret;
}

update_status ModuleRender::PreUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->editorWindow);
	ImGui::NewFrame();

	for (std::list<SubModuleEditor*>::iterator it = editorSubmodules.begin(); it != editorSubmodules.end(); ++it)
	{
		(*it)->drawSubmodule();
	}

	ImGui::Render();
	SDL_GL_MakeCurrent(App->window->editorWindow, context);
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->editorWindow);

	SDL_RenderPresent(renderer);

	App->imGuiStarted = true;
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");
	

	//Destroy window
	if(renderer != nullptr)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool flip)
{
	bool ret = true;
	SDL_Rect rect;

	//Bounds contraints
	if (camera.x > LEFT_BOUND) camera.x = LEFT_BOUND;
	if (camera.x < RIGHT_BOUND) camera.x = RIGHT_BOUND;

	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	if (SDL_RenderCopyEx(renderer, texture, section, &rect, 0, nullptr, flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) != 0)	
	{
		LOG("Cannot blit to screen. SDL_RenderCopyEx error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}
