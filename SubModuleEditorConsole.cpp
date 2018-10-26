#include "SubModuleEditorConsole.h"
#include "Application.h"
#include "imgui.h"

SubModuleEditorConsole::SubModuleEditorConsole()
{
}


SubModuleEditorConsole::~SubModuleEditorConsole()
{
}

bool SubModuleEditorConsole::drawSubmodule()
{	
	if (ImGui::CollapsingHeader("Console"))
	{		
		ImGui::TextUnformatted(App->consoleBuffer.begin());
	}
	return true;
}
