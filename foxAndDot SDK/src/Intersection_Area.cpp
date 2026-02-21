#include "../include/foxAndDot-SDK/Components/Intersection_Area.h"

Intersection_Area::Intersection_Area(const sf::FloatRect& rect)
{
	this->colliding = false;

	this->setSize(rect.size);
	this->setPosition(rect.position);

	this->setFillColor(sf::Color(209, 76, 64, 127));
	this->setOutlineColor(sf::Color(209, 76, 64, 255));

	this->setOutlineThickness(5);
}

void Intersection_Area::on_intersection(Core* the_core, Scene_Component* component)
{
	auto comp = components_inside_area.find(component);
	if (comp == components_inside_area.end())
	{
		components_inside_area.insert(component);
		if (on_enterence != nullptr) { on_enterence(the_core, component); }
	}
}
sf::Drawable* Intersection_Area::as_drawable() { return static_cast<sf::RectangleShape*>(this); }
void Intersection_Area::update()
{
	if (!erase_buffer.empty()) { erase_buffer.clear(); }
	for (auto& element : components_inside_area)
	{
		if (!element->get_component_bounds().findIntersection(this->get_component_bounds()))
		{
			if (on_exit != nullptr) { on_exit(Core::the_core, element); }
			erase_buffer.push_back(element);
		}
	}
	for (int i = 0; i < erase_buffer.size(); ++i)
	{
		components_inside_area.erase(erase_buffer[i]);
	}
};

sf::FloatRect Intersection_Area::get_component_bounds()
{
	sf::FloatRect b; b.size = this->getSize();
	b.position = this->getPosition();
	return b;
}
sf::FloatRect Intersection_Area::get_component_render_bounds()
{
	return get_component_bounds();
}

void Intersection_Area::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) {}

void Intersection_Area::set_slot_on_enterence(const Core::slot_type& slot)
{
	on_enterence = slot;
}
void Intersection_Area::set_slot_on_exit(const Core::slot_type& slot)
{
	on_exit = slot;
}