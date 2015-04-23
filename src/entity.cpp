
#include "entity.h"
#include "octal/vector/vector.h"

using namespace octal;

Vector Entity::GetPosition() const
{
	return position;
}

void Entity::SetPosition(Vector vec) const
{
	position = vec;
}