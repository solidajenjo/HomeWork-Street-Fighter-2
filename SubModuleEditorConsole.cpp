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
	if (ImGui::TreeNodeEx("Console"))
	{		
		ImGui::TextUnformatted(App->consoleBuffer.begin());
		ImGui::TreePop();
	}
	return true;
}
