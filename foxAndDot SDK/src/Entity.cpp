#include "../include/foxAndDot-SDK/Components/Entity.h"

Entity::Entity() : Collider(), sf::Sprite(empty_entity_s_texture)
{
	this->handle_collision_slot = Slot<sf::Vector2f, Entity>(&Entity::handle_collision, this);
	connect(&this->collision, &this->handle_collision_slot);

	this->collider_margin = sf::Vector2f(0, 0);

	this->type_of_resource = Resource_Types::Texture;
}

Entity::Entity(const int& resource_id) : Entity()
{
	this->set_resource(resource_id);
}

Entity::Entity(const sf::Vector2i& size) : Entity()
{
	this->setTextureRect(sf::IntRect(this->getTextureRect().position, size));
	this->collision_bounds = this->getGlobalBounds();
}

Entity::Entity(const sf::Vector2i& size, const int& resource_id) : Entity(size)
{
	this->set_resource(resource_id);
}

Entity::Entity(const sf::IntRect& rect) : Entity()
{
	this->setTextureRect(rect);
	this->collision_bounds = this->getGlobalBounds();
}

Entity::Entity(const sf::IntRect& rect, const int& resource_id) : Entity(rect)
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


void Entity::handle_collision(const sf::Vector2f& args)
{
	this->setPosition(args);
	this->move(-this->collider_margin);
	this->collision_bounds.position = args;
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


