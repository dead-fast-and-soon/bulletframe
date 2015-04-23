#pragma once

#include "entity.h"
#include "engine.h"
#include "octal/vector/vector.h"

using namespace octal;

class Bullet;

class BulletAlgorithm 
{
public:
	virtual void Tick(Bullet bullet, double deltaTime) = 0;
};

/**
* @author	octopod
* @brief	A bullet.
*/
class Bullet : virtual Entity, Clonable<Bullet>
{
private:
	EngineObject *core, *body;
	mutable Vector velocity;
	mutable BulletAlgorithm *algorithm;

	void Tick(double deltaTime) { algorithm->Tick(*this, deltaTime); }

public:
	Bullet(EngineObject* core, EngineObject* body, int radius);

	/**
	* @author	octopod
	* @brief	Gets the position.
	* 		
	* @return	the position
	*/
	virtual Vector GetPosition() const final { return Entity::GetPosition(); }

	/**
	* @author	octopod
	* @brief	Sets the position.
	*
	* @param	vec	the vector position
	*/
	virtual void SetPosition(Vector pos) const final { Entity::SetPosition(pos); }
	
	/**
	* @author	octopod
	* @brief	Gets the velocity.
	*
	* @return	the velocity
	*/
	Vector GetVelocity(void) const { return this->velocity; }

	/**
	* @author	octopod
	* @brief	Sets the velocity.
	*
	* @param	vec the vector velocity
	*/
	void SetVelocity(Vector vel) const { this->velocity = vel; }

	/**
	* @author	octopod
	* @brief	Gets the core object.
	*
	* @return	the core object
	*/
	EngineObject* Core(void) const { return core; }

	/**
	* @author	octopod
	* @brief	Gets the body object.
	*
	* @return	the body object
	*/
	EngineObject* Body(void) const { return body; }

	/**
	* @author	octopod
	* @brief	Gets the current bullet algorithm.
	*
	* @return	the current algorithm
	*/
	BulletAlgorithm* GetAlgorithm(void) const { return algorithm; }

	/**
	* @author	octopod
	* @brief	Sets the current bullet algorithm.
	*
	* @param	algorithm the algorithm
	*/
	void SetAlgorithm(BulletAlgorithm* algorithm) const { this->algorithm = algorithm; }

	/**
	* @author	octopod
	* @brief	Clones this bullet.
	*
	* @return	the cloned bullet
	*/
	Bullet Clone();
};

class BulletTemplate
{
private:
	const int r;
	EngineObjectTemplate<> *cT, *bT;

public:
	BulletTemplate(EngineObjectTemplate<>* coreTemplate, EngineObjectTemplate<>* bodyTemplate, int radius) : r(radius), cT(coreTemplate), bT(bodyTemplate) { }
	Bullet Create() { return Bullet(cT->Create(), bT->Create(), r); }
};
