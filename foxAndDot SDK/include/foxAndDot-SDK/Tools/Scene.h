#pragma once


//std includes
#include <unordered_map>
#include <vector>
#include <string>

//sdk includes
#include "../Components/Scene_Component.h"

class Scene
{
	friend class Core;

	struct comp_info
	{
		Scene_Component* component = nullptr;
		int actual_comp_lay = 0;
	};

	//---------------------------------------------------------------------------------------------------------------------------------------------
		
		std::unordered_map<std::string, comp_info> scene_data;
		
		std::unordered_map<int,std::unordered_map<std::string, Scene_Component*>> render_order;

	//---------------------------------------------------------------------------------------------------------------------------------------------

		void render(const sf::View& view);

	//---------------------------------------------------------------------------------------------------------------------------------------------

public:
	
	Scene() = default;
	Scene(const int& lays_count);
	virtual ~Scene() = default;

	//INTERFACE
	//=============================================================================================================================================
	
		void add(Scene_Component*, const int& lay);							 // Add component to the sсene
		
		void remove(const std::string& component_name);						 // Remove component from the scene
		
		void move_on_lay(const std::string& component_name, const int& lay); // Move component to another layer
		
		bool is_on_scene(const std::string& component_name);				 // Component on the stage?

		void add_new_lay(const int& lay_count = 1);							 // add lays on scene

	//---------------------------------------------------------------------------------------------------------------------------------------------

		Scene_Component* operator[](const std::string& component_name); // Get component pointer
		
		Scene_Component* operator[](const char* component_name);		// Get component pointer

	//=============================================================================================================================================

};

