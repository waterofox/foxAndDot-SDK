#pragma once

//sfml 3.0.0 includes 
#include "SFML/Config.hpp"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"


//std inlcludes
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <variant>
#include <queue>

//sdk includes
#include "Media_Manager.h"

//PROPERTIES
#define Int(int_property) std::get<int>(int_property)
#define Float(float_property) std::get<float>(float_property)
#define Bool(bool_property) std::get<bool>(bool_property)
#define String(string_property) std::get<std::string>(string_property)

//Any other questions? a3shirnin@gmail.com

class Scene_Component;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//RESOURCE MANAGER
class  Resource_Manager
{

	friend class Core;

//TYPES OF RESOURCES
public:
	enum class resource_type
	{
		texture = 0,
		font = 1,
		no_resource = 2
	};

//FIELDS
private:
	std::map<int, sf::Texture> texture_library;
	std::map<int, sf::Font>	      font_library;

//METHODS
public:

	Resource_Manager() = default;
	~Resource_Manager() = default;

	//INTERFACE OF THE CLASS
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	void add_texture(const std::string& texture_url, const int& id);//add texture in library
	void add_font(const std::string& font_url, const int& id);		//add font in library

	void clear_libraries(); //drop all fonts and textures

	sf::Texture& texture(const int& id); //get texture from library (You can control it)
	sf::Font& font(const int& id);		 //get font from library (You can control it)
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


private:
	void update_resource(Scene_Component*& component); 
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//CORE
class  Core : public sf::RenderWindow
{
//TYPES & ENUMS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:	
	enum camera_settings
	{
		dynamic_camera = 0, //The camera will follow the selected target
		static_camera = 1   //The camera will be fixed
	};
	
	//FUNCTION TYPES
	using process_events_function = void(*)(Core*); //a type for a function that handles events
	
	using slot_type = void(*)(Core*, Scene_Component*);						   //a slot that accepts a pointer to the signal sender as an argument
	using dual_slot_type = void(*)(Core*, Scene_Component*, Scene_Component*); //a slot that accepts a pointer to the signal sender and another pointer to a component as arguments
	
	//CONTAINERS
private:
	using signals_container = std::pair<std::variant<slot_type, dual_slot_type>, std::pair<Scene_Component*, Scene_Component*>>;

public:
	using lay_type = std::map<std::string, Scene_Component*>; //A simple std::map with components
	using scene_type = std::vector<lay_type>;				  //Simple std::vector with std::map

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:
	sf::Time delta_time = sf::Time::Zero;

	sf::View	camera;
	camera_settings camera_mod = camera_settings::static_camera;
	std::string camera_target = "";

	std::queue<signals_container> signals_queue;
	std::map<int, std::variant<slot_type, dual_slot_type>> connections;



public:
	Core() = default;
	virtual ~Core() = default;

public:
//INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	static inline Resource_Manager resource_manager{}; //A single-instance resource manager. Required for managing fonts and textures
	static inline Media_Manager media_manager{};	   //A single-instance media manager. Required for managing sounds and music

	scene_type scene; //actual scene

	const sf::Time& get_delta_time(); //get actual delta time

	void set_process_events_function(const process_events_function& function); //change the function that handles events

	sf::View& get_camera();									   //get camera (You can control it)
	void set_camera_mod(const camera_settings& mod);		   //Make the camera static or dynamic
	void set_camera_target(const std::string& name_of_target); //Specify the target for the dynamic camera

	void run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title, const sf::State& state); //start your game

	Scene_Component* get_component(const std::string& name);			     //return pointer on component
	Scene_Component* get_component(const std::string& name, const int& lay); //return pointer on component

	void emit_signal(const int& signal_id, Scene_Component*&);						         //emit signal
	void emit_signal(const int& signal_id, Scene_Component*&, Scene_Component*&);	         //emit signal (dual slot)
	void connect(const int& signal_id, const std::variant<slot_type, dual_slot_type>& slot); //create connection between signal and slot

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	
private:
	process_events_function process_events = nullptr;
	void process_signals();
	void process_intersections_and_collisions();

