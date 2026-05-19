#include "../include/foxAndDot-SDK/Components/Animated_Entity.h"

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

Animated_Entity::Animated_Entity() : Entity(){}

Animated_Entity::Animated_Entity(const int& resource_id) : Entity(resource_id)
{
}

Animated_Entity::Animated_Entity(const sf::Vector2i& size) : Entity(size)
{
}

Animated_Entity::Animated_Entity(const sf::Vector2i& size, const int& resource_id) : Entity(size,resource_id)
{
}

Animated_Entity::Animated_Entity(const sf::IntRect& rect) : Entity(rect)
{
}

Animated_Entity::Animated_Entity(const sf::IntRect& rect, const int& resource_id) : Entity(rect,resource_id)
{
}


void Animated_Entity::play_animation()
{
	animation_enabled = true;
}
void Animated_Entity::pause_animation()
{
	animation_enabled = false;
}