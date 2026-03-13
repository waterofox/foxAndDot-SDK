#pragma once
#include "../Slot.h"

class Collider;
class Scene_Component;

struct Collider_Args_Package
{
	Collider* collider = nullptr;
	Scene_Component* other_comp = nullptr;
};

class Handle_Collider_Slot : public Slot<Collider_Args_Package>
{
	void do_something() override;
};

