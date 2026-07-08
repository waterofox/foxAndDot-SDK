#pragma once

//std inclides
#include <set>

//sdk includes
#include "Scene_Component.h"
#include "../Tools/Signal.h"


class  Intersection_Area : public Scene_Component, public sf::RectangleShape
{
	//----------------------------------------------------------------------------------------------------------------
		
		std::set<Scene_Component*> components_inside_area;
		std::vector<Scene_Component*> erase_buffer;

	//----------------------------------------------------------------------------------------------------------------

		void update() override;
		void on_intersection(Scene_Component* component) override;
		void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

	//----------------------------------------------------------------------------------------------------------------

public:

	Intersection_Area();
	Intersection_Area(const sf::Vector2f& size);
	Intersection_Area(const sf::FloatRect& rect);
	~Intersection_Area() = default;

	//INTERFACE
	//================================================================================================================

		Signal<Scene_Component*> component_in;	// Emited when component in
		
		Signal<Scene_Component*> component_out; // Emited when component out

	//----------------------------------------------------------------------------------------------------------------

		sf::Drawable* as_drawable() override;

		sf::FloatRect get_component_render_bounds() override;
		
		sf::FloatRect get_component_bounds()		override;

	//================================================================================================================

};