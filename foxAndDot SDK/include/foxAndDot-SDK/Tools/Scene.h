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

	std::unordered_map<std::string, comp_info> scene_data;
	std::unordered_map<int,std::unordered_map<std::string, Scene_Component*>> render_order;

	void render(const sf::View& view);

public:	
	void add(Scene_Component*, const int& lay);
	void remove(const std::string& component_name);
	void move_on_lay(const std::string& component_name, const int& lay);
	bool is_on_scene(const std::string& component_name);

	Scene_Component* operator[](const std::string& component_name);
	Scene_Component* operator[](const char* component_name);

	Scene(const int& lays_count);
	~Scene() = default;
};

