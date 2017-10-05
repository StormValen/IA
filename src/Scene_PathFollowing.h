#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"


class Scene_PathFollowing :
	public Scene
{
public:
	Scene_PathFollowing();
	~Scene_PathFollowing();
	void update(float dtime, SDL_Event *event);
	void draw();
	Vector2D generateRanomPoint();
	int findNearestPoint();
	const char* getTitle();
	
private:
	int nearestPoint;
	std::vector<Agent*> agents;
	Vector2D target;
	Vector2D path[];
};
