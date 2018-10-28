#include "ModuleEditor.h"
#include "SDL/include/SDL.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "imgui/imgui.h"
#include "../Engine---Master/glew-2.1.0/include/GL/glew.h"
#include "SubModuleEditor.h"
#include "SubModuleEditorFPS.h"
#include "SubModuleEditorConsole.h"
#include "SubModuleEditorMenu.h"
#include "SubModuleEditorAnimator.h"
#include "Application.h"
#include "ModuleWindow.h"




ModuleEditor::ModuleEditor() : Module(true)
{
}


ModuleEditor::~ModuleEditor()
{
	for (std::list<SubModuleEditor*>::iterator it = editorSubmodules.begin(); it != editorSubmodules.end(); ++it)
	{
		delete (*it);
	}
}

bool ModuleEditor::Init()
{
	LOG("Loading editor");
	bool ret = true;
	editorSubmodules.push_back(new SubModuleEditorFPS());
	editorSubmodules.push_back(new SubModuleEditorMenu());
	editorSubmodules.push_back(new SubModuleEditorConsole());
	editorSubmodules.push_back(new SubModuleEditorAnimator());
	
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
	io = &ImGui::GetIO(); (void)io;

	ImGui_ImplSDL2_InitForOpenGL(App->window->editorWindow, context);
	ImGui_ImplOpenGL3_Init("#version 330");

	ImGui::StyleColorsDark();	
	return ret;
}

update_status ModuleEditor::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	App->imGuiStarted = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->editorWindow);
	ImGui::NewFrame();

	for (std::list<SubModuleEditor*>::iterator it = editorSubmodules.begin(); it != editorSubmodules.end(); ++it)
	{
		(*it)->drawSubmodule();
	}

	ImGui::Render();
	SDL_GL_MakeCurrent(App->window->editorWindow, context);
	glViewport(0, 0, (int)io->DisplaySize.x, (int)io->DisplaySize.y);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	SDL_GL_SwapWindow(App->window->editorWindow);
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{	

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
	return true;
}
