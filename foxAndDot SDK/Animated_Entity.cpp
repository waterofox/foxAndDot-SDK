#include "Core.h"

Animated_Entity::Animated_Entity(const sf::IntRect& sprite_rectangle) : Entity(sprite_rectangle){}

void Animated_Entity::update(Core* the_core)
{
	Entity::update(the_core);
	if (animation_enabled)
	{
		animation_timer += the_core->get_delta_time();
		if (animation_timer.asSeconds() >= 1.0 / frame_per_seconds)
		{
			animation_timer = sf::Time::Zero;
			current_frame = (current_frame + 1) % frame_count;
		}
	}
	this->setTextureRect(sf::IntRect(sf::Vector2i(int(current_frame) * (this->getTexture().getSize().x / frame_count),0),sf::Vector2i(this->getTexture().getSize().y, this->getTexture().getSize().x / frame_count)));
}

void Animated_Entity::play_animation()
{
	animation_enabled = true;
}
void Animated_Entity::pause_animation()
{
	animation_enabled = false;
}