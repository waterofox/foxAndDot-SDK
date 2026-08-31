#pragma once
#include "Entity.h"

template<typename properties_package>
class Advanced_Entity : public Entity
{

	//Advanced Entity is Entity with custom args package (var/class/struct)
public:
	properties_package properties;

	Advanced_Entity() : Entity() {};
	Advanced_Entity(const int& resource_id) : Entity(resource_id) {};
	Advanced_Entity(const sf::Vector2i& size) : Entity(size) {};
	Advanced_Entity(const sf::Vector2i& size, const int& resource_id) : Entity(size, resource_id) {};
	Advanced_Entity(const sf::IntRect& rect) : Entity(rect) {};
	Advanced_Entity(const sf::IntRect& rect, const int& resource_id) : Entity(rect, resource_id) {};

	Advanced_Entity(const Advanced_Entity<properties_package>& other) : Entity(other) 
	{
		this->properties = other.properties;
	}
	Advanced_Entity<properties_package>& operator=(const Advanced_Entity<properties_package>& other)
	{
		if (this == &other) { return *this; }

		Entity::operator=(other);

		this->properties = other.properties;

		return *this;
	}

	~Advanced_Entity() = default;
};

 