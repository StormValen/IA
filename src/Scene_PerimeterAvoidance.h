#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_PerimeterAvoidance :
	public Scene
{
public:
	Scene_PerimeterAvoidance();
	~Scene_PerimeterAvoidance();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};