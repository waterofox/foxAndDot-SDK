#pragma once

//sdk includes
#include "../Core.h"

#include "Collider.h"
#include "../Tools/Script.h"

class  Entity : public Collider, public sf::Sprite
{
	//----------------------------------------------------------------------------------------------------------------------------------
		Slot<sf::Vector2f, Entity> handle_collision_slot; //This slot is triggered when the parent collider's 
		void handle_collision(const sf::Vector2f&);		  //signal is called to handle a collision

		sf::Vector2f collider_margin;		 //Collision area offset from the Entity position
	//----------------------------------------------------------------------------------------------------------------------------------	
		Script* entity_script = nullptr;	  //A script describing the behavior of an Entity
	//----------------------------------------------------------------------------------------------------------------------------------

protected:
	//----------------------------------------------------------------------------------------------------------------------------------				
		void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
		void update() override;
	//----------------------------------------------------------------------------------------------------------------------------------

public:
	Entity();
	Entity(const int& resource_id);
	Entity(const sf::Vector2i& size);
	Entity(const sf::Vector2i& size, const int& resource_id);
	Entity(const sf::IntRect& rect);
	Entity(const sf::IntRect& rect, const int& resource_id);

	Entity(const Entity& other);
	virtual Entity& operator=(const Entity& other);

	virtual ~Entity() = default;

	//INTERFACE
	//===================================================================================================================================
		sf::FloatRect get_component_render_bounds() const override; //Returns GlobalBounds of sf::Sprite
		sf::FloatRect get_component_bounds() const override;		//Returns collider bounds + collider margin

		const sf::Drawable* const as_drawable() const override;
	//----------------------------------------------------------------------------------------------------------------------------------
		void set_script(Script* ent_script);			      //Set a Script
	//----------------------------------------------------------------------------------------------------------------------------------
		void set_collider_margin(const sf::Vector2f& arg);    //Set the collider offset
	//===================================================================================================================================
};