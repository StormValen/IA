#pragma once
#include "Agent.h"
#include "Vector2D.h"

class Agent;

class SteeringBehavior
{
public:
	SteeringBehavior();
	~SteeringBehavior();
	Vector2D KinematicSeek(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicSeek(Agent *agent, Agent *target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Vector2D target, float dtime);
	Vector2D KinematicFlee(Agent *agent, Agent *target, float dtime);

	/* Add here your own Steering Behavior functions declarations */
	Vector2D Seek(Agent *agent, Vector2D target, float dtime);
	Vector2D Seek(Agent *agent, Agent *target, float dtime);
	Vector2D Flee(Agent *agent, Vector2D target, float dtime);
	Vector2D Flee(Agent *agent, Agent *target, float dtime);
	Vector2D Arrive(Agent *agent, Vector2D target, float dtime);
	Vector2D Arrive(Agent *agent, Agent *target, float dtime);
	Vector2D Pursue(Agent *agent, Agent *target, float dtime);
	Vector2D Evade(Agent *agent, Agent *target, float dtime);
	Vector2D Wander(Agent *agent, Vector2D target, float dtime);
	Vector2D Wander(Agent *agent, Agent *target, float dtime);
	Vector2D PerimeterAvoidance(Agent *agent, Vector2D target, float dtime);
	Vector2D Combination(Agent *agent, Vector2D target, float dtime);
	//etc...

};
