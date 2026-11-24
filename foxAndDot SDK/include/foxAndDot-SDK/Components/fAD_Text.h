#pragma once

//sdk includes
#include "Scene_Component.h"

class fAD_Text : public Scene_Component, public sf::Text
{
protected:
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;

public:
	const  sf::Drawable* const as_drawable() const override;

	sf::FloatRect get_component_bounds() const override;
	sf::FloatRect get_component_render_bounds() const override;

	fAD_Text();
	fAD_Text(const sf::Font& font);
	fAD_Text(const std::string& str);
	fAD_Text(const sf::String& sfstr);
};

