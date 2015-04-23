
#pragma once

#include "octal/vector/vector.h"

using namespace octal;

/**
* @author	octopod
* @brief	An entity.
*/
class Entity
{
private:
	mutable Vector position = Vector::ZERO;

public:
	virtual ~Entity() { }

	virtual Vector GetPosition() const;
	virtual void SetPosition(Vector vec) const;

	virtual void Tick(double deltaTime) = 0;
};

/**
* @author	octopod
* @brief	A clonable entity.
*/
template <class T>
class Clonable : virtual Entity
{
public:
	virtual T Clone() = 0;
};