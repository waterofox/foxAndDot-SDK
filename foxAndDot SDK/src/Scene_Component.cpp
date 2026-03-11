#include "../include/foxAndDot-SDK/Components/Scene_Component.h"


void Scene_Component::on_intersection(Scene_Component* component){}

void Scene_Component::on_intersection(Collider* component){}

void Scene_Component::update(){}

const std::string& Scene_Component::get_name()
{
	return this->component_name;
}

void Scene_Component::set_name(const std::string& new_name)
{
	this->component_name = new_name;
}

void Scene_Component::set_visble(const bool& arg) 
{ 
	visible = arg; 
}

const bool& Scene_Component::is_visible() 
{ 
	return visible; 
}

void Scene_Component::set_updatable(const bool& arg) 
{ 
	updatable = arg; 
} 	

const bool& Scene_Component::is_updatable() 
{ 
	return updatable; 
}		

void Scene_Component::set_resource(const int& arg) 
{ 
	this->resource = arg; this->ready_to_update_resource = true; 
} 

void Scene_Component::set_resource_and_type(const int& arg, const Resource_Types& arg_type) 
{ 
	set_resource(arg); this->type_of_resource = arg_type; 
} 

const int& Scene_Component::get_resource() 
{ 
	return resource; 
} 

const Resource_Types& Scene_Component::get_type_of_resource() 
{ 
	return type_of_resource; 
} 