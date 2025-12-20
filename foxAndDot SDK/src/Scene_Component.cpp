#include "../include/foxAndDot-SDK/Components/Scene_Component.h"

std::string& Scene_Component::name()
{
	return this->component_name;
}

void Scene_Component::set_visble(const bool& arg) { visible = arg; }

const bool& Scene_Component::is_visible() { return visible; };

void Scene_Component::set_updateble(const bool& arg) { updateble = arg; } //when set_updateble(true) component will be updated by Core							
const bool& Scene_Component::is_updateble() { return updateble; }		 //return updateble

void Scene_Component::set_colliding(const bool& arg) { colliding = arg; } //when set_colliding(true) component will collide with other components
const bool& Scene_Component::is_colliding() { return colliding; };		 //retunr colliding

sf::FloatRect& Scene_Component::get_collision_bounds() { return collision_bounds; }; //returns the bounds of the component's collision (you can control it)
void Scene_Component::set_collision_bounds(const sf::FloatRect& bounds) { collision_bounds = bounds; } //set bounds of collisions
void Scene_Component::set_collision_padding(const sf::Vector2f& padding) { collision_padding = padding; } //the default values are 0 and 0, which means that the coordinates of the collision rectangle match the coordinates of the component

const sf::Vector2f& Scene_Component::get_last_valid_position() { return last_valid_position; } //will return the last position of the component where it did not collide with another

void Scene_Component::set_resource(const int& arg) { this->resource = arg; this->ready_to_update_resource = true; } //set current resource (ATTENTION! NOT SAFE)
void Scene_Component::set_resource_and_type(const int& arg, const int& arg_type) { set_resource(arg); this->type_of_resource = arg_type; } //set current resource

const int& Scene_Component::get_resource() { return resource; } //returns the resource ID that is used by the component 
const int& Scene_Component::get_type_of_resource() { return type_of_resource; } //returns the resource type used by the component 