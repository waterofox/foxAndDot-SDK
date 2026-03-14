#pragma once

#include <SFML/Graphics.hpp>

#include "../Tools/Collider.h"

class Visualized_Collider : public Collider, public sf::RectangleShape
{

private:
	void update() override;

public:
	Visualized_Collider();
	~Visualized_Collider() = default;

	void set_bounds(const sf::FloatRect& new_bounds);

	sf::FloatRect get_component_render_bounds() override;
	sf::Drawable* as_drawable() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
};

