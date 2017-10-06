#include "Scene_PathFollowing.h"
#include <time.h>
using namespace std;

Scene_PathFollowing::Scene_PathFollowing()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
	for (int i = 0; i < 5; i++) {
		path[i] = generateRanomPoint();
	}

	nearestPoint = 0;
	isFirstLoop = true;
}

Scene_PathFollowing::~Scene_PathFollowing()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}	
}
Vector2D Scene_PathFollowing::generateRanomPoint() {
	return Vector2D(rand() % 1280, rand() % 768);
}

int Scene_PathFollowing::findNearestPoint() {
	int index;
	float min = 100000.f;
	for (int i = 0; i < 5; i++) {
		Vector2D temp = agents[0]->getPosition() - path[i];
		if (temp.Length() < min) {
			min = temp.Length();
			index = i;
		}
	}
	return index;
}

void Scene_PathFollowing::update(float dtime, SDL_Event *event)
{
	
	if (isFirstLoop == true) {
			nearestPoint = findNearestPoint();
			isFirstLoop = false;
	}
	
	Vector2D pos;
	agents[0]->setTarget(path[nearestPoint]);

	if (pos.Distance(agents[0]->getPosition(), agents[0]->getTarget())<100) {
		if (!nearestPoint<4) {
			agents[0]->setTarget(nearestPoint++);
		}
	}

	Vector2D steering_force = agents[0]->Behavior()->Seek(agents[0], agents[0]->getTarget(), dtime);
	Vector2D acceleration = steering_force / agents[0]->getMass();
	agents[0]->setVelocity(agents[0]->getVelocity() + acceleration * dtime);
	agents[0]->setVelocity(agents[0]->getVelocity().Truncate(agents[0]->getMaxVelocity()));
	agents[0]->setPosition(agents[0]->getPosition() + agents[0]->getVelocity() * dtime);
	agents[0]->update(steering_force, dtime, event);
}

void Scene_PathFollowing::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	for (int i = 0; i < 5; i++) {
		draw_circle(TheApp::Instance()->getRenderer(), (int)path[i].x, (int)path[i].y, 15, 255, 0, 0, 255);
	}
}

const char* Scene_PathFollowing::getTitle()
{
	return "SDL Steering Behaviors :: PathFollowing Demo";
}