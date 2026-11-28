#pragma once
#include "Scene_Component.h"

#include <unordered_map>

class Group : public Scene_Component, public sf::Transformable
{
	std::unordered_map<sf::Transformable*, sf::Vector2f> data;

protected:
	const sf::Drawable* const as_drawable() const override;

	void update_resource(const std::variant<sf::Texture*, sf::Font*>&) override;
	void update() override;

	sf::FloatRect get_component_bounds() const override;
	sf::FloatRect get_component_render_bounds() const override;


public:
	Group();
	
	void set_margin(sf::Transformable* comp, const sf::Vector2f& margin);
	void add(sf::Transformable*, const sf::Vector2f& margin);
	void remove(sf::Transformable*);
};

