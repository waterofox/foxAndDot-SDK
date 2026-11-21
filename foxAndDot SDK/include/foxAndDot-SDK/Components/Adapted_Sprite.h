#pragma once

//sdk includes
#include "../Core.h"

class Adapted_Sprite : public Scene_Component, public sf::Sprite
{
	static inline sf::Texture txt;

	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;

	sf::Drawable* as_drawable() override;

public:
	void set_size(const sf::Vector2f& f_size);

	Adapted_Sprite();
	~Adapted_Sprite() = default;
};

