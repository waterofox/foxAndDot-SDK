#pragma once
#include "Entity.h"

template<typename properties_package>
class Advanced_Entity : public Entity
{
public:
	properties_package properties;

	Advanced_Entity() : Entity() {};
	Advanced_Entity(const int& resource_id) : Entity(resource_id) {};
	Advanced_Entity(const sf::Vector2i& size) : Entity(size) {};
	Advanced_Entity(const sf::Vector2i& size, const int& resource_id) : Entity(size, resource_id) {};
	Advanced_Entity(const sf::IntRect& rect) : Entity(rect) {};
	Advanced_Entity(const sf::IntRect& rect, const int& resource_id) : Entity(rect, resource_id) {};

	~Advanced_Entity() = default;
};

 