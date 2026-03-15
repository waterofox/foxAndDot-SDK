#pragma once

#include <SFML/Graphics.hpp>

#include "../Tools/Collider.h"
#include "../Tools/Slot.h"

class Visualized_Collider : public Collider, public sf::RectangleShape
{
	//----------------------------------------------------------------------------------------------------------------------
		Slot<sf::Vector2f> v_collider_slot;

		void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
		void update() override;
	//----------------------------------------------------------------------------------------------------------------------

public:
		Visualized_Collider();
		~Visualized_Collider() = default;
	
		//INTERFACE
	//======================================================================================================================

		void set_bounds(const sf::FloatRect& new_bounds);		//Set collider bounds
		
		sf::FloatRect get_component_render_bounds() override;
		
		sf::Drawable* as_drawable() override;

	//======================================================================================================================
};