	void update();
	void update_camera();

	void render();
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//SCENE COMPONENT
class Scene_Component
{

	friend class Core;
	friend class Resource_Manager;

protected:
	std::string component_name;
	bool visible = true;
	bool updateble = true;

	int resource;
	Resource_Manager::resource_type type_of_resource;

	sf::Vector2f last_valid_position;
	bool colliding;
	sf::FloatRect collision_bounds = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
	sf::Vector2f collision_padding = sf::Vector2f(0, 0);

//VIRTUAL METHODS & METHODS
protected:
	virtual void on_intersection(Core* the_core, Scene_Component* component) = 0; //How the component reacts to the intersection
	virtual sf::Drawable* as_drawable() = 0; //What you need to draw
	virtual void update(Core* the_core) = 0; //How does the component behave during Core operation
	virtual void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) = 0; //How component updates it's resource

//INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:
	virtual sf::FloatRect get_component_render_bounds() = 0; //Returns the bounds that are used to determine whether the component intersects with the camera
	virtual sf::FloatRect get_component_bounds() = 0; //Returns the bounds that are used to determine whether a component intersects with other components



public:
	std::string& name() { return component_name; }	//get name (You can control it)							

	void set_visble(const bool& arg) { visible = arg; }	//when set_visible(true) component will be drawn by Core					
	const bool& is_visible() { return visible; };		//return visible						

	void set_updateble(const bool& arg) { updateble = arg; } //when set_updateble(true) component will be updated by Core							
	const bool& is_updateble() { return updateble; }		 //return updateble

	void set_colliding(const bool& arg) { colliding = arg; } //when set_colliding(true) component will collide with other components
	const bool& is_colliding() { return colliding; };		 //retunr colliding

	sf::FloatRect& get_collision_bounds() { return collision_bounds; }; //returns the bounds of the component's collision (you can control it)
	void set_collision_padding(const sf::Vector2f& padding) { collision_padding = padding; } //the default values are 0 and 0, which means that the coordinates of the collision rectangle match the coordinates of the component

	const sf::Vector2f& get_last_valid_position() { return last_valid_position; } //will return the last position of the component where it did not collide with another


	int& get_resource() { return resource; } //returns the resource ID that is used by the component (You can control it)
	Resource_Manager::resource_type& get_type_of_resource() { return type_of_resource; } //returns the resource type used by the component (You can control it)

	virtual ~Scene_Component() = default;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//ENTITY
class  Entity : public Scene_Component, public sf::Sprite
{
	static inline sf::Texture empty_entity_s_texture; // I don't like that sf::Sprite needs an sf::Texture. So... this is a field to supply a default constructor argument for sf::Sprite.

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

public:
	using script = void(*)(Core*,Entity*);

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


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//COLLISION AREA

class  Collision_Area : public Scene_Component, public sf::RectangleShape
{

//OVERRIDED METHODS & METHODS
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Collision_Area(const sf::FloatRect& rect);
	~Collision_Area() = default;

// INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds()		override;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//INTERSECTION AREA

class  Intersection_Area : public Scene_Component, public sf::RectangleShape
{
	std::set<Scene_Component*> components_inside_area;
	std::vector<Scene_Component*> erase_buffer;

	Core::slot_type on_enterence = nullptr;
	Core::slot_type on_exit = nullptr;

//OVERRIDED METHODS & METHODS
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;


public:
	Intersection_Area(const sf::FloatRect& rect);
	~Intersection_Area() = default;

// INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds()		override;

	void set_slot_on_enterence(const Core::slot_type& slot); //What happens when a component steps into an area
	void set_slot_on_exit(const Core::slot_type& slot);      //What happens when the component leaves the area

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};