#pragma once
#include "Scene_Component.h"

#include <unordered_map>

class Group : protected Scene_Component, public sf::Transformable
{
	std::unordered_map<sf::Transformable*, sf::Vector2f> data;

	sf::Drawable* as_drawable() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>&) override;

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;

public:
	Group();
	~Group() = default;

	void update() override;
	
	const Scene_Component* as_component();

	void add(sf::Transformable*, const sf::Vector2f& margin);
	void remove(sf::Transformable*);
};

