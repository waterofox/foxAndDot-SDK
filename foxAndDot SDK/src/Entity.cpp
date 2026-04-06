#include "../include/foxAndDot-SDK/Components/Entity.h"

Entity::Entity(const sf::IntRect& sprite_rectangle) :
	Sprite(empty_entity_s_texture, sprite_rectangle)
{
	this->collision_slot.this_entity = this;	
	this->collision.connect(&this->collision_slot);

	this->collider_margin = sf::Vector2f(0, 0);
	this->collision_bounds = this->getGlobalBounds();
}

Entity::Entity(const sf::IntRect& sprite_rectangle, const int& resource_id) : Entity(sprite_rectangle)
{
	this->set_resource(resource_id);
}

Entity::Entity(const sf::Vector2i& sprite_size): Entity(sf::IntRect(sf::Vector2i(0,0),sprite_size)){}

Entity::Entity(const sf::Vector2i& sprite_size, const int& resource_id) : Entity(sprite_size)
{
	this->set_resource(resource_id);
}

void Entity::set_collider_margin(const sf::Vector2f& arg)
{
	this->collider_margin = arg;
}

void Entity::set_collision_size(const sf::Vector2f& arg)
{
	this->collision_bounds.size = arg;
}

sf::Drawable* Entity::as_drawable()
{
	return static_cast<sf::Sprite*>(this);
}


void Entity::update()
{
	Collider::update();

	if (entity_script != nullptr) 
	{ 
		entity_script->set_entity(this);
		(*entity_script)();
	}

	collision_bounds.position  = this->getPosition();
	collision_bounds.position += collider_margin;
}

sf::FloatRect Entity::get_component_render_bounds()
{
	return this->getGlobalBounds();
}

sf::FloatRect Entity::get_component_bounds()
{
	return this->collision_bounds;
}


void Entity::set_script(Script* ent_script)
{
	entity_script = ent_script;
}

void Entity::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	this->setTexture(*std::get<sf::Texture*>(resource));
}


void Entity::Handle_Collision_Slot::do_something()
{
	this->this_entity->setPosition(this->args);
	this->this_entity->move(-this->this_entity->collider_margin);
	this->this_entity->collision_bounds.position = this->args;
}
