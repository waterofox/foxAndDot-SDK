#pragma once

#include "../Components/Scene_Component.h"
#include "../Tools/Signal.h"

struct Collider_Args_Package;

class Collider : public Scene_Component
{

	Signal<Collider_Args_Package>* im_collider = nullptr;
protected:
	Signal<sf::Vector2f> collision;
private:
	
	
	void on_intersection(Scene_Component* comp)    override;
	void on_intersection(Collider* other_collider) override;

	bool colliding = true;

protected:
	sf::FloatRect collision_bounds;
private:
	sf::Vector2f last_valid_position;

public:
	sf::FloatRect get_component_bounds() override;

protected:
	void update() override;

public:
	Collider();
	~Collider();

	void set_colliding(const bool& arg);
	bool is_colliding();
};

