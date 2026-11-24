#pragma once

//std  includes
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

//sdk  includes
#include "../Tools/Resource_Types.h"
#include "../Tools/connect.h"

class Collider;

using Type_Res = std::variant<sf::Texture*, sf::Font*>;

class Scene_Component
{
	friend class Core;
	friend class Resource_Manager;

//--------------------------------------------------------------------------------------------------------------------------------------
	int resource = 1;
	Resource_Types type_of_resource = Resource_Types::Undefined;      
	Signal<Scene_Component*> ready_for_update_resource;
//--------------------------------------------------------------------------------------------------------------------------------------
	std::string component_name;  // Name of component
	
	bool visible = true;	    // When true => component is visible
	bool updatable = true;		// When true => component will update every iteration of game cycle
	bool intersection = false;  // When true => Core will check intersections with other components
//--------------------------------------------------------------------------------------------------------------------------------------

protected:
		virtual void update_resource(const Type_Res& resource) = 0;  // How component updates it's resource?
		virtual void update();										 // How component updates it's logic?

		virtual void on_intersection(Scene_Component* component);  // How component will react on intersection with other component?
		virtual void on_intersection(Collider* component);		   // How component wiil react on intersection with collider component?

public:
	Scene_Component();

	virtual ~Scene_Component() = default;

	//INTERFACE
	//================================================================================================================================================================
		virtual sf::FloatRect get_component_bounds() const  = 0; // Returns the bounds that are used to determine whether a component intersects with other components
		
		bool is_intersection() const;			 // Returns intersection
		void set_intersection(const bool& arg);  // When set_intersection(true) Core will check intersections with other components
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
		virtual sf::FloatRect get_component_render_bounds() const = 0;  // Returns the bounds that are used to determine whether the component intersects with the camera (sf::View)

		virtual const sf::Drawable* const as_drawable() const = 0;  // What you need to draw?
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
		const std::string& get_name() const;        // Get name of component
		void set_name(const std::string& new_name); // Set name of Component
	
		void set_visble(const bool& arg);  // When set_visible(true) component will be drawn by Core					
		bool is_visible() const; 		   // Returns visible						

		void set_updatable(const bool& arg);  // When set_updateble(true) component will be updated by Core								
		bool is_updatable() const;	  // Returns updateble
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
		void set_resource_and_type(const int& arg, const Resource_Types& arg_type); //set current resource
		void set_resource(const int& arg);							                //set current resource (ATTENTION! NOT SAFE)

		int get_resource() const;			         //returns the resource ID that is used by the component 
		Resource_Types get_type_of_resource() const;  //returns the resource type used by the component 
	//================================================================================================================================================================
};