#ifndef _MODULE_EDITOR_H
#define _MODULE_EDITOR_H

#include "Globals.h"
#include "Module.h"
#include <list>

typedef void *SDL_GLContext;
struct ImGuiIO;
class SubModuleEditor;

class ModuleEditor :
	public Module
{
public:
//methods
	ModuleEditor();
	~ModuleEditor();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
//members
	std::list<SubModuleEditor*> editorSubmodules;
	
private:
	SDL_GLContext context;
	ImGuiIO* io;
};

#endif

