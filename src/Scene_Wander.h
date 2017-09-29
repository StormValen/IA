#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_Wander :
	public Scene
{
public:
	Scene_Wander();
	~Scene_Wander();
	void update(float dtime, SDL_Event *event);
	void draw();
	float RandomBinomial();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};