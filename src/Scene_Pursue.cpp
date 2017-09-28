#include "Scene_Pursue.h"

using namespace std;

Scene_Pursue::Scene_Pursue()
{
	target = Vector2D(640, 360);
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(target);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);

	Agent *agent2 = new Agent;
	agent2->setPosition(Vector2D(320, 360));
	agent2->setTarget(agent->getPosition());
	agent2->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent2);
}

Scene_Pursue::~Scene_Pursue()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void Scene_Pursue::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			target = Vector2D((float)(event->button.x), (float)(event->button.y));
			agents[0]->setTarget(target);
			agents[1]->setTarget(agents[0]->getPosition());
		}
		break;
	default:
		break;
	}
	Vector2D steering_force = agents[0]->Behavior()->Arrive(agents[0], agents[0]->getTarget(), dtime);
	Vector2D acceleration = steering_force / agents[0]->getMass();
	agents[0]->setVelocity(agents[0]->getVelocity() + acceleration * dtime);
	agents[0]->setVelocity(agents[0]->getVelocity().Truncate(agents[0]->getMaxVelocity()));
	agents[0]->setPosition(agents[0]->getPosition() + agents[0]->getVelocity() * dtime);
	agents[0]->update(steering_force, dtime, event);
	
	steering_force = agents[1]->Behavior()->Pursue(agents[1], agents[0], dtime);
	acceleration = steering_force / agents[1]->getMass();
	agents[1]->setVelocity(agents[1]->getVelocity() + acceleration * dtime);
	agents[1]->setVelocity(agents[1]->getVelocity().Truncate(agents[1]->getMaxVelocity()));
	agents[1]->setPosition(agents[1]->getPosition() + agents[1]->getVelocity() * dtime);
	agents[1]->update(steering_force, dtime, event);
}

void Scene_Pursue::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
	agents[1]->draw();
}

const char* Scene_Pursue::getTitle()
{
	return "SDL Steering Behaviors :: Pursue Demo";
}