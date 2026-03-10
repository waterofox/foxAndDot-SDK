#include "../include/foxAndDot-SDK/Tools/Ready slots/Handle_Collision_Slot.h"
#include "../include/foxAndDot-SDK/Components/Entity.h"

void Handle_Collision_Slot::do_something()
{
	this->this_entity->setPosition(this->args);
}
