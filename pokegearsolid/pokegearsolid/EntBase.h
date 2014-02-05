#pragma once
#include "Defines.h"

enum EntTypes
{
	none,
	AI,
	Item,
	Node
};

class Entity
{
protected:
	EntTypes type;
	Pos loc;
public:
	Entity();
	Entity(EntTypes);
	Entity(EntTypes,Pos&);
	EntTypes getType();
	virtual bool getRend(D3Object&) = 0;
	virtual bool setRend(D3Object&) = 0;
	virtual bool update(void*) = 0;
};