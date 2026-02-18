#include "../include/foxAndDot-SDK/Tools/Script.h"

void Script::set_entity(Entity* entity_ptr)
{
	this->this_entity = entity_ptr;
}

Script::Script(Entity* entity_ptr)
{
	set_entity(entity_ptr);
}

Script::Script(const Script& other_script)
{
	//this class must not make the of it's fields!
}

Script& Script::operator=(const Script& other_script)
{
	//this class must not make the of it's fields!
	return *this;
}
