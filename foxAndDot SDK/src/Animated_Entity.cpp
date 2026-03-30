#include "../include/foxAndDot-SDK/Components/Animated_Entity.h"

Animated_Entity::Animated_Entity(const sf::IntRect& sprite_rectangle) : 
	Entity(sprite_rectangle){}
Animated_Entity::Animated_Entity(const sf::IntRect& sprite_rectangle, const int& resource_id) : 
	Entity(sprite_rectangle, resource_id) {}
Animated_Entity::Animated_Entity(const sf::Vector2i& size_of_sprite_rectangle) : 
	Entity(size_of_sprite_rectangle){}
Animated_Entity::Animated_Entity(const sf::Vector2i& size_of_sprite_rectangle, const int& resource_id) : 
	Entity(size_of_sprite_rectangle, resource_id) {}

Animated_Entity::Animated_Entity(const sf::IntRect& sprite_rectangle, const int& resource_id) : Entity(sprite_rectangle,resource_id){}

Animated_Entity::Animated_Entity(const sf::Vector2i& sprite_size) : Entity(sprite_size){}

Animated_Entity::Animated_Entity(const sf::Vector2i& sprite_size, const int& resource_id) : Entity(sprite_size,resource_id){}

void Animated_Entity::update()
{
	Entity::update();
	if (animation_enabled)
	{
		animation_timer += Core::the_core->get_delta_time();
		if (animation_timer.asSeconds() >= 1.0 / frame_per_seconds)
		{
			animation_timer = sf::Time::Zero;
			current_frame = (current_frame + 1) % frame_count;
		}
	}
	this->setTextureRect(sf::IntRect(sf::Vector2i(int(current_frame) * (this->getTexture().getSize().x / frame_count),0),\
		sf::Vector2i(this->getTexture().getSize().x / frame_count, this->getTexture().getSize().y)));
}

void Animated_Entity::play_animation()
{
	animation_enabled = true;
}
void Animated_Entity::pause_animation()
{
	animation_enabled = false;
}