#include "SubModuleEditorAnimator.h"
#include "Application.h"
#include "ModuleRender.h"
#include "PlayerAnimationBase.h"
#include "ModulePlayer.h"
#include "imgui.h"
#include "SDL/include/SDL.h"

SubModuleEditorAnimator::SubModuleEditorAnimator()
{
}


SubModuleEditorAnimator::~SubModuleEditorAnimator()
{
}

bool SubModuleEditorAnimator::drawSubmodule()
{	
	if (ImGui::TreeNode("Animation Editor"))
	{				
		ImGui::Checkbox("Active", &active);
		ImGui::TreePop();
	}
	if (active) {
		App->renderer->Blit(App->player->animSheet->sheetTexture, xSheet, ySheet, App->player->animSheet->sheetRect);		
	}
	return true;
}
