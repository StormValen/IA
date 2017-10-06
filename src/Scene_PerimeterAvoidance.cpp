#include "Scene_PerimeterAvoidance.h"

using namespace std;

Scene_PerimeterAvoidance::Scene_PerimeterAvoidance()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

Scene_PerimeterAvoidance::~Scene_PerimeterAvoidance()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void Scene_PerimeterAvoidance::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->PerimeterAvoidance(agents[0], agents[0]->getTarget(), dtime);
	Vector2D acceleration = steering_force / agents[0]->getMass();
	agents[0]->setVelocity(agents[0]->getVelocity() + acceleration * dtime);
	agents[0]->setVelocity(agents[0]->getVelocity().Truncate(agents[0]->getMaxVelocity()));
	agents[0]->setPosition(agents[0]->getPosition() + agents[0]->getVelocity() * dtime);
	agents[0]->update(steering_force, dtime, event);
}

void Scene_PerimeterAvoidance::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)150, (int)618, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)150, (int)150, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)1130, (int)618, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)1130, (int)150, 15, 255, 0, 0, 255);
	
	agents[0]->draw();
}

const char* Scene_PerimeterAvoidance::getTitle()
{
	return "SDL Steering Behaviors :: Perimeter Avoidance Demo";
}