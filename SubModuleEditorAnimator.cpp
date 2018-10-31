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
				{
					strcpy(status, "New animation object ready.");
					ySheet = animSheet->sheetHeight;
					animSheet->sheetRect->h = animSheet->sheetHeight;
				}
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
		if (ImGui::Button("Load", ImVec2(187, 50))) { 
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
					strcpy(sheetName, &animSheet->sheetFileName[0]);
					ySheet = animSheet->sheetHeight;
					animSheet->sheetRect->h = animSheet->sheetHeight;
				}
				
			}
		}
		ImGui::InputText("File name", filename, 50);		
		ImGui::InputText("TextureSheet File name", sheetName, 50);
		if (animSheet == nullptr || !ok)
			return true;		
		ImGui::PushItemWidth(196.f);
		ImGui::InputInt("Gizmo x", &gizmoX);
		ImGui::SameLine();
		ImGui::InputInt("Gizmo y", &gizmoY);
		ImGui::SameLine();
		ImGui::InputInt("Gizmo size", &gizmoSize);
		ImGui::PopItemWidth();
		ImVec2 pos = ImGui::GetCursorScreenPos();
		pos.y += 10;
		ImGui::SetCursorScreenPos(pos);
		ImGui::ListBox("Animation", &currentAnimation, animSheet->ANIM_NAMES, ANIM_NUM);
		pos = ImGui::GetCursorScreenPos();
		pos.y += 10;
		ImGui::SetCursorScreenPos(pos);
		int i = currentAnimation;
		if (ImGui::Button("Play animation"))
		{
			std::string message = "Playing animation " + std::string(animSheet->ANIM_NAMES[i]);					
			loopAnimations = true;
			strcpy(status, message.c_str());
			LOG(message.c_str());
		}
		ImGui::SameLine();
		if (ImGui::Button("Stop animation"))
		{
			std::string message = "Stopped animation " + std::string(animSheet->ANIM_NAMES[i]);					
			strcpy(status, message.c_str());
			loopAnimations = false;
			LOG(message.c_str());
		}
		ImGui::SliderInt("Frame", &currentFrame, 0, animSheet->animations[i]->frameNum - 1);
		ImGui::InputInt("# of frames", &animSheet->animations[i]->frameNum);
		animSheet->animations[i]->frameNum = std::clamp(animSheet->animations[i]->frameNum, 1, 20);
		ImGui::InputInt("Frame width(Auto calculation)", &animSheet->animations[i]->frameWidth);
		ImGui::InputFloat("Animation speed", &animSheet->animations[i]->speed);
		ImGui::PushItemWidth(190.f);
		ImGui::InputInt("First Frame x", &xSheet);
		animSheet->sheetRect->x = std::clamp(animSheet->sheetRect->x, 0, animSheet->sheetWidth);
		ImGui::SameLine();
		ImGui::InputInt("First Frame y", &ySheet);
		animSheet->sheetRect->y = std::clamp(animSheet->sheetRect->y, 0, animSheet->sheetHeight);
		ImGui::PopItemWidth();
		ImGui::SliderInt("Low cut of animation sequence", &lowCut, 10, animSheet->sheetHeight);
		ImGui::Checkbox("Is Loop", &animSheet->animations[i]->isLoop);

		if (ImGui::Button("Auto calculate"))
		{
			std::string message = "Auto calculating frames for " + std::string(animSheet->ANIM_NAMES[i]);
			LOG(message.c_str());
			int frameWidth = animSheet->animations[i]->frameWidth;
			int frameHeight = animSheet->sheetRect->h;
			int xStart = -xSheet;
			int yStart = ySheet - animSheet->sheetRect->h;
			for (int ii = 0; ii < animSheet->animations[i]->frameNum; ++ii) {
				animSheet->animations[i]->frames[ii]->x = ii * frameWidth + xStart;
				animSheet->animations[i]->frames[ii]->y = -yStart;
				animSheet->animations[i]->frames[ii]->w = frameWidth;
				animSheet->animations[i]->frames[ii]->h = lowCut;
			}
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
			
		ImGui::PushItemWidth(100.f);
		ImGui::InputInt("x", &animSheet->animations[i]->frames[currentFrame]->x);
		ImGui::SameLine();
		ImGui::InputInt("y", &animSheet->animations[i]->frames[currentFrame]->y);
		ImGui::InputInt("w", &animSheet->animations[i]->frames[currentFrame]->w);
		ImGui::SameLine();
		ImGui::InputInt("h", &animSheet->animations[i]->frames[currentFrame]->h);

		if (ImGui::TreeNode("Head collider"))
		{
			ImGui::InputInt("x", &animSheet->animations[i]->headColliders[currentFrame]->x);
			ImGui::SameLine();
			ImGui::InputInt("y", &animSheet->animations[i]->headColliders[currentFrame]->y);
			ImGui::InputInt("w", &animSheet->animations[i]->headColliders[currentFrame]->w);
			ImGui::SameLine();
			ImGui::InputInt("h", &animSheet->animations[i]->headColliders[currentFrame]->h);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Body collider"))
		{
			ImGui::InputInt("x", &animSheet->animations[i]->bodyColliders[currentFrame]->x);
			ImGui::SameLine();
			ImGui::InputInt("y", &animSheet->animations[i]->bodyColliders[currentFrame]->y);
			ImGui::InputInt("w", &animSheet->animations[i]->bodyColliders[currentFrame]->w);
			ImGui::SameLine();
			ImGui::InputInt("h", &animSheet->animations[i]->bodyColliders[currentFrame]->h);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Legs collider"))
		{
			ImGui::InputInt("x", &animSheet->animations[i]->legsColliders[currentFrame]->x);
			ImGui::SameLine();
			ImGui::InputInt("y", &animSheet->animations[i]->legsColliders[currentFrame]->y);
			ImGui::InputInt("w", &animSheet->animations[i]->legsColliders[currentFrame]->w);
			ImGui::SameLine();
			ImGui::InputInt("h", &animSheet->animations[i]->legsColliders[currentFrame]->h);
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Damage collider"))
		{
			ImGui::InputInt("x", &animSheet->animations[i]->damageColliders[currentFrame]->x);
			ImGui::SameLine();
			ImGui::InputInt("y", &animSheet->animations[i]->damageColliders[currentFrame]->y);
			ImGui::InputInt("w", &animSheet->animations[i]->damageColliders[currentFrame]->w);
			ImGui::SameLine();
			ImGui::InputInt("h", &animSheet->animations[i]->damageColliders[currentFrame]->h);
			ImGui::TreePop();
		}
		ImGui::PopItemWidth();
	}
	if (active) {
		App->renderer->Blit(animSheet->sheetTexture, xSheet * SCREEN_SIZE, ySheet * SCREEN_SIZE, animSheet->sheetRect);
		SDL_SetRenderDrawColor(App->renderer->renderer, 0, 0, 0, 255);
		
		SDL_Surface* blackBox = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 32, 0, 0, 0, 0);
		SDL_FillRect(blackBox, NULL, SDL_MapRGB(blackBox->format, 0, 0, 0));
		SDL_FreeSurface(blackBox);
		SDL_Rect blackBoxRect = { 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 };
		SDL_RenderFillRect(App->renderer->renderer, &blackBoxRect);

		SDL_SetRenderDrawColor(App->renderer->renderer, 255, 0, 0, 255);
		int x1 = 0;
		int x2 = animSheet->sheetRect->w * SCREEN_SIZE;
		int y1 = lowCut * SCREEN_SIZE;
		int y2 = y1;
		SDL_RenderDrawLine(App->renderer->renderer, x1, y1, x2, y2);
		if (loopAnimations  && animSheet->animations[currentAnimation] != nullptr && animSheet->animations[currentAnimation]->frameNum > 0)
			App->renderer->Blit(animSheet->sheetTexture, xFrame * SCREEN_SIZE, gizmoY, animSheet->animations[currentAnimation]->GetCurrentFrame(), 1.0f, false);
		else
		{
			if (animSheet->animations[currentAnimation] != nullptr && animSheet->animations[currentAnimation]->frameNum > 0)
			{
				App->renderer->Blit(animSheet->sheetTexture, xFrame * SCREEN_SIZE, gizmoY, animSheet->animations[currentAnimation]->frames[currentFrame], 1.0f, false);
			}
		}
		SDL_RenderDrawLine(App->renderer->renderer, gizmoX, gizmoY, gizmoX + gizmoSize, gizmoY);
		SDL_RenderDrawLine(App->renderer->renderer, gizmoX + gizmoSize / 2, gizmoY, gizmoX + gizmoSize / 2, gizmoY - gizmoSize);
	}
	return true;
}
