#pragma once

//sdk includes
#include "../Core.h"
#include "Collider.h"
#include "../Tools/Script.h"

//PROPERTIES
//#define Int(int_property) std::get<int>(int_property)
//#define Float(float_property) std::get<float>(float_property)
//#define Bool(bool_property) std::get<bool>(bool_property)
//#define String(string_property) std::get<std::string>(string_property)

//ENTITY
class  Entity : public Collider, public sf::Sprite
{
	static inline sf::Texture empty_entity_s_texture; // I don't like that sf::Sprite needs an sf::Texture. So... this is a field to supply a default constructor argument for sf::Sprite.

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:

	//using property_type = std::variant<int, float, bool, std::string, const char*>;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
protected:

	//EXECUTABLE STAFF
	Script* entity_script = nullptr;
	//Core::slot_type intersection_slot = nullptr;

	//PROPERTIES
	//std::map<std::string, property_type> properties;
	
	//COLLISION
	//bool colliding = false;
	//sf::Vector2f  last_valid_position;
	//sf::Vector2f  collision_margin;
	//sf::FloatRect collision_bounds;
	sf::Vector2f collider_margin;

	sf::Drawable* as_drawable() override;
	void update() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Entity(const sf::IntRect& sprite_rectangle);
	virtual ~Entity() = default;

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	//sf::FloatRect get_component_bounds()		override;

	//void set_entity_intersection_slot(const Core::slot_type& slot); //Replacing the function that handles the intersection of an entity with another component
	void set_script(Script* ent_script);						 //Replace the script

	//property_type& operator[](const std::string& name);		//get property (You can control it)
	//property_type& operator[](const char*& name);			//get property (You can control it)
	//void add_property(const std::string& name, const property_type& data); //add property (int/float/bool/string/const char*)

	//bool  is_colliding();
	//void set_colliding(const bool& arg);
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};