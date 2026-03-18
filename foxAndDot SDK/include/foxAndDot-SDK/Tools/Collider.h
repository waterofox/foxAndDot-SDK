#pragma once

#include "../Components/Scene_Component.h"
#include "../Tools/Signal.h"

struct Collider_Args_Package
{
	Collider* collider = nullptr;
	Scene_Component* other_comp = nullptr;
};

class Collider : public Scene_Component
{

	//-----------------------------------------------------------------------------------------------------------------
		sf::Vector2f last_valid_position; // The last position where there was no collision

		Signal<Collider_Args_Package>* im_collider = nullptr;

		bool colliding = true;
	//-----------------------------------------------------------------------------------------------------------------

		void on_intersection(Scene_Component* comp)    override;
		
		void on_intersection(Collider* other_collider) override;

	//-----------------------------------------------------------------------------------------------------------------

protected:

	//-----------------------------------------------------------------------------------------------------------------
		
		Signal<sf::Vector2f> collision; // This signal is called when a collision is detected. The parameter is the last valid position
		
		sf::FloatRect collision_bounds; // Dimensions and position of the collider
		
	//-----------------------------------------------------------------------------------------------------------------
		
		void update() override;

	//-----------------------------------------------------------------------------------------------------------------
public:

	Collider();
	virtual ~Collider();

	//INTERFACE
	//=================================================================================================================
	
		virtual sf::FloatRect get_component_bounds() override;

		void set_colliding(const bool& arg); // Enable/disable collisions
		
		bool is_colliding();				 // Do collisions work?

	//=================================================================================================================
};

