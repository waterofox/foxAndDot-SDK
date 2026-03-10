#include "../include/foxAndDot-SDK/Tools/Ready slots/Handle_Collider_Slot.h"
#include "../include/foxAndDot-SDK/Components/Scene_Component.h"
#include "../include/foxAndDot-SDK/Components/Collider.h"

void Handle_Collider_Slot::do_something()
{
	args.other_comp->on_intersection(args.collider);
}