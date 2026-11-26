#pragma once

#include "Scene_Component.h"

#include <SFML/Graphics/RectangleShape.hpp>

class fAD_RectangleShape : public Scene_Component, public sf::RectangleShape
{
protected:
	void update_resource(const Type_Res& res);

public:
	fAD_RectangleShape();
	fAD_RectangleShape(const sf::RectangleShape&);
	fAD_RectangleShape(const sf::Vector2f& size);

	sf::FloatRect get_component_bounds() const override;
	sf::FloatRect get_component_render_bounds() const override;

	const sf::Drawable* const as_drawable() const override;
};
