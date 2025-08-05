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
//C
#include <cassert>

//ERRORS
#define ECORE std::string("CORE ERROR: ")
#define EENTITY std::string("ENTITY ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

//PROPERTIES
#define Int(int_property) std::get<int>(int_property)
#define Float(float_property) std::get<float>(float_property)
#define Bool(bool_property) std::get<bool>(bool_property)
#define String(string_property) std::get<std::string>(string_property)

class Core;
class Drawable_Entity;


class Core : public sf::RenderWindow 
{

//some types & enums
public:

	enum camera_settings
	{
		dynamic_camera = 0,
		static_camera = 1
	};

	using process_events_function = void(*)(Core*);
	using slot_type = void(*)(Core*, Drawable_Entity*);
	using dual_slot_type = void(*)(Core*, Drawable_Entity*, Drawable_Entity*);
	using signals_container = std::pair<std::variant<slot_type, dual_slot_type>, std::pair<Drawable_Entity*, Drawable_Entity*>>;

	using lay_type = std::map<std::string, Drawable_Entity*>;
	using scene_type = std::vector<lay_type>;
//core fields
private:
	//window
	sf::Time delta_time = sf::Time::Zero;
	sf::View camera;
	camera_settings camera_mod = camera_settings::static_camera;
	std::string camera_target = "";

	//signals & slots
	std::queue<signals_container> signals_queue;
	std::map<int, std::variant<slot_type, dual_slot_type>> connections;
public:
	//game
	std::string scene_name;
	scene_type scene;
	
//core methods
	Core();
	~Core();

	//window
	const sf::Time& get_delta_time();
	sf::View& get_camera();
	void set_camera_mod(const camera_settings& mod);
	void set_camera_target(const std::string& name_of_target);

	//game
	void run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title, const sf::State& state);
	void set_process_events_function(const process_events_function& function);

	Drawable_Entity* get_entity(const std::string& name);
	Drawable_Entity* get_entity(const std::string& name, const int& lay);
	
	//signals & slots
	void emit_signal(const int& signal_id, Drawable_Entity*&);
	void emit_signal(const int& signal_id, Drawable_Entity*&,Drawable_Entity*&);
	void connect(const int& signal_id, const std::variant<slot_type, dual_slot_type>& slot);



//process methods
private:
	process_events_function process_events = nullptr;
	void update();
	void update_camera();
	void process_signals();
	void process_intersections_and_collisions();

	void render();
	
};

class Drawable_Entity
{
	friend class Core;

	bool visible = true;
	bool updateble = true;

protected:
	Core::dual_slot_type on_intersection = nullptr;
	sf::Vector2f last_valid_position;

public:

	sf::Vector2f& get_last_valid_position() { return last_valid_position; }

	void set_visble(const bool& arg) { visible = arg; }
	const bool& is_visible() { return visible; };

	void set_updateble(const bool& arg) { updateble = arg; }
	const bool& is_updateble() { return updateble; };

	void set_on_intersection(Core::dual_slot_type slot) { on_intersection = slot; }

	virtual sf::Drawable* asDrawable() { return nullptr; }
	virtual void update(Core* the_core) = 0;

	virtual sf::FloatRect get_entity_global_bounds() = 0;
	virtual sf::FloatRect get_entity_local_bounds() = 0;

};

class Entity : public Drawable_Entity, public sf::Sprite
{

	friend class Core;

	static void entity_on_intersection(Core* the_core, Drawable_Entity* elementA, Drawable_Entity* elementB)
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

	std::map<std::string, property_type> properties;
	bool colliding;
	sf::FloatRect collision_bounds = sf::FloatRect(sf::Vector2f(0,0),sf::Vector2f(0,0));
	sf::Vector2f collision_padding = sf::Vector2f(0, 0);

public:

	sf::Drawable* asDrawable() override;
	void update(Core* the_core) override; 
	virtual sf::FloatRect get_entity_global_bounds() override;
	virtual sf::FloatRect get_entity_local_bounds() override;

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


	void add_property(const std::string& name, const property_type& data);
	void set_intersection_slot(Core::dual_slot_type slot);
	void set_script(script ent_script);
};