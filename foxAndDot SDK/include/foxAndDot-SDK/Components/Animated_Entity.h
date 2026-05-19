#pragma once

//sdk includes
#include "Entity.h"


class  Animated_Entity : public Entity
{
private:

	//---------------------------------------------------------------------------------------------------------------
		
		bool animation_enabled = false;				// When true then animation is playing

		sf::Time animation_timer = sf::Time::Zero;  // Timer for changing frames

	//---------------------------------------------------------------------------------------------------------------

		void update() override;

	//---------------------------------------------------------------------------------------------------------------

public:
	Animated_Entity();
	Animated_Entity(const int& resource_id);
	Animated_Entity(const sf::Vector2i& size);
	Animated_Entity(const sf::Vector2i& size, const int& resource_id);
	Animated_Entity(const sf::IntRect& rect);
	Animated_Entity(const sf::IntRect& rect, const int& resource_id);
	
	virtual ~Animated_Entity() = default;

	//INTERFACE
	//===============================================================================================================
	
		int frame_count = 1;		// The number of frames in the current resource
		
		int frame_per_seconds = 24; // Fps
		
		int current_frame = 0;		// Current frame (the current resource is used)

	//---------------------------------------------------------------------------------------------------------------

		void play_animation();	// Play  animation  (the current resource is used)
		
		void pause_animation(); // Pause animation (the current resource is used)

	//===============================================================================================================

};