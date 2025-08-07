#include "Core.h"
Entity::Entity(const sf::Texture& texture, const sf::IntRect& sprite_rectangle) : 
		Sprite(texture,sprite_rectangle)
{
	on_intersection = Entity::entity_on_intersection;
	this->collision_bounds = this->getGlobalBounds();
	this->colliding = false;
	last_valid_position = sf::Vector2f(0, 0);

}

Entity::~Entity() {}

/*
Entity::Entity(const Entity& another_entity) : Sprite(*this)
{

	//todo возможные проблемы с текстурами

	this->collision_bounds = another_entity.collision_bounds;
	this->colliding = another_entity.colliding;


	this->entity_script = another_entity.entity_script;

	this->properties = another_entity.properties;
}

Entity& Entity::operator=(const Entity& another_entity)
{
	if (this == &another_entity) { return *this; }
	//todo возможные проблемы с текстурами

	this->collision_bounds = another_entity.collision_bounds;
	this->colliding = another_entity.colliding;


	this->entity_script = another_entity.entity_script;

	this->properties = another_entity.properties;

	return *this;
}
*/
Entity::property_type& Entity::operator[](const std::string& name)
{
	try
	{
		auto iter_on_property = this->properties.find(name);
		if (iter_on_property == this->properties.end()) {
			throw std::runtime_error(ERROR(EENTITY, "property [" + name + "] does not exist"));
		}
		else { return this->properties[name]; }
	}
	catch (std::exception& err) { std::cout << err.what() << std::endl; assert(false); }
}
sf::Drawable* Entity::as_drawable()
{
	return this;
}
Entity::property_type& Entity::operator[](const char*& name)
{
	return (*this)[std::string(name)];
}

void Entity::set_colliding(const bool& arg) { this->colliding = arg;}
const bool& Entity::is_colliding() { return this->colliding; }

sf::FloatRect& Entity::get_collision_bounds() { return this->collision_bounds; }

void Entity::update(Core* the_core)
{
	last_valid_position = this->getPosition();

	if (entity_script == nullptr) { return; }
	entity_script(the_core,this);

	collision_bounds.position = this->getPosition();
	collision_bounds.position += collision_padding;
}

sf::FloatRect Entity::get_entity_global_bounds()
{
	return this->getGlobalBounds();
}
void Entity::set_collision_padding(sf::Vector2f padding)
{
	collision_padding = padding;
}
void Entity::set_intersection_slot(Core::dual_slot_type slot)
{
	this->intersection_slot = slot;
}
sf::FloatRect Entity::get_entity_local_bounds()
{
	return this->get_collision_bounds();
}

void Entity::add_property(const std::string& name, const property_type& data)
{
	if (data.index() == 4) { this->properties[name] = std::string(std::get<const char*>(data)); return; }
	this->properties[name] = data;

}
void Entity::set_script(script ent_script)
{
	entity_script = ent_script;
}
