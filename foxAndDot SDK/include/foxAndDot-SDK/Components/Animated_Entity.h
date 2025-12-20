#pragma once

#include "Entity.h"

//todo erase <include 'Core.h'>

//ANIMATED ENTITY
class  Animated_Entity : public Entity
{
private:
	bool animation_enabled = false;
	sf::Time animation_timer = sf::Time::Zero;

public:
	Animated_Entity(const sf::IntRect& sprite_rectangle);
	~Animated_Entity() = default;


	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	int frame_count = 1;		//the number of frames in the current resource
	int frame_per_seconds = 24; //fps
	int current_frame = 0;		//current frame (the current resource is used)

	void play_animation();	//play the animation  (the current resource is used)
	void pause_animation(); //pause the animation (the current resource is used)

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

protected:
	void update(Core* the_core) override;
};