#include "../include/foxAndDot-SDK/Components/Adapted_Sprite.h"

void Adapted_Sprite::update_resource(const std::variant<sf::Texture*, sf::Font*>& res)
{
	this->setTexture(*std::get<sf::Texture*>(res));
}

sf::FloatRect Adapted_Sprite::get_component_bounds()
{
	return this->getGlobalBounds();
}

sf::FloatRect Adapted_Sprite::get_component_render_bounds()
{
	return get_component_bounds();
}

sf::Drawable* Adapted_Sprite::as_drawable()
{
	return this;
}

void Adapted_Sprite::set_size(const sf::Vector2f& f_size)
{
	this->setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(int(f_size.x),int(f_size.y) )));
}

Adapted_Sprite::Adapted_Sprite() : sf::Sprite(Resource_Manager::adam)
{
	this->type_of_resource = Resource_Types::Texture;
	set_updatable(false);
	set_intersection(false);
}
