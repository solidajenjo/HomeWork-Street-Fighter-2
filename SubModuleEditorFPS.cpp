#include "SubModuleEditorFPS.h"
#include "Application.h"
#include "imgui.h"

SubModuleEditorFPS::SubModuleEditorFPS()
{
}


SubModuleEditorFPS::~SubModuleEditorFPS()
{
}

bool SubModuleEditorFPS::drawSubmodule()
{	
	if (ImGui::TreeNode("Performance"))
	{		
		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", App->fpsLog[App->fpsLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &App->fpsLog[0], App->fpsLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %0.1f", App->msLog[App->msLog.size() - 1]);
		ImGui::PlotHistogram("##milliseconds", &App->msLog[0], App->msLog.size(), 0, title, 0.0f, 100.0f, ImVec2(310, 100));
		ImGui::TreePop();
	}
	return true;
}
