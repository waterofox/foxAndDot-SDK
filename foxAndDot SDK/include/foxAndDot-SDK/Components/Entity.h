#pragma once

//sdk includes
#include "../Core.h"
#include "Scene_Component.h"

//ENTITY
class  Entity : public Scene_Component, public sf::Sprite
{
	static inline sf::Texture empty_entity_s_texture; // I don't like that sf::Sprite needs an sf::Texture. So... this is a field to supply a default constructor argument for sf::Sprite.

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:
	using script = std::function<void(Core*, Entity*)>;

	using property_type = std::variant<int, float, bool, std::string, const char*>;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:
	script entity_script = nullptr;
	Core::slot_type intersection_slot = nullptr;

	std::map<std::string, property_type> properties;

	//OVERRIDED METHODS & METHODS
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Entity(const sf::IntRect& sprite_rectangle);
	virtual ~Entity() = default;

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds()		override;

	void set_entity_intersection_slot(const Core::slot_type& slot); //Replacing the function that handles the intersection of an entity with another component
	void set_script(const script& ent_script);						 //Replace the script

	property_type& operator[](const std::string& name);		//get property (You can control it)
	property_type& operator[](const char*& name);			//get property (You can control it)
	void add_property(const std::string& name, const property_type& data); //add property (int/float/bool/string/const char*)

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};