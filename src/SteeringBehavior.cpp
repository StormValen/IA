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

Vector2D SteeringBehavior::Pursue(Agent *agent, Agent *target, float dtime)
{
	if (target->getVelocity().Length() == 0) {
		return Arrive(agent, target->getPosition(), dtime);
	}
	float T = Vector2D::Distance(agent->getPosition(), target->getPosition()) / target->getVelocity().Length();
	Vector2D predictedTarget = target->getPosition() + target->getVelocity()*T;
	return Arrive(agent, predictedTarget,dtime);
}

Vector2D SteeringBehavior::Evade(Agent *agent, Agent *target, float dtime)
{
	if (target->getVelocity().Length() == 0) {
		return Flee(agent, target->getPosition(), dtime);
	}
	float T = Vector2D::Distance(agent->getPosition(), target->getPosition()) / target->getVelocity().Length();
	Vector2D predictedTarget = target->getPosition() + target->getVelocity()*T;
	agent->setTarget(predictedTarget);
	return Flee(agent, predictedTarget, dtime);
}

Vector2D SteeringBehavior::Wander(Agent *agent, Vector2D target, float dtime)
{
	return Arrive(agent, target, dtime);
}

Vector2D SteeringBehavior::PerimeterAvoidance(Agent *agent, Vector2D target, float dtime)
{
	int perimeterBorder = 150;
	int perimeterHeight = 768;
	int perimeterWidth = 1280;
	Vector2D desiredVelocity = target - agent->getPosition();
	Vector2D steeringForce;

	if (agent->getPosition().x < perimeterBorder)
		desiredVelocity.x = agent->getMaxVelocity();
	else if(agent->getPosition().x > perimeterWidth - perimeterBorder)
		desiredVelocity.x = -agent->getMaxVelocity();
	if (agent->getPosition().y < perimeterBorder)
		desiredVelocity.y = agent->getMaxVelocity();
	else if(agent->getPosition().y > perimeterHeight - perimeterBorder)
		desiredVelocity.y = -agent->getMaxVelocity();
	if (desiredVelocity.Length() > 0.0f) {
		steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getMaxVelocity();
		steeringForce *= agent->max_force;
	}
	return steeringForce;
}

Vector2D SteeringBehavior::Combination(Agent *agent, Vector2D target, float dtime)
{
	int perimeterBorder = 150;
	int perimeterHeight = 768;
	int perimeterWidth = 1280;
	Vector2D desiredVelocity = target - agent->getPosition();
	Vector2D steeringForce;

	if (agent->getPosition().x < perimeterBorder)
		desiredVelocity.x = agent->getMaxVelocity();
	else if (agent->getPosition().x > perimeterWidth - perimeterBorder)
		desiredVelocity.x = -agent->getMaxVelocity();
	if (agent->getPosition().y < perimeterBorder)
		desiredVelocity.y = agent->getMaxVelocity();
	else if (agent->getPosition().y > perimeterHeight - perimeterBorder)
		desiredVelocity.y = -agent->getMaxVelocity();
	if (desiredVelocity.Length() > 0.0f) {
		steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce /= agent->getMaxVelocity();
		steeringForce *= agent->max_force;
	}
	return steeringForce;
}