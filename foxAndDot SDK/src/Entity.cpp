#include "../include/Core.h"

#define EENTITY std::string("ENTITY ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

Entity::Entity(const sf::IntRect& sprite_rectangle) :
	Sprite(empty_entity_s_texture, sprite_rectangle)
{
	//on_intersection = Entity::entity_on_intersection;
	this->collision_bounds = this->getGlobalBounds();
	this->colliding = false;
	last_valid_position = sf::Vector2f(0, 0);

}

void Entity::on_intersection(Core* the_core, Scene_Component* component)
{
	//collision
	if (this->colliding and component->is_colliding())
	{
		this->setPosition(last_valid_position);

		this->collision_bounds.position = this->getPosition();
		this->collision_bounds.position += this->collision_padding;
	}
	//intersection
	if (this->intersection_slot != nullptr)
	{
		this->intersection_slot(the_core, component);
	}
}


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

void Entity::update(Core* the_core)
{
	last_valid_position = this->getPosition();

	if (entity_script == nullptr) { return; }
	entity_script(the_core,this);

	collision_bounds.position = this->getPosition();
	collision_bounds.position += collision_padding;
}

sf::FloatRect Entity::get_component_bounds()
{
	return collision_bounds;
}
sf::FloatRect Entity::get_component_render_bounds()
{
	return this->getGlobalBounds();
}

void Entity::add_property(const std::string& name, const property_type& data)
{
	if (data.index() == 4) { this->properties[name] = std::string(std::get<const char*>(data)); return; }
	this->properties[name] = data;

}
void Entity::set_entity_intersection_slot(const Core::slot_type& slot)
{
	intersection_slot = slot;
}
void Entity::set_script(const script& ent_script)
{
	entity_script = ent_script;
}

void Entity::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	this->setTexture(*std::get<sf::Texture*>(resource));
}
