#include "../include/foxAndDot-SDK/Components/Visualized_Collider.h"
#include "../include/foxAndDot-SDK/Core.h"


void Visualized_Collider::update()
{
	Collider::update();

	this->collision_bounds = this->getGlobalBounds();

}

Visualized_Collider::Visualized_Collider()
{
	this->type_of_resource = Resource_Types::Undefined;

	this->setFillColor(sf::Color(144, 238, 144, 100));
	this->setOutlineColor(sf::Color(144, 238, 144, 255));
	this->setOutlineThickness(-1);

	this->v_collider_slot = Slot<sf::Vector2f, Visualized_Collider>(&Visualized_Collider::v_collider, this);
	connect(&this->collision, &this->v_collider_slot);
}

Visualized_Collider::Visualized_Collider(const sf::Vector2f& size) : Visualized_Collider()
{
	this->setSize(size);
}

Visualized_Collider::Visualized_Collider(const sf::FloatRect& rect) : Visualized_Collider(rect.size)
{
	this->setPosition(rect.position);
}

sf::FloatRect Visualized_Collider::get_component_render_bounds()
{
	return this->getGlobalBounds();
}

sf::Drawable* Visualized_Collider::as_drawable()
{
	return static_cast<sf::RectangleShape*>(this);
}

void Visualized_Collider::v_collider(const sf::Vector2f&)
{
}

void Visualized_Collider::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	
}
