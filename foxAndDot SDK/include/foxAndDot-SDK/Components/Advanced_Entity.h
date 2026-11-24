#pragma once
#include "Entity.h"

template<typename properties_package>
class Advanced_Entity : public Entity
{
	//Advanced Entity is Entity with custom args package (var/class/struct)
public:
	properties_package properties;
};

 