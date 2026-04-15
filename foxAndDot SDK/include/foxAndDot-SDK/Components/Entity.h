#pragma once

//sdk includes
#include "../Core.h"

#include "../Tools/Collider.h"
#include "../Tools/Script.h"

class  Entity : public Collider, public sf::Sprite
{
	static inline sf::Texture empty_entity_s_texture; // I don't like that sf::Sprite needs an sf::Texture. 
													  //So... this is a field to supply a default constructor argument for sf::Sprite.
	//----------------------------------------------------------------------------------------------------------------------------------

		Slot<sf::Vector2f, Entity>* handle_collision_slot = nullptr; //This slot is triggered when the parent collider's 
		void handle_collision(const sf::Vector2f&);					 //signal is called to handle a collision

	//----------------------------------------------------------------------------------------------------------------------------------	


protected:


	//----------------------------------------------------------------------------------------------------------------------------------
		
		Script* entity_script = nullptr;	  //A script describing the behavior of an Entity

	//----------------------------------------------------------------------------------------------------------------------------------
	
		sf::Vector2f collider_margin;		 //Collision area offset from the Entity position

	//----------------------------------------------------------------------------------------------------------------------------------

protected:

	//----------------------------------------------------------------------------------------------------------------------------------
		void update() override;
		void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;
	//----------------------------------------------------------------------------------------------------------------------------------

public:

	Entity(const sf::IntRect& sprite_rectangle);
	Entity(const sf::IntRect& sprite_rectangle, const int& resource_id);
	Entity(const sf::Vector2i& sprite_size);
	Entity(const sf::Vector2i& sprite_size, const int& resource_id);

	virtual ~Entity();


	//INTERFACE
	//===================================================================================================================================
		
		sf::FloatRect get_component_render_bounds() override; //Returns GlobalBounds of sf::Sprite
		sf::FloatRect get_component_bounds() override;		  //Returns collider bounds + collider margin

		sf::Drawable* as_drawable() override;

		void set_script(Script* ent_script);			      //Set a Script

	//----------------------------------------------------------------------------------------------------------------------------------

		void set_collider_margin(const sf::Vector2f& arg);    //Set the collider offset
		
		void set_collision_size(const sf::Vector2f& arg);     //Set the size of the collision
	
	//===================================================================================================================================
};