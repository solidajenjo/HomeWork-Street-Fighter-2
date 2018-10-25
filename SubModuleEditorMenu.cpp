#include "SubModuleEditorMenu.h"
#include "Application.h"
#include "imgui.h"

#include <Windows.h>
#include <shellapi.h>


SubModuleEditorMenu::SubModuleEditorMenu()
{	
}


SubModuleEditorMenu::~SubModuleEditorMenu()
{
}

bool SubModuleEditorMenu::drawSubmodule()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Help")) {
			
			if (ImGui::MenuItem("Documentation"))
				ShellExecuteA(NULL, "open", "https://github.com/solidajenjo/Engine---Master/wiki",
					NULL, NULL, 1);
			if (ImGui::MenuItem("Download latest"))
				ShellExecuteA(NULL, "open", "https://github.com/solidajenjo/Engine---Master",
					NULL, NULL, 1);
			if (ImGui::MenuItem("Report a bug"))
				ShellExecuteA(NULL, "open", "https://github.com/solidajenjo/Engine---Master/issues",
					NULL, NULL, 1);
					
			ImGui::EndMenu();
			
		}
		ImGui::EndMainMenuBar();
	}
	return true;
}
