#pragma once
#include "SFML/System/Vector2.hpp"
#include "../Slot.h"

class Handle_Collision_Slot : public Slot<sf::Vector2f>
{
	friend class Entity;

	Entity* this_entity = nullptr;

	void do_something() override;
};

