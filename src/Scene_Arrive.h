#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Scene_Arrive :
	public Scene
{
public:
	Scene_Arrive();
	~Scene_Arrive();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};
