#pragma once
//sdk includes
#include "Scene_Component.h"

class fAD_Sprite : public Scene_Component, public sf::Sprite
{
protected:
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;

public:
	 const sf::Drawable* const as_drawable() const override;

	sf::FloatRect get_component_bounds() const override;
	sf::FloatRect get_component_render_bounds() const override;

	fAD_Sprite();
	fAD_Sprite(const sf::Texture& texture);
	fAD_Sprite(const sf::IntRect& texture_rect);
	fAD_Sprite(const sf::FloatRect& texture_frect);
	fAD_Sprite(const sf::Vector2i& size);
	fAD_Sprite(const sf::Vector2f& sizef);
};

