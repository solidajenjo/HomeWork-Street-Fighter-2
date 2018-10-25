#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include<vector>
#include "Globals.h"
#include "Module.h"
#include "imgui.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModuleSceneKen;
class ModuleSceneHonda;
class PlayerAnimationBase;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;
	ModulePlayer* player;
	ModuleSceneKen* scene_ken;
	ModuleSceneHonda* scene_honda;
	Module* currentScene;	

	ImGuiTextBuffer consoleBuffer;
	bool imGuiStarted = false;
	std::vector<float> fpsLog = std::vector<float>(50);
	std::vector<float> msLog = std::vector<float>(50);
	int fpsLogIterator = 0;

private:

	std::list<Module*> modules;

};

extern Application* App;

#endif // __APPLICATION_CPP__