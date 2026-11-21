#include "../include/foxAndDot-SDK/Components/fAD_Sprite.h"

#include "../include/foxAndDot-SDK/Resource_Manager.h"

sf::Drawable* fAD_Sprite::as_drawable()
{
	return this;
}

void fAD_Sprite::update_resource(const std::variant<sf::Texture*, sf::Font*>& res)
{
	setTexture(*std::get<sf::Texture*>(res));
}


sf::FloatRect fAD_Sprite::get_component_bounds()
{
	return getGlobalBounds();
}

sf::FloatRect fAD_Sprite::get_component_render_bounds()
{
	return get_component_render_bounds();
}

fAD_Sprite::fAD_Sprite() : sf::Sprite(Resource_Manager::adam)
{
	set_resource_and_type(0, Resource_Types::Texture);
	set_updatable(false);
	set_intersection(false);
}

fAD_Sprite::fAD_Sprite(const sf::Texture& texture) : fAD_Sprite()
{
	setTexture(texture);
}

fAD_Sprite::fAD_Sprite(const sf::IntRect& texture_rect) : fAD_Sprite()
{
	setTextureRect(texture_rect);
}

fAD_Sprite::fAD_Sprite(const sf::FloatRect& texture_frect) : 
	fAD_Sprite(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(int(texture_frect.size.x),int(texture_frect.size.y)))){}

fAD_Sprite::fAD_Sprite(const sf::Vector2i& size) : fAD_Sprite(sf::IntRect(sf::Vector2i(0,0),size)){}

fAD_Sprite::fAD_Sprite(const sf::Vector2f& sizef) : fAD_Sprite(sf::Vector2i(int(sizef.x),int(sizef.y))){}
