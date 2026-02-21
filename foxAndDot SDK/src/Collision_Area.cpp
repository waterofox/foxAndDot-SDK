#include "../include/foxAndDot-SDK/Components/Collision_Area.h"

Collision_Area::Collision_Area(const sf::FloatRect& rect)
{
	
	this->colliding = true;

	this->setSize(rect.size);
	this->setPosition(rect.position);

	this->setFillColor(sf::Color(95, 234, 54, 127));
	this->setOutlineColor(sf::Color(95, 234, 54, 255));

	this->setOutlineThickness(5);
}

void Collision_Area::on_intersection(Core* the_core, Scene_Component* component){}

sf::Drawable* Collision_Area::as_drawable() { return static_cast<sf::RectangleShape*>(this); }

void Collision_Area::update() {}

sf::FloatRect Collision_Area::get_component_bounds()
{
	sf::FloatRect b; b.size = this->getSize();
	b.position = this->getPosition();
	return b;
}

sf::FloatRect Collision_Area::get_component_render_bounds()
{
	return get_component_bounds();
}

void Collision_Area::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) {}