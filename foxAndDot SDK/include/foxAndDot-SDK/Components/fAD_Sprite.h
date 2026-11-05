#pragma once
//sdk includes
#include "Scene_Component.h"

class fAD_Sprite : public Scene_Component, public sf::Sprite
{
public:
	sf::Drawable* as_drawable() override;

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;

	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;

	fAD_Sprite();
	fAD_Sprite(const sf::Texture& texture);
	fAD_Sprite(const sf::IntRect& texture_rect);
	fAD_Sprite(const sf::FloatRect& texture_frect);
	fAD_Sprite(const sf::Vector2i& size);
	fAD_Sprite(const sf::Vector2f& sizef);


	~fAD_Sprite() = default;
};

