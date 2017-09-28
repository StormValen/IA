#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_Evade :
	public Scene
{
public:
	Scene_Evade();
	~Scene_Evade();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};