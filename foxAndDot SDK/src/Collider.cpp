#include "../include/foxAndDot-SDK/Components/Collider.h"
#include "../include/foxAndDot-SDK/Core.h"

void Collider::on_intersection(Scene_Component* comp)
{
	Collider_Args_Package args;
	args.collider   = this;
	args.other_comp = comp;
	this->im_collider->push_args(args);
	Core::the_core->emit(im_collider);
}

void Collider::on_intersection(Collider* other_collider)
{
	if (this->colliding and other_collider->is_colliding())
	{
		collision.push_args(last_valid_position);
		Core::the_core->emit(&collision);
	}
}

sf::FloatRect Collider::get_component_bounds()
{
	return this->collision_bounds;
}

void Collider::update()
{
	last_valid_position = (this->collision_bounds.position);
}

Collider::Collider()
{
	im_collider = new Signal<Collider_Args_Package>;
	Core::connect<Collider_Args_Package>(im_collider, &Core::handle_collider);
}

Collider::~Collider()
{
	delete im_collider;
	im_collider = nullptr;
}

void Collider::set_colliding(const bool& arg)
{
	colliding = arg;
}

bool Collider::is_colliding()
{
	return this->colliding;
}
