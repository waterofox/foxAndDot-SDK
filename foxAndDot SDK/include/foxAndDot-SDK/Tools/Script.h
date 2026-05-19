#pragma once

#include "Executable.h"

class Entity;

class Script : public Executable
{
protected:
	Entity* this_entity = nullptr; // Refer to this field to interact with the entity

public: 
	void set_entity(Entity* entity_ptr);
	virtual void operator()() override {}
	virtual ~Script() = default;
};

