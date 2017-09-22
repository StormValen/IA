#include "SteeringBehavior.h"



SteeringBehavior::SteeringBehavior()
{
}


SteeringBehavior::~SteeringBehavior()
{
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = target - agent->position;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicSeek(Agent *agent, Agent *target, float dtime)
{
	return KinematicSeek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D steering = agent->position - target;
	steering.Normalize();
	return steering * agent->max_velocity;
}

Vector2D SteeringBehavior::KinematicFlee(Agent *agent, Agent *target, float dtime)
{
	return KinematicFlee(agent, target->position, dtime);
}

/* Add here your own Steering Behavior functions definitions */

Vector2D SteeringBehavior::Seek(Agent *agent, Vector2D target, float dtime)
{
	
	Vector2D desiredVelocity = target - agent->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;
	return steeringForce;
}

Vector2D SteeringBehavior::Seek(Agent *agent, Agent *target, float dtime)
{
	return Seek(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Flee(Agent *agent, Vector2D target, float dtime)
{
	Vector2D desiredVelocity = agent->getPosition()- target;
	desiredVelocity.Normalize();
	desiredVelocity *= agent->max_velocity;
	Vector2D steeringForce = desiredVelocity - agent->getVelocity();
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;
	return steeringForce;
}

Vector2D SteeringBehavior::Flee(Agent *agent, Agent *target, float dtime)
{
	return Flee(agent, target->position, dtime);
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Vector2D target, float dtime)
{
	if (target.Distance(agent->getPosition(), target) > 300.f) {
		Vector2D desiredVelocity = target - agent->getPosition();
		desiredVelocity.Normalize();
		desiredVelocity *= agent->max_velocity;
		Vector2D steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->max_velocity;
		steeringForce *= agent->max_force;
		return steeringForce;
	}
	else {
		Vector2D desiredVelocity = target - agent->getPosition();
		desiredVelocity.Normalize();
		desiredVelocity *= agent->max_velocity*(target.Distance(agent->getPosition(), target) / 300.f);
		Vector2D steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->max_velocity;
		steeringForce *= agent->max_force;
		return steeringForce;
	}
}

Vector2D SteeringBehavior::Arrive(Agent *agent, Agent *target, float dtime)
{
	return Arrive(agent, target->position, dtime);
}
