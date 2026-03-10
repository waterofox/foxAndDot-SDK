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

#include "Tools/Scene.h"
#include "Tools/Executable.h"
#include "Tools/Signal.h"
#include "Tools/Slot.h"

#include "Tools/Ready slots/Handle_Collider_Slot.h"

//Any other questions? a3shirnin@gmail.com

//CORE
class  Core : public sf::RenderWindow
{
//TYPES & ENUMS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
public:	
	//FUNCTION TYPES
	using slot_type      = std::function<void(Core*, Scene_Component*)>; //a slot that accepts a pointer to the signal sender as an argument.
	using dual_slot_type = std::function<void(Core*, Scene_Component*,\
		                                             Scene_Component*)>; //a slot that accepts a pointer to the signal sender and another 
	                                                                     //pointer to a component as arguments.
private:
	//CONTAINERS
	using signals_container = std::pair<std::variant<slot_type, dual_slot_type>, std::pair<Scene_Component*, Scene_Component*>>;
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	sf::Time delta_time = sf::Time::Zero;
	std::unordered_map<std::string,sf::View> views;
	
	Scene* actual_scene   = nullptr;
	bool   changin_scene  = false;
	Scene* scene_buffer   = nullptr;

	//std::queue<signals_container> signals_queue;
	//std::map<int, std::variant<slot_type, dual_slot_type>> connections;

	sf::Clock game_cycle_clock;
	sf::Time emited_timer = sf::Time::Zero;

	int slot_handler_timelimit = 500;

	std::queue<Executable*> emited_queue;




public:
	Core();
	virtual ~Core() = default;

//INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	//STAIC FIELDS
	static inline Slot<Collider_Args_Package> handle_collider;
	static inline Resource_Manager resource_manager{}; //A single-instance resource manager. Required for managing fonts  and textures
	static inline Media_Manager    media_manager   {}; //A single-instance media    manager. Required for managing sounds and music
	static inline Core*            the_core;           //Static Core reference. Actually this is a "this" pointer. foxAndDot SDK using 
													   //a single ton pattern

	//GAME TOOLS
	void change_scene(Scene* new_Scene);               //change actual scene by other scene
	Scene* get_actual_scene();						   //get actual scene
	const sf::Time& get_delta_time();                  //get actual delta time (elapsed time since last frame)


	template<typename args_package>
	static void connect(Signal<args_package>* signal, Slot<args_package>* slot)
	{
		signal->next_connectable = slot;
		signal->next_connectable_type = 1;
	}
	template<typename args_package>
	static void connect(Signal<args_package>* signal, Signal<args_package>* signal_2)
	{
		signal->next_connectable = signal_2;
		signal->next_connectable_type = 0;
	}
	template<typename args_package>
	void emit(Signal<args_package>* signal)
	{
		signal->core_queue = &(this->emited_queue);
		(*signal)();
	}

	void set_slot_handler_timelimit(const int& new_timelimit);

	//void emit_signal(const int& signal_id, Scene_Component*&);						         //emit signal
	//void emit_signal(const int& signal_id, Scene_Component*&, Scene_Component*&);	         //emit signal (dual slot)
	//void connect(const int& signal_id, const std::variant<slot_type, dual_slot_type>& slot); //create connection between signal and slot

	void      add_view   (const std::string& view_name, const sf::View& view); //Add view.
	void      remove_view(const std::string& view_name);					   //Remove_view.
	sf::View* get_view   (const std::string& view_name);					   //Get View.

	//GAME SETTINGS
	void set_event_handler(Executable* handler);       //change the object that handles events

	void run(const unsigned int& window_width, \
		     const unsigned int& window_height,\
		     const std::string& window_title,\
		     const unsigned long& framerate_limit,\
		     const sf::State& state);				  //start your game

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:
	Executable*  event_handler = nullptr;
	void handle_slots();
	void process_intersections_and_collisions();

	void update();
	void render();
};
