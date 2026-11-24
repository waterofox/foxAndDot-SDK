#include "../include/foxAndDot-SDK/Components/Collider.h"
#include "../include/foxAndDot-SDK/Core.h"

void Collider::on_intersection(Scene_Component* comp)
{
	Collider_Args_Package args;
	args.collider   = this;
	args.other_comp = comp;
	this->im_collider.push_args(args);
	Core::the_core->emit(&im_collider);
}

void Collider::on_intersection(Collider* other_collider)
{
	if (this->colliding and other_collider->is_colliding())
	{
		collision.push_args(last_valid_position);
		Core::the_core->emit(&collision);
	}
}

sf::FloatRect Collider::get_component_bounds() const
{
	return this->collision_bounds;
}

void Collider::set_collision_size(const sf::Vector2f& size)
{
	collision_bounds.size = size;

}

sf::Vector2f Collider::get_collision_size() const
{
	return collision_bounds.size;
}


void Collider::update()
{
	last_valid_position = (this->collision_bounds.position);
}

Collider::Collider()
{
	connect(&this->im_collider, &Core::handle_collider_slot);
	set_intersection(true);
}

void Collider::set_colliding(const bool& arg)
{
	colliding = arg;
}

bool Collider::is_colliding() const
{
	return colliding;
}

