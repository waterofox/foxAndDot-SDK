#pragma once

//sfml includes
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//std inlcludes
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <variant>
#include <queue>

//ERRORS
#define ECORE std::string("CORE ERROR: ")
#define EENTITY std::string("ENTITY ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

//PROPERTIES
#define Int(int_property) std::get<int>(int_property)
#define Float(float_property) std::get<float>(float_property)
#define Bool(bool_property) std::get<bool>(bool_property)
#define String(string_property) std::get<std::string>(string_property)

class Scene_Component;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CORE

class Core : public sf::RenderWindow 
{
//TYPES & ENUMS
public:
	
	//ENUMS
	enum camera_settings
	{
		dynamic_camera = 0,
		static_camera = 1
	};
	
	//FUNCTION TYPES
	using process_events_function = void(*)(Core*);

	using slot_type = void(*)(Core*, Scene_Component*);

	using dual_slot_type = void(*)(Core*, Scene_Component*, Scene_Component*);
	
	//CONTAINERS
	using signals_container = std::pair<std::variant<slot_type, dual_slot_type>, std::pair<Scene_Component*, Scene_Component*>>;

	using lay_type = std::map<std::string, Scene_Component*>;

	using scene_type = std::vector<lay_type>;

//FIELDS
private:

	//WINDOW
	sf::Time delta_time = sf::Time::Zero;

	//CAMERA
	sf::View	camera;
	camera_settings camera_mod = camera_settings::static_camera;
	std::string camera_target = "";

	//SIGNALS SYSTEM
	std::queue<signals_container> signals_queue;
	std::map<int, std::variant<slot_type, dual_slot_type>> connections;

public:
	
	//SCENE
	std::string scene_name;
	scene_type scene;
	
//METHODS
	Core();
	~Core();

	//WINDOW
	const sf::Time& get_delta_time();

	//CAMERA
	sf::View& get_camera();
	void set_camera_mod(const camera_settings& mod);
	void set_camera_target(const std::string& name_of_target);
	
	//SETTINGS & RUN
	void run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title, const sf::State& state);
	void set_process_events_function(const process_events_function& function);

	//COMPONENTS
	Scene_Component* get_component(const std::string& name);
	Scene_Component* get_component(const std::string& name, const int& lay);
	
	//SIGNALS SYSTEM
	void emit_signal(const int& signal_id, Scene_Component*&);
	void emit_signal(const int& signal_id, Scene_Component*&,Scene_Component*&);
	void connect(const int& signal_id, const std::variant<slot_type, dual_slot_type>& slot);

//PROCESS METHODS
private:

	//PROCESS
	process_events_function process_events = nullptr;
	void process_signals();
	void process_intersections_and_collisions();

	//UPDATE
	void update();
	void update_camera();

	//RENDER
	void render();
	
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SCENE COMPONENT

class Scene_Component
{
	friend class Core;

//FIELDS

	//WORK STAFF
	std::string component_name;
	bool visible = true;
	bool updateble = true;

protected:

	//PROCESS INTERSECTIONS
	Core::dual_slot_type on_intersection = nullptr;

//METHODS
public:
	
	//WORK STAFF
	std::string& name() { return component_name; }											//retunr name   of component

	void set_visble(const bool& arg) { visible = arg; }										//set visible   of component
	const bool& is_visible() { return visible; };											//check visible

	void set_updateble(const bool& arg) { updateble = arg; }								//set updatable of component
	const bool& is_updateble() { return updateble; };
	
	//PROCESS INTERSECTIONS
	void set_on_intersection(Core::dual_slot_type slot) { on_intersection = slot; }			//set slot on intersection

//VIRTUAL METHODS

	//WORK
	virtual sf::Drawable* as_drawable() { return nullptr; }									//retunr component as sf::Drawable* for render
	virtual void update(Core* the_core) = 0;												//method to update logic
	
	//BOUNDS
	virtual sf::FloatRect get_entity_global_bounds() = 0;									//return global bounds (scaling)
	virtual sf::FloatRect get_entity_local_bounds() = 0;									//return local  bounds (no scaling)

	//RESOURCES
	virtual void set_resource(const std::variant<sf::Texture*,sf::Font*>& resource) = 0;	// set/update resource for component
};




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ENTITY

class Entity : public Scene_Component, public sf::Sprite
{

	friend class Core;

	static void entity_on_intersection(Core* the_core, Scene_Component* elementA, Scene_Component* elementB)
	{
		Entity* entityA = static_cast<Entity*>(elementA);
		Entity* entityB = static_cast<Entity*>(elementB);
		//collision
		if (entityA->colliding and entityB->colliding) 
		{
			entityA->setPosition(entityA->get_last_valid_position());

			entityA->collision_bounds.position = entityA->getPosition();
			entityA->collision_bounds.position += entityA->collision_padding;
		}
		//intersection
		if (entityA->intersection_slot != nullptr)
		{
			entityA->intersection_slot(the_core, elementA, elementB);
		}
	}
public:
	using script = void(*)(Core*,Entity*);
	using property_type = std::variant<int, float, bool, std::string, const char*>;

private:
	script entity_script = nullptr;
	Core::dual_slot_type intersection_slot = nullptr;

	sf::Vector2f last_valid_position;

	std::map<std::string, property_type> properties;
	bool colliding;
	sf::FloatRect collision_bounds = sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(0,0));
	sf::Vector2f collision_padding = sf::Vector2f(0, 0);

public:

	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override; 
	sf::FloatRect get_entity_global_bounds() override;
	sf::FloatRect get_entity_local_bounds() override;
	void set_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override
	{
		this->setTexture(*std::get<sf::Texture*>(resource));

	}


	Entity(const sf::Texture& texture, const sf::IntRect& sprite_rectangle);
	//Entity(const Entity& another_entity);
	~Entity();
	//Entity& operator=(const Entity& another_entity);
	property_type& operator[](const std::string& name);
	property_type& operator[](const char*& name);

	void set_colliding(const bool& arg);
	const bool& is_colliding();

	sf::FloatRect& get_collision_bounds();
	void set_collision_padding(sf::Vector2f padding);

	sf::Vector2f& get_last_valid_position() { return last_valid_position; }


	void add_property(const std::string& name, const property_type& data);
	void set_intersection_slot(Core::dual_slot_type slot);
	void set_script(script ent_script);
};