#pragma once
#include "Entity.h"

template<typename properties_package>
class Advanced_Entity : public Entity
{
public:
	properties_package properties;

	Advanced_Entity(const sf::IntRect& sprite_rectangle) : Entity(sprite_rectangle){}
	Advanced_Entity(const sf::IntRect& sprite_rectangle, const int& resource_id) : Entity(sprite_rectangle, resource_id) {}
	Advanced_Entity(const sf::Vector2i& sprite_size) : Entity(sprite_size) {}
	Advanced_Entity(const sf::Vector2i& sprite_size, const int& resource_id) : Entity(sprite_size, resource_id) {}

	~Advanced_Entity() = default;
};

