#pragma once

#include <SFML/Graphics.hpp>

#include "../Tools/Collider.h"
#include "../Tools/Slot.h"

class Visualized_Collider : public Collider, public sf::RectangleShape
{
	//----------------------------------------------------------------------------------------------------------------------
		Slot<sf::Vector2f,Visualized_Collider>* v_collider_slot = nullptr;
		void v_collider(const sf::Vector2f&);

		void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
		void update() override;
	//----------------------------------------------------------------------------------------------------------------------

public:
		Visualized_Collider(const sf::FloatRect& rect);
		~Visualized_Collider() = default;
	
		//INTERFACE
	//======================================================================================================================
		
		sf::FloatRect get_component_render_bounds() override;
		
		sf::Drawable* as_drawable() override;

	//======================================================================================================================
};

