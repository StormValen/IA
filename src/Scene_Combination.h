#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_Combination :
	public Scene
{
public:
	Scene_Combination();
	~Scene_Combination();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
	float RandomBinomial();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};