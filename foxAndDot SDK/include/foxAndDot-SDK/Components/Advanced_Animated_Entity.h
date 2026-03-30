#pragma once
#include "Animated_Entity.h"

template <typename properties_package>
class Advanced_Animated_Entity : public Animated_Entity
{
public:
	properties_package properties;

	Advanced_Animated_Entity(const sf::IntRect& sprite_rectangle) : Animated_Entity(sprite_rectangle) {}
	Advanced_Animated_Entity(const sf::IntRect& sprite_rectangle, const int& resource_id) : Animated_Entity(sprite_rectangle, resource_id) {}
	Advanced_Animated_Entity(const sf::Vector2i& sprite_size) : Animated_Entity(sprite_size) {}
	Advanced_Animated_Entity(const sf::Vector2i& sprite_size, const int& resource_id) : Animated_Entity(sprite_size, resource_id) {}

	~Advanced_Animated_Entity() = default;
};