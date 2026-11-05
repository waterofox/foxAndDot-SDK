#pragma once

#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "../Tools/Slot.h"

class Visualized_Collider : public Collider, public sf::RectangleShape
{
	//----------------------------------------------------------------------------------------------------------------------
		Slot<sf::Vector2f,Visualized_Collider> v_collider_slot;
		void v_collider(const sf::Vector2f&);
	//----------------------------------------------------------------------------------------------------------------------

public:

	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
	void update() override;


	Visualized_Collider();
	Visualized_Collider(const sf::Vector2f& size);
	Visualized_Collider(const sf::FloatRect& rect);

	Visualized_Collider(const Visualized_Collider& other);
	Visualized_Collider& operator=(const Visualized_Collider& other);

		//INTERFACE
	//======================================================================================================================
		
		sf::FloatRect get_component_render_bounds() override;
		
		sf::Drawable* as_drawable() override;

	//======================================================================================================================
};

