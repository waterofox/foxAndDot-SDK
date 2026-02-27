#pragma once

//std includes
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

class Resource_Manager;
class Core;

//SCENE COMPONENT
class Scene_Component
{
	//todo changed
	friend class Core;
	friend class Resource_Manager;

protected:
	std::string component_name;
	bool visible = true;
	bool updateble = true;
	bool ready_to_update_resource = true; //true when you are changing the resource

	int resource;
	int type_of_resource;
	
	//todo changed53
	//sf::Vector2f last_valid_position;
	bool colliding;
	//sf::FloatRect collision_bounds = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	//sf::Vector2f collision_padding = sf::Vector2f(0, 0);

	//VIRTUAL METHODS & METHODS
protected:
	virtual void on_intersection(Core* the_core, Scene_Component* component) = 0; //How the component reacts to the intersection
	//todo changed
	virtual void update() = 0; //How does the component behave during Core operation
	virtual void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) = 0; //How component updates it's resource

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:
	virtual sf::Drawable* as_drawable() = 0; //What you need to draw

	virtual sf::FloatRect get_component_render_bounds() = 0; //Returns the bounds that are used to determine whether the component intersects with the camera
	virtual sf::FloatRect get_component_bounds() = 0; //Returns the bounds that are used to determine whether a component intersects with other components

	//todo changed*
	//std::string& name(); //get name (You can control it)	
	const std::string& get_name();
	void set_name(const std::string& new_name);
	
	//VISIBLE
	void set_visble(const bool& arg);	//when set_visible(true) component will be drawn by Core					
	const bool& is_visible();	//return visible						

	//UPDATEBLE**666
	void set_updateble(const bool& arg);//when set_updateble(true) component will be updated by Core							
	const bool& is_updateble(); //return updateble

	//todo changed
	//COLLISION
	//void set_colliding(const bool& arg); //when set_colliding(true) component will collide with other components
	const bool& is_colliding(); //retunr colliding

	//sf::FloatRect& get_collision_bounds(); //returns the bounds of the component's collision (you can control it)
	//void set_collision_bounds(const sf::FloatRect& bounds); //set bounds of collisions
	//void set_collision_padding(const sf::Vector2f& padding); //the default values are 0 and 0, which means that the coordinates of the collision rectangle match the coordinates of the component

	//const sf::Vector2f& get_last_valid_position(); //will return the last position of the component where it did not collide with another

	//RESOURCES
	void set_resource(const int& arg); //set current resource (ATTENTION! NOT SAFE)
	void set_resource_and_type(const int& arg, const int& arg_type); //set current resource

	const int& get_resource();  //returns the resource ID that is used by the component 
	const int& get_type_of_resource(); //returns the resource type used by the component 

	virtual ~Scene_Component() = default;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};