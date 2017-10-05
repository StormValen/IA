#include "Scene_Wander.h"

using namespace std;
const float WanderMaxAngleChange = 30;
const float WanderOffset = 200;
const float WanderRadius = 100;
float angle = 0;
float WanderAngle = 0;
Vector2D TargetPosition;
Vector2D CircleCenter;


int counter = 0;

Scene_Wander::Scene_Wander()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);
}

Scene_Wander::~Scene_Wander()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

float Scene_Wander::RandomBinomial() {
	return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX));
}

void Scene_Wander::update(float dtime, SDL_Event *event)
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
	if (counter %1000 == 0) {
	angle = (float)(atan2(agents[0]->getVelocity().y, agents[0]->getVelocity().x) * RAD2DEG);
	WanderAngle += RandomBinomial() * WanderMaxAngleChange;
	
	}
	float TargetAngle = angle + WanderAngle;
	CircleCenter = agents[0]->getPosition() + agents[0]->getVelocity().Normalize() * WanderOffset;
	TargetPosition.x = CircleCenter.x + WanderRadius * cos(TargetAngle);
	TargetPosition.y = CircleCenter.y + WanderRadius * sin(TargetAngle);


		Vector2D steering_force = agents[0]->Behavior()->Wander(agents[0], TargetPosition, dtime);
		Vector2D acceleration = steering_force / agents[0]->getMass();
		agents[0]->setVelocity(agents[0]->getVelocity() + acceleration * dtime);
		agents[0]->setVelocity(agents[0]->getVelocity().Truncate(agents[0]->getMaxVelocity()));
		agents[0]->setPosition(agents[0]->getPosition() + agents[0]->getVelocity() * dtime);
		agents[0]->update(steering_force, dtime, event);
	

	counter++;
}

void Scene_Wander::draw()
{
	draw_circle(TheApp::Instance()->getRenderer(), (int)CircleCenter.x, (int)CircleCenter.y, WanderRadius, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)TargetPosition.x, (int)TargetPosition.y, 15, 255, 0, 0, 255);
	agents[0]->draw();
}

const char* Scene_Wander::getTitle()
{
	return "SDL Steering Behaviors :: Wander Demo";
}