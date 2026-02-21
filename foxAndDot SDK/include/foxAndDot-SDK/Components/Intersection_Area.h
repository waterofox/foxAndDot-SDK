#pragma once

//sdk includes

#include "../Core.h"
#include "Scene_Component.h"

//INTERSECTION AREA

class  Intersection_Area : public Scene_Component, public sf::RectangleShape
{
	std::set<Scene_Component*> components_inside_area;
	std::vector<Scene_Component*> erase_buffer;

	Core::slot_type on_enterence = nullptr;
	Core::slot_type on_exit = nullptr;

	//OVERRIDED METHODS & METHODS
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;


public:
	Intersection_Area(const sf::FloatRect& rect);
	~Intersection_Area() = default;

	// INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds()		override;

	void set_slot_on_enterence(const Core::slot_type& slot); //What happens when a component steps into an area
	void set_slot_on_exit(const Core::slot_type& slot);      //What happens when the component leaves the area

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};