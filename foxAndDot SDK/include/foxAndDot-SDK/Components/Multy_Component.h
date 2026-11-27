#pragma once

#include "Scene_Component.h"

class Multy_Component : public Scene_Component
{
	std::unordered_map<std::string, Scene_Component*> components;

	void update_resource(const Type_Res&) override;

protected:
	void update() override;

	void add(Scene_Component* comp);

public:
	Scene_Component* const get(const std::string& name);
	const Scene_Component* const get(const std::string& name) const;
};

