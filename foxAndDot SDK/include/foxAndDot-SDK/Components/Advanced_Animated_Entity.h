#pragma once
#include "Animated_Entity.h"

template <typename properties_package>
class Advanced_Animated_Entity : public Animated_Entity
{
public:
	properties_package properties;

	Advanced_Animated_Entity() : Animated_Entity() {};
	Advanced_Animated_Entity(const int& resource_id) : Animated_Entity(resource_id) {};
	Advanced_Animated_Entity(const sf::Vector2i& size) : Animated_Entity(size) {};
	Advanced_Animated_Entity(const sf::Vector2i& size, const int& resource_id) : Animated_Entity(size, resource_id) {};
	Advanced_Animated_Entity(const sf::IntRect& rect) : Animated_Entity(rect) {};
	Advanced_Animated_Entity(const sf::IntRect& rect, const int& resource_id) : Animated_Entity(rect, resource_id) {};

	~Advanced_Animated_Entity() = default;
};