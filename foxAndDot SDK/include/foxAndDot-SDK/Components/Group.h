#pragma once
#include "Scene_Component.h"

#include <unordered_map>

class Group : protected Scene_Component, public sf::Transformable
{
	std::unordered_map<sf::Transformable*, sf::Vector2f> data;

	const sf::Drawable* const as_drawable() const override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>&) override;

	sf::FloatRect get_component_bounds() const override;
	sf::FloatRect get_component_render_bounds() const override;

protected:
	void update() override;

public:
	Group();
	~Group() = default;

	const Scene_Component* const as_component() const;
	
	void set_name(const std::string& group_name);
	void add(sf::Transformable*, const sf::Vector2f& margin);
	void remove(sf::Transformable*);
};

