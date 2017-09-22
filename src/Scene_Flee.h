#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_Flee :
	public Scene
{
public:
	Scene_Flee();
	~Scene_Flee();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};