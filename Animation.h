#pragma once
#include <vector>

using namespace std;

struct SDL_Rect;

class Animation
{
public:
	float speed;
	vector<SDL_Rect*> frames;

	int frameNum = 0;
	int frameWidth = 0;
	bool isLoop = false;
private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	SDL_Rect* GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}

	SDL_Rect* GetLastFrame()
	{
		//TODO: Check if cleanises
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