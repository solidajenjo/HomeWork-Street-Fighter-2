#include "PlayerAnimationBase.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "Animation.h"
#include <string>


PlayerAnimationBase::PlayerAnimationBase(const char * name, bool &ok)
{
	ok = true;
	if (name == 0) //TDOD: Fix this shit
		return;
	ok = setUp(name);
}

PlayerAnimationBase::~PlayerAnimationBase()
{
	for (int i = 0; i < animations.size(); ++i) {
		delete (animations[i]);
	}

	if (sheetRect != nullptr)
		delete sheetRect;
	App->textures->Unload(sheetTexture);
}

bool PlayerAnimationBase::setUp(const char * name)
{
	if (*name == 0)
		return false;
	std::string path = std::string(name);
	path = "Graphics/" + path;
	
	strcpy(&sheetFileName[0], name);
	App->textures->Unload(sheetTexture); //memory leak when loading file fix
	sheetTexture = App->textures->Load(path.c_str());
	if (sheetTexture == nullptr)
	{
		return false;
	}
	int w;
	int h;
	SDL_QueryTexture(sheetTexture, nullptr, nullptr, &w, &h);
	sheetRect = new SDL_Rect();
	sheetRect->x = 0;
	sheetRect->y = 0;
	sheetRect->w = w;
	sheetRect->h = 130;

	sheetWidth = w;
	sheetHeight = h;
	for (int i = 0; i < ANIM_NUM; ++i)
	{
		if (animations[i] != nullptr)
			delete animations[i];
		animations[i] = new Animation();
	}
	return true;
}

bool PlayerAnimationBase::save(const char* filename) const
{
	FILE *fp;
	fp = fopen(filename, "w");
	if (fp == nullptr)
		return false;
	
	fwrite(sheetFileName, sizeof(char), strlen(&sheetFileName[0]), fp);
	fwrite("\n", sizeof(char), 1, fp);
	char* buffer = (char*)malloc(sizeof(char) * 50);
	
	for (int i = 0; i < ANIM_NUM; ++i)
	{
		itoa(animations[i]->frameNum, buffer, 10);				
		
		fwrite(buffer, sizeof(char), strlen(buffer), fp);
		fwrite("#", sizeof(char), 1, fp);			
		sprintf(buffer, "%f", animations[i]->speed);
		fwrite(buffer, sizeof(char), strlen(buffer), fp);
		fwrite("#", sizeof(char), 1, fp);
		for (int j = 0; j < animations[i]->frameNum; ++j)
		{
			itoa(animations[i]->frames[j]->x, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->frames[j]->y, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->frames[j]->w, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->frames[j]->h, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);

			itoa(animations[i]->headColliders[j]->x, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->headColliders[j]->y, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->headColliders[j]->w, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->headColliders[j]->h, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);

			itoa(animations[i]->bodyColliders[j]->x, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->bodyColliders[j]->y, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->bodyColliders[j]->w, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->bodyColliders[j]->h, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);

			itoa(animations[i]->legsColliders[j]->x, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->legsColliders[j]->y, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->legsColliders[j]->w, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->legsColliders[j]->h, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);

			itoa(animations[i]->damageColliders[j]->x, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->damageColliders[j]->y, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->damageColliders[j]->w, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
			itoa(animations[i]->damageColliders[j]->h, buffer, 10);
			fwrite(buffer, sizeof(char), strlen(buffer), fp);
			fwrite("#", sizeof(char), 1, fp);
		}
		fwrite("\n", sizeof(char), 1, fp);
	}
	fclose(fp);
	return true;
}

bool PlayerAnimationBase::load(const char* filename) 
{
	FILE * fp;
	char * line = NULL;
	size_t len = 10000;

	fopen_s(&fp, filename, "r");
	
	if (fp == NULL)
		return false;

	line = (char*)malloc(len);
	
	if (!fgets(line, len, fp))
		return false;
	char* sheetName = (char*)malloc(sizeof(char) * 300);
	int i = 0;
	int j = 0;
	while (line[i] != '\n')
		sheetName[j++] = line[i++];
	sheetName[j] = 0;
	strcpy(&sheetFileName[0], sheetName);

	setUp(sheetName);
	
	if (sheetTexture == nullptr)
	{
		free(line);
		return false;
	}
	int animCount = 0;
	while (fgets(line, len, fp)) {
		i = 0;
		j = 0;
		char buffer[300];		
		while (line[i] != '#')
			buffer[j++] = line[i++];
		buffer[j++] = 0;
		++i;
		j = 0;
		int nFrames = atoi(buffer);
		while (line[i] != '#')
			buffer[j++] = line[i++];
		buffer[j++] = 0;
		i++;
		float speed = atof(buffer);
		animations[animCount]->frameNum = nFrames;
		animations[animCount]->speed = speed;

		for (int ii = 0; ii < nFrames; ii++)
		{			
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			int x = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			int y = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			int w = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			int h = atoi(buffer);
			++i;
			animations[animCount]->frames.push_back(new SDL_Rect({ x,y,w,h }));

			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			x = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			y = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			w = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			h = atoi(buffer);
			++i;
			animations[animCount]->headColliders.push_back(new SDL_Rect({ x,y,w,h }));

			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			x = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			y = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			w = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			h = atoi(buffer);
			++i;
			animations[animCount]->bodyColliders.push_back(new SDL_Rect({ x,y,w,h }));

			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			x = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			y = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			w = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			h = atoi(buffer);
			++i;
			animations[animCount]->legsColliders.push_back(new SDL_Rect({ x,y,w,h }));

			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			x = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			y = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			w = atoi(buffer);
			++i;
			j = 0;
			while (line[i] != '#')
				buffer[j++] = line[i++];
			buffer[j++] = 0;
			h = atoi(buffer);
			++i;
			animations[animCount]->damageColliders.push_back(new SDL_Rect({ x,y,w,h }));
		}
		++animCount;
	}

	fclose(fp);
	free(line);
	

	return true;
}
