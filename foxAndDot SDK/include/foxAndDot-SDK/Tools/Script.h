#pragma once

#include "Executable.h"

class Entity;

class Script : public Executable
{
protected:
	Entity* this_entity = nullptr;

public: 
	void set_entity(Entity* entity_ptr);
	virtual void operator()() override {}

	Script()  = default;
	Script(Entity* entity_ptr);
	Script(const Script& other_script);

	Script& operator=(const Script& other_script);
	
	virtual ~Script() = default;
};

