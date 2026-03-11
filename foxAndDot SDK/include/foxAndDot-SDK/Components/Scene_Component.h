#pragma once

//std  includes
#include <string>
#include <iostream>

//sfml includes
#include <SFML/Graphics.hpp>

//sdk  includes
#include "../Tools/Resource_Types.h"

class Collider;

class Scene_Component
{
	friend class Core;
	friend class Resource_Manager;


protected:
	//-------------------------------------------------------------------------------------------------------------------

		std::string component_name;			  // Name of component
		
		bool visible = true;				  // When true => component is visible
		
		bool updatable = true;				  // When true => component will update every iteration of game cycle

		//todo : remake it as signal
		bool ready_to_update_resource = true; // True when you are changing the resource (Marker for Resource Manager)

	//-------------------------------------------------------------------------------------------------------------------

		int resource;						  // Resource's identifi

		Resource_Types type_of_resource;      // Type of resource which component prefers
	
	//-------------------------------------------------------------------------------------------------------------------
		
		virtual void update();				                           // How does the component behave during Core operation
		
		virtual void update_resource(const std::variant<sf::Texture*,\
								     sf::Font*>& resource) = 0;        // How component updates it's resource
	
	//-------------------------------------------------------------------------------------------------------------------


public:

	virtual ~Scene_Component() = default;

	//INTERFACE
	//================================================================================================================================================================

		virtual void on_intersection(Scene_Component* component); // How component will react on intersection with other component?

		virtual void on_intersection(Collider* component);		  // How component wiil react on intersection with collider component?

		virtual sf::FloatRect get_component_bounds() = 0;         // Returns the bounds that are used to determine whether a component intersects with other components
		
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

		virtual sf::Drawable* as_drawable() = 0;                 // What you need to draw?

		virtual sf::FloatRect get_component_render_bounds() = 0; // Returns the bounds that are used to determine whether the component intersects with the camera

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
		const std::string& get_name();				// Get name of component
		
		void set_name(const std::string& new_name); // Set name of Component

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
		void set_visble(const bool& arg);	 // When set_visible(true) component will be drawn by Core					
		
		const bool& is_visible();			 // Return visible						


		void set_updatable(const bool& arg); // When set_updateble(true) component will be updated by Core							
		
		const bool& is_updatable();			 // Return updateble

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------

		void set_resource(const int& arg);							//set current resource (ATTENTION! NOT SAFE)
		
		void set_resource_and_type(const int& arg,\
								   const Resource_Types& arg_type); //set current resource

		const int& get_resource();									//returns the resource ID that is used by the component 
	
		const Resource_Types& get_type_of_resource();               //returns the resource type used by the component 

	//================================================================================================================================================================
};