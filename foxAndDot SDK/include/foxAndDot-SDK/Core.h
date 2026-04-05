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
#include "Tools/Collider.h"
#include "Tools/Signal.h"
#include "Tools/Slot.h"

//Any other questions? a3shirnin@gmail.com

class  Core : public sf::RenderWindow
{
	class Handle_Collider_Slot : public Slot<Collider_Args_Package>
	{
		void do_something() override;
	};
	//-------------------------------------------------------------------------------------------------------
		sf::Time delta_time = sf::Time::Zero;
		sf::Clock game_cycle_clock;

		std::unordered_map<std::string,sf::View> views;
	
		Scene* actual_scene   = nullptr;
		bool   changing_scene  = false;
		Scene* scene_buffer   = nullptr;

		std::queue<Executable*> emited_queue;
	//-------------------------------------------------------------------------------------------------------
		Executable* event_handler = nullptr;
		void handle_slots();
		void process_intersections_and_collisions();

		void update();
		void render();
	//-------------------------------------------------------------------------------------------------------
public:

	struct Changed_Scene_Package
	{
		Scene* new_scene = nullptr;
		Scene* old_scene = nullptr;
	};


	Core();
	virtual ~Core() = default;

	//INTERFACE
	//=================================================================================================================================
	
		static inline Handle_Collider_Slot handle_collider; // Сollision handling slot

		static inline Signal<Changed_Scene_Package> scene_had_changed;		// Emited when new scene had loaded


		static inline Resource_Manager resource_manager;	// Resource manager for managing fonts and textures

		static inline Media_Manager    media_manager;		// Media manager for managing sounds and a music center

		static inline Core*            the_core;            // A static Core pointer to itself. Provides access to core settings from anywhere

	//---------------------------------------------------------------------------------------------------------------------------------

		void set_event_handler(Executable* handler);       // Change the object that handles events

		void run(const unsigned int& window_width, \
			const unsigned int& window_height, \
			const std::string& window_title, \
			const unsigned long& framerate_limit, \
			const sf::State& state);					   // Start your game


	//---------------------------------------------------------------------------------------------------------------------------------

		void change_scene(Scene* new_Scene); // Change actual scene by other scene
		
		Scene* get_actual_scene();			 // Get actual scene
		
		const sf::Time& get_delta_time();    // Get actual delta time (elapsed time since last frame)

	//---------------------------------------------------------------------------------------------------------------------------------
		
		void      add_view(const std::string& view_name, const sf::View& view); // Add view
	
		void      remove_view(const std::string& view_name);					// Remove view
		
		sf::View* get_view(const std::string& view_name);					    // Get View

	//---------------------------------------------------------------------------------------------------------------------------------

		template<typename args_package>
		static void connect(Signal<args_package>* signal, Slot<args_package>* slot)			// Connect signal to slot
		{
			signal->next_c.emplace(slot,Connection_Types::Slot);
		}
		template<typename args_package>
		static void connect(Signal<args_package>* signal, Signal<args_package>* signal_2)	// Connect signal to signal
		{
			signal->next_c.emplace(signal_2, Connection_Types::Signal);
		}
		template<typename args_package>				
		void emit(Signal<args_package>* signal)												// Emit connected signal
		{
			signal->core_queue = &(this->emited_queue);
			(*signal)();
		}

	//=================================================================================================================================

};
