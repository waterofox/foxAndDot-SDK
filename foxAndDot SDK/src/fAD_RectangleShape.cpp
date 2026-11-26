#include "../include/foxAndDot-SDK/Components/fAD_RectangleShape.h"

void fAD_RectangleShape::update_resource(const Type_Res&)
{
}

fAD_RectangleShape::fAD_RectangleShape()
{
	set_resource_and_type(-1, Resource_Types::Undefined);
	set_intersection(false);
	set_updatable(false);
}

fAD_RectangleShape::fAD_RectangleShape(const sf::RectangleShape& rsh) : RectangleShape(rsh)
{
	set_resource_and_type(-1, Resource_Types::Undefined);
	set_intersection(false);
	set_updatable(false);
}

fAD_RectangleShape::fAD_RectangleShape(const sf::Vector2f& size) : fAD_RectangleShape()
{
	setSize(size);
}

sf::FloatRect fAD_RectangleShape::get_component_bounds() const
{
	return getGlobalBounds();
}

sf::FloatRect fAD_RectangleShape::get_component_render_bounds() const
{
	return get_component_bounds();
}

const sf::Drawable* const fAD_RectangleShape::as_drawable() const
{
	return this;
}
