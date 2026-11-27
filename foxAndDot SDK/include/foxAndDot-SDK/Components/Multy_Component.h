#pragma once

#include "Scene_Component.h"

class Multy_Component : public Scene_Component
{
	std::unordered_map<std::string, std::pair<Scene_Component*,int>> components;
	std::vector<Scene_Component*> update_order;

	void update_resource(const Type_Res&) override;

protected:
	void update() override;

	void add(Scene_Component* comp,const int& update_order = -1);
	void set_update_order(const std::string& comp_name, const int& update_order);

public:
	Scene_Component* const get(const std::string& name);
	const Scene_Component* const get(const std::string& name) const;
};

