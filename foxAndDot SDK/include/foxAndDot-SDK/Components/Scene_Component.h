#pragma once

//std includes
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

class Collider;

class Scene_Component
{
	friend class Core;
	friend class Resource_Manager;

protected:
	std::string component_name;
	bool visible = true;
	bool updateble = true;
	bool ready_to_update_resource = true; //true when you are changing the resource

	int resource;
	int type_of_resource;


protected:
	virtual void update(); //How does the component behave during Core operation
	virtual void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) = 0; //How component updates it's resource

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:
	virtual void on_intersection(Scene_Component* component);
	virtual void on_intersection(Collider* component);

	virtual sf::Drawable* as_drawable() = 0; //What you need to draw

	virtual sf::FloatRect get_component_render_bounds() = 0; //Returns the bounds that are used to determine whether the component intersects with the camera
	virtual sf::FloatRect get_component_bounds() = 0; //Returns the bounds that are used to determine whether a component intersects with other components

	const std::string& get_name();
	void set_name(const std::string& new_name);
	

	void set_visble(const bool& arg);	//when set_visible(true) component will be drawn by Core					
	const bool& is_visible();	//return visible						

	void set_updateble(const bool& arg);//when set_updateble(true) component will be updated by Core							
	const bool& is_updateble(); //return updateble

	void set_resource(const int& arg); //set current resource (ATTENTION! NOT SAFE)
	void set_resource_and_type(const int& arg, const int& arg_type); //set current resource

	const int& get_resource();  //returns the resource ID that is used by the component 
	const int& get_type_of_resource(); //returns the resource type used by the component 

	virtual ~Scene_Component() = default;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};