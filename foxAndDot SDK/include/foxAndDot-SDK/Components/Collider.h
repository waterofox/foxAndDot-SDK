#pragma once

#include "../Components/Scene_Component.h"
#include "../Tools/connect.h"

struct Collider_Args_Package
{
	Collider* collider = nullptr;
	Scene_Component* other_comp = nullptr;
};

class Collider : public Scene_Component
{
	//-----------------------------------------------------------------------------------------------------------------
		Signal<Collider_Args_Package>im_collider;
		sf::Vector2f last_valid_position; 
		bool colliding = true;
	//-----------------------------------------------------------------------------------------------------------------

protected:
	//-----------------------------------------------------------------------------------------------------------------
		Signal<sf::Vector2f> collision; // This signal is called when a collision is detected. The parameter is the last valid position
		sf::FloatRect collision_bounds; // Dimensions and position of the collider

		void on_intersection(Scene_Component* comp)    override;
		void on_intersection(Collider* other_collider) override;
	//-----------------------------------------------------------------------------------------------------------------
		void update() override;
	//-----------------------------------------------------------------------------------------------------------------

public:
	Collider();
	Collider(const Collider& other);

	virtual ~Collider() = default;

	//INTERFACE
	//=================================================================================================================
		virtual sf::FloatRect get_component_bounds() const override;

		void set_collision_size(const sf::Vector2f& size);  // Change current  
		sf::Vector2f get_collision_size() const;			// Returns current bounds of collision

		void set_colliding(const bool& arg); // Enable/disable collisions
		bool is_colliding() const;		     // Do collisions work?
	//=================================================================================================================
};

