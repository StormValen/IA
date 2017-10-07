#include "Scene_Combination.h"

using namespace std;

const float _WanderMaxAngleChange = 30;
const float _WanderOffset = 200;
const float _WanderRadius = 100;
float _angle = 0;
float _WanderAngle = 0;
Vector2D _TargetPosition;
Vector2D _CircleCenter;
int _counter = 0;

Scene_Combination::Scene_Combination()
{
	Agent *agent = new Agent;
	agent->setPosition(Vector2D(640, 360));
	agent->setTarget(Vector2D(640, 360));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent);
	target = Vector2D(640, 360);

	Agent *agent2 = new Agent;
	agent2->setPosition(Vector2D(320, 360));
	agent2->setTarget(agent->getPosition());
	agent2->loadSpriteTexture("../res/soldier.png", 4);
	agents.push_back(agent2);
}

Scene_Combination::~Scene_Combination()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

float Scene_Combination::RandomBinomial() {
	return ((float)rand() / (RAND_MAX)) - ((float)rand() / (RAND_MAX));
}

void Scene_Combination::update(float dtime, SDL_Event *event)
{
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			//target = Vector2D((float)(event->button.x), (float)(event->button.y));
			//agents[0]->setTarget(target);
		}
		break;
	default:
		break;
	}
	
	if (_counter % 1000 == 0) {
		_angle = (float)(atan2(agents[0]->getVelocity().y, agents[0]->getVelocity().x) * RAD2DEG);
		_WanderAngle += RandomBinomial() * _WanderMaxAngleChange;

	}
	float TargetAngle = _angle + _WanderAngle;
	_CircleCenter = agents[0]->getPosition() + agents[0]->getVelocity().Normalize() * _WanderOffset;
	_TargetPosition.x = _CircleCenter.x + _WanderRadius * cos(TargetAngle);
	_TargetPosition.y = _CircleCenter.y + _WanderRadius * sin(TargetAngle);

	Vector2D steering_force = agents[0]->Behavior()->Combination(agents[0], _TargetPosition, dtime);
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

	_counter++;
}

void Scene_Combination::draw()
{
	//draw_circle(TheApp::Instance()->getRenderer(), (int)target.x, (int)target.y, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)_CircleCenter.x, (int)_CircleCenter.y, _WanderRadius, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)_TargetPosition.x, (int)_TargetPosition.y, 15, 255, 0, 0, 255);

	draw_circle(TheApp::Instance()->getRenderer(), (int)150, (int)618, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)150, (int)150, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)1130, (int)618, 15, 255, 0, 0, 255);
	draw_circle(TheApp::Instance()->getRenderer(), (int)1130, (int)150, 15, 255, 0, 0, 255);

	agents[0]->draw();
	agents[1]->draw();
}

const char* Scene_Combination::getTitle()
{
	return "SDL Steering Behaviors :: Combination [Perimeter Avoidance / Wander / Pursue] Demo";
}