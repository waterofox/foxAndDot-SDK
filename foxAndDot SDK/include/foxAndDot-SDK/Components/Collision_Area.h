#pragma once

//sdk includes

//todo erase core

#include "../Core.h"
#include "Scene_Component.h"

//COLLISION AREA

class  Collision_Area : public Scene_Component, public sf::RectangleShape
{

	//OVERRIDED METHODS & METHODS
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Collision_Area(const sf::FloatRect& rect);
	~Collision_Area() = default;

	// INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds()		override;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};