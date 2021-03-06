#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Vector2D.h"

class Scene_Pursue :
	public Scene
{
public:
	Scene_Pursue();
	~Scene_Pursue();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D target;
};