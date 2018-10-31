#pragma once
#include <vector>

using namespace std;

struct SDL_Rect;

class Animation
{
public:
	float speed;
	vector<SDL_Rect*> frames;
	vector<SDL_Rect*> headColliders;
	vector<SDL_Rect*> bodyColliders;
	vector<SDL_Rect*> legsColliders;
	vector<SDL_Rect*> damageColliders;

	int frameNum = 1;
	int frameWidth = 0;
	bool isLoop = false;
private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{
		frames.push_back(new SDL_Rect({ 0,0,0,0 }));
		headColliders.push_back(new SDL_Rect({ 0,0,0,0 }));
		bodyColliders.push_back(new SDL_Rect({ 0,0,0,0 }));
		legsColliders.push_back(new SDL_Rect({ 0,0,0,0 }));
		damageColliders.push_back(new SDL_Rect({ 0,0,0,0 }));

	}

	~Animation()
	{
		for (int i = 0; i < frames.size(); i++)
		{
			delete(frames[i]);
			delete(headColliders[i]);
			delete(bodyColliders[i]);
			delete(legsColliders[i]);
			delete(damageColliders[i]);
		}
	}

	SDL_Rect* GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	SDL_Rect* GetLastFrame()
	{
		return frames[frames.size() - 1];
	}

	void reset() {
		current_frame = 0.0f;
	}

	bool isFinished()
	{
		return (int)current_frame == frames.size() - 1;
	}
};