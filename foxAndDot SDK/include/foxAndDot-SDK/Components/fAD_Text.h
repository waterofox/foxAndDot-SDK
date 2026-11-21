#pragma once

//sdk includes
#include "Scene_Component.h"

class fAD_Text : public Scene_Component, public sf::Text
{
public:
	sf::Drawable* as_drawable() override;

	void update_resource(const std::variant<sf::Texture*, sf::Font*>& res) override;

	sf::FloatRect get_component_bounds() override;
	sf::FloatRect get_component_render_bounds() override;

	fAD_Text();
	fAD_Text(const sf::Font& font);
	fAD_Text(const std::string& str);
	fAD_Text(const sf::String& sfstr);
	~fAD_Text() = default;
};

