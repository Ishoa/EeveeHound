#include "EntBase.h"

Entity::Entity()
{
	type = none;
}

Entity::Entity(EntTypes Type)
{
	type = Type;
}

Entity::Entity(EntTypes Type,Pos& pos)
{
	type = Type;
	loc = pos;
}

EntTypes Entity::getType()
{
	return type;
}