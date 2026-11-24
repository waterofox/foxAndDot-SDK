#pragma once

//std inclides
#include <set>

//sdk includes
#include "Scene_Component.h"
#include "../Tools/connect.h"


class  Intersection_Area : public Scene_Component, public sf::RectangleShape
{
	//----------------------------------------------------------------------------------------------------------------
		std::set<Scene_Component*> components_inside_area;
		std::vector<Scene_Component*> erase_buffer;
	//----------------------------------------------------------------------------------------------------------------

protected:
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
	void update() override;
	void on_intersection(Scene_Component* component) override;

public:
	Intersection_Area();
	Intersection_Area(const sf::Vector2f& size);
	Intersection_Area(const sf::FloatRect& rect);

	//INTERFACE
	//================================================================================================================
		Signal<Scene_Component*> component_in;	// Emited when component in
		Signal<Scene_Component*> component_out; // Emited when component out
	//----------------------------------------------------------------------------------------------------------------
		const sf::Drawable*  const as_drawable() const override;
	//----------------------------------------------------------------------------------------------------------------
		sf::FloatRect get_component_render_bounds() const override;
		sf::FloatRect get_component_bounds() const override;
	//================================================================================================================

};