#pragma once

#include "octal/vector/vector.h"

class Engine
{
public:
	/**
	 *	@author octopod
	 *	@brief	Runs every frame update (or tick)
	 */
	void OnTick(float deltaTime);
};
/**
* @author	octopod
* @brief	An object created by the engine.
*/
class EngineObject
{
private:
	virtual ~EngineObject() { }

public:
	virtual void Remove() = 0;

	virtual Vector GetPosition() = 0;
	virtual void SetPosition(Vector vec) = 0;
};

/**
* @author	octopod
* @brief	A template that creates objects.
*/
template<class Type = EngineObject>
class EngineObjectTemplate
{
public:
	virtual Type* Create() = 0;
};