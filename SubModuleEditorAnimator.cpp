#include "SubModuleEditorAnimator.h"
#include "Application.h"
#include "ModuleRender.h"
#include "PlayerAnimationBase.h"
#include "ModulePlayer.h"
#include "imgui.h"
#include "SDL/include/SDL.h"
#include <algorithm>

SubModuleEditorAnimator::SubModuleEditorAnimator()
{
	strcpy(status, "OK");
	strcpy(sheetName, "");
	strcpy(filename, "default.anm");
}


SubModuleEditorAnimator::~SubModuleEditorAnimator()
{
	if (animSheet != nullptr)
		delete animSheet;
}

bool SubModuleEditorAnimator::drawSubmodule()
{	
	if (ImGui::CollapsingHeader("Animation Editor"))
	{	
		ImGui::Checkbox("Active", &active);
		if (!active) {
			return true;
		}
		ImGui::SameLine();
		ImGui::Checkbox("Loop Animations", &loopAnimations);
		ImGui::Text(status);
		if (ImGui::Button("New", ImVec2(187,50))) {
			if (sheetName[0] == '\0')
			{
				strcpy(status, "Enter the name of the texture sheet file.");
			}
			else
			{
				if (animSheet != nullptr)
					delete animSheet; 
				animSheet = new PlayerAnimationBase(sheetName, ok);
				if (!ok)
					strcpy(status, "Error loading texture sheet.");
				else
					strcpy(status, "New animation object ready.");
			}				
		}

		ImGui::SameLine();
		if (ImGui::Button("Save", ImVec2(187, 50))) {
			if (!ok)
			{
				strcpy(status, "No data loaded to save.");
			}
			else if (filename[0] == '\0')
			{
				strcpy(status, "Enter the name of the animation file.");
			}
			else
			{
				animSheet->save(filename);
				strcpy(status, "File saved.");
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("Load", ImVec2(187, 50))) { //TODO:Fix memory leak
			if (filename[0] == '\0')
			{
				strcpy(status, "Enter the name of the animation file.");
			}
			else
			{
				strcpy(status, "OK");
				if (animSheet != nullptr)
					delete animSheet; 
				animSheet = new PlayerAnimationBase(sheetName, ok);
				
				ok = animSheet->load(filename);
				if (!ok)
					strcpy(status, "Error loading animation file sheet.");
				else
				{
					strcpy(status, "File loaded.");
					strcpy(sheetName, animSheet->sheetFileName);
				}
				
			}
		}
		ImGui::InputText("File name", filename, 50);		
		ImGui::InputText("TextureSheet File name", sheetName, 50);
		if (animSheet == nullptr || !ok)
			return true;
		ImGui::SliderInt("Low cut of animation sequence", &animSheet->sheetRect->h, 10, 200);
		ImGui::PushItemWidth(196.f);
		ImGui::InputInt("Gizmo x", &gizmoX);
		ImGui::SameLine();
		ImGui::InputInt("Gizmo y", &gizmoY);
		ImGui::SameLine();
		ImGui::InputInt("Gizmo size", &gizmoSize);
		ImGui::PopItemWidth();
		for (int i = 0; i < ANIM_NUM; ++i) {
			if (ImGui::TreeNode(animSheet->ANIM_NAMES[i]))
			{		
				if (ImGui::Button("Play animation"))
				{
					std::string message = "Playing animation " + std::string(animSheet->ANIM_NAMES[i]);
					currentAnimation = i;
					strcpy(status, message.c_str());
					LOG(message.c_str());
				}
				ImGui::SameLine();
				if (ImGui::Button("Stop animation"))
				{
					std::string message = "Stopped animation " + std::string(animSheet->ANIM_NAMES[i]);
					currentAnimation = -1;
					strcpy(status, message.c_str());
					LOG(message.c_str());
				}
				ImGui::InputInt("# of frames", &animSheet->animations[i]->frameNum);
				ImGui::InputInt("Frame width(Auto calculation)", &animSheet->animations[i]->frameWidth);
				ImGui::InputFloat("Animation speed", &animSheet->animations[i]->speed);
				ImGui::PushItemWidth(190.f);
				ImGui::InputInt("First Frame x", &animSheet->sheetRect->x);
				animSheet->sheetRect->x = std::clamp(animSheet->sheetRect->x, 0, animSheet->sheetWidth);
				ImGui::SameLine();
				ImGui::InputInt("First Frame y", &animSheet->sheetRect->y);
				animSheet->sheetRect->y = std::clamp(animSheet->sheetRect->y, 0, animSheet->sheetHeight);
				ImGui::PopItemWidth();
				ImGui::Checkbox("Is Loop", &animSheet->animations[i]->isLoop);

				if (ImGui::Button("Auto calculate"))
				{
					std::string message = "Auto calculating frames for " + std::string(animSheet->ANIM_NAMES[i]);
					LOG(message.data());
				}
				if (animSheet->animations[i]->frameNum > 0 && animSheet->animations[i]->frameNum != animSheet->animations[i]->frames.size()) {
					animSheet->animations[i]->frames.resize(animSheet->animations[i]->frameNum);
					animSheet->animations[i]->headColliders.resize(animSheet->animations[i]->frameNum);
					animSheet->animations[i]->bodyColliders.resize(animSheet->animations[i]->frameNum);
					animSheet->animations[i]->legsColliders.resize(animSheet->animations[i]->frameNum);
					animSheet->animations[i]->damageColliders.resize(animSheet->animations[i]->frameNum);
					for (int j = 0; j < animSheet->animations[i]->frames.size(); ++j)
						if (animSheet->animations[i]->frames[j] == nullptr)
						{
							animSheet->animations[i]->frames[j] = new SDL_Rect({ 0,0,0,0 });
							animSheet->animations[i]->headColliders[j] = new SDL_Rect({ 0,0,0,0 });
							animSheet->animations[i]->bodyColliders[j] = new SDL_Rect({ 0,0,0,0 });
							animSheet->animations[i]->legsColliders[j] = new SDL_Rect({ 0,0,0,0 });
							animSheet->animations[i]->damageColliders[j] = new SDL_Rect({ 0,0,0,0 });
						}
				}
				//TODO:free and delete frames erased from vector??
				for (int j = 0; j < animSheet->animations[i]->frameNum; ++j)
				{
					
					char buffer[50];
					char buffer2[50];
					strcpy(buffer, "Frame ");
					strcat(buffer, itoa(j, buffer2, 10));
					if (ImGui::TreeNode(buffer)) {						
						ImGui::PushItemWidth(100.f);
						ImGui::InputInt("x", &animSheet->animations[i]->frames[j]->x);
						ImGui::SameLine();
						ImGui::InputInt("y", &animSheet->animations[i]->frames[j]->y);
						ImGui::InputInt("w", &animSheet->animations[i]->frames[j]->w);
						ImGui::SameLine();
						ImGui::InputInt("h", &animSheet->animations[i]->frames[j]->h);
						
						if (ImGui::TreeNode("Head collider"))
						{
							ImGui::InputInt("x", &animSheet->animations[i]->headColliders[j]->x);
							ImGui::SameLine();
							ImGui::InputInt("y", &animSheet->animations[i]->headColliders[j]->y);
							ImGui::InputInt("w", &animSheet->animations[i]->headColliders[j]->w);
							ImGui::SameLine();
							ImGui::InputInt("h", &animSheet->animations[i]->headColliders[j]->h);
							ImGui::TreePop();
						}

						if (ImGui::TreeNode("Body collider"))
						{
							ImGui::InputInt("x", &animSheet->animations[i]->bodyColliders[j]->x);
							ImGui::SameLine();
							ImGui::InputInt("y", &animSheet->animations[i]->bodyColliders[j]->y);
							ImGui::InputInt("w", &animSheet->animations[i]->bodyColliders[j]->w);
							ImGui::SameLine();
							ImGui::InputInt("h", &animSheet->animations[i]->bodyColliders[j]->h);
							ImGui::TreePop();
						}

						if (ImGui::TreeNode("Legs collider"))
						{
							ImGui::InputInt("x", &animSheet->animations[i]->legsColliders[j]->x);
							ImGui::SameLine();
							ImGui::InputInt("y", &animSheet->animations[i]->legsColliders[j]->y);
							ImGui::InputInt("w", &animSheet->animations[i]->legsColliders[j]->w);
							ImGui::SameLine();
							ImGui::InputInt("h", &animSheet->animations[i]->legsColliders[j]->h);
							ImGui::TreePop();
						}

						if (ImGui::TreeNode("Damage collider"))
						{
							ImGui::InputInt("x", &animSheet->animations[i]->damageColliders[j]->x);
							ImGui::SameLine();
							ImGui::InputInt("y", &animSheet->animations[i]->damageColliders[j]->y);
							ImGui::InputInt("w", &animSheet->animations[i]->damageColliders[j]->w);
							ImGui::SameLine();
							ImGui::InputInt("h", &animSheet->animations[i]->damageColliders[j]->h);
							ImGui::TreePop();
						}
						ImGui::PopItemWidth();
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}

	}
	if (active) {
		App->renderer->Blit(animSheet->sheetTexture, 0, 0, animSheet->sheetRect);		
		SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 255);
		int x1 = 0;
		int x2 = animSheet->sheetRect->w;
		int y1 = /*animSheet->sheetRect->y + */animSheet->sheetRect->h * SCREEN_SIZE;
		int y2 = y1;
		SDL_RenderDrawLine(App->renderer->renderer, x1, y1, x2, y2);
		if (currentAnimation >= 0 && animSheet->animations[currentAnimation] != nullptr && animSheet->animations[currentAnimation]->frameNum > 0)
			App->renderer->Blit(animSheet->sheetTexture, 100, 220, animSheet->animations[currentAnimation]->GetCurrentFrame(), 1.0f, false);
		SDL_RenderDrawLine(App->renderer->renderer, gizmoX, gizmoY, gizmoX + gizmoSize, gizmoY);
		SDL_RenderDrawLine(App->renderer->renderer, gizmoX + gizmoSize / 2, gizmoY, gizmoX + gizmoSize / 2, gizmoY - gizmoSize);
	}
	return true;
}
