#include "SubModuleEditorAnimator.h"
#include "Application.h"
#include "ModuleRender.h"
#include "PlayerAnimationBase.h"
#include "ModulePlayer.h"
#include "imgui.h"
#include "SDL/include/SDL.h"
#include <string>

SubModuleEditorAnimator::SubModuleEditorAnimator()
{
}


SubModuleEditorAnimator::~SubModuleEditorAnimator()
{
}

bool SubModuleEditorAnimator::drawSubmodule()
{	
	if (ImGui::CollapsingHeader("Animation Editor"))
	{				
		ImGui::Checkbox("Active", &active);
		ImGui::SliderInt("Low cut of animation sequence", &App->player->animSheet->sheetRect->h, 10, 200);
		for (int i = 0; i < ANIM_NUM; ++i) {
			if (ImGui::TreeNode(App->player->animSheet->ANIM_NAMES[i]))
			{		
				if (ImGui::Button("Play animation"))
				{
					std::string message = "Playing animation " + std::string(App->player->animSheet->ANIM_NAMES[i]);
					LOG(message.c_str());
				}
				ImGui::InputInt("# of frames", &App->player->animSheet->animations[i]->frameNum);
				ImGui::InputInt("Frame width(Auto calculation)", &App->player->animSheet->animations[i]->frameWidth);
				if (ImGui::Button("Auto calculate"))
				{
					std::string message = "Auto calculating frames for " + std::string(App->player->animSheet->ANIM_NAMES[i]);
					LOG(message.c_str());
				}
				if (App->player->animSheet->animations[i]->frameNum != 0 && App->player->animSheet->animations[i]->frameNum != App->player->animSheet->animations[i]->frames.size()) {
					App->player->animSheet->animations[i]->frames.resize(App->player->animSheet->animations[i]->frameNum);
				}
				for (int j = 0; j < App->player->animSheet->animations[i]->frameNum; ++j)
				{
					std::string frameTitle = "Frame" + std::to_string(j);
					if (ImGui::TreeNode(frameTitle.c_str())) {
						if (App->player->animSheet->animations[i]->frames[j] == nullptr) App->player->animSheet->animations[i]->frames[j] = new SDL_Rect({ 0,0,0,0 });

						ImGui::InputInt("x", &App->player->animSheet->animations[i]->frames[j]->x);
						ImGui::InputInt("y", &App->player->animSheet->animations[i]->frames[j]->y);
						ImGui::InputInt("w", &App->player->animSheet->animations[i]->frames[j]->w);
						ImGui::InputInt("h", &App->player->animSheet->animations[i]->frames[j]->x);
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}

	}
	if (active) {
		App->renderer->Blit(App->player->animSheet->sheetTexture, xSheet, ySheet, App->player->animSheet->sheetRect);		
		SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 255);
		int x1 = 0;
		int x2 = App->player->animSheet->sheetRect->w;
		int y1 = /*App->player->animSheet->sheetRect->y + */App->player->animSheet->sheetRect->h * SCREEN_SIZE;
		int y2 = y1;
		SDL_RenderDrawLine(App->renderer->renderer, x1, y1, x2, y2);
	}
	return true;
}
