#include "../../include/foxAndDot-SDK/Components/fAD_Text.h"

#include "../../include/foxAndDot-SDK/Resource_Manager.h"

sf::Drawable* fAD_Text::as_drawable()
{
	return this;
}

void fAD_Text::update_resource(const std::variant<sf::Texture*, sf::Font*>& res)
{
	setFont(*std::get<sf::Font*>(res));
}

sf::FloatRect fAD_Text::get_component_bounds()
{
	return getGlobalBounds();
}

sf::FloatRect fAD_Text::get_component_render_bounds()
{
	return get_component_bounds();
}

fAD_Text::fAD_Text() : sf::Text(Resource_Manager::eva)
{
	set_resource_and_type(-1, Resource_Types::Font);
	set_updatable(false);
	set_intersection(false);
}

fAD_Text::fAD_Text(const sf::Font& font) : fAD_Text()
{
	setFont(font);
}

fAD_Text::fAD_Text(const std::string& str) : fAD_Text()
{
	setString(str);
}

fAD_Text::fAD_Text(const sf::String& sfstr) : fAD_Text()
{
	setString(sfstr);
}