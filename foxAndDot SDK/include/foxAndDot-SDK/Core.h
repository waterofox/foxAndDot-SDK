#pragma once

//sfml 3.0.0 includes 
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

//std inlcludes
#include <set>
#include <vector>
#include <variant>
#include <queue>
#include <functional>

//sdk includes
#include "Media_Manager.h"
#include "Resource_Manager.h"

//PROPERTIES
#define Int(int_property) std::get<int>(int_property)
#define Float(float_property) std::get<float>(float_property)
#define Bool(bool_property) std::get<bool>(bool_property)
#define String(string_property) std::get<std::string>(string_property)

//Any other questions? a3shirnin@gmail.com

class Scene_Component;

//CORE
class  Core : public sf::RenderWindow
{
//TYPES & ENUMS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	//todo create uniq classes
public:	
	enum camera_settings
	{
		dynamic_camera = 0, //The camera will follow the selected target
		static_camera = 1   //The camera will be fixed
	};
	
	//FUNCTION TYPES
	using process_events_function = void(*)(Core*); //a type for a function that handles events
	
	using slot_type = std::function<void(Core*, Scene_Component*)>;						   //a slot that accepts a pointer to the signal sender as an argument
	using dual_slot_type = std::function<void(Core*, Scene_Component*, Scene_Component*)>; //a slot that accepts a pointer to the signal sender and another pointer to a component as arguments
	
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

	void run(const unsigned int& window_width, const unsigned int& window_height, const std::string& window_title,\
		const unsigned long& framerate_limit,const sf::State& state); //start your game

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
