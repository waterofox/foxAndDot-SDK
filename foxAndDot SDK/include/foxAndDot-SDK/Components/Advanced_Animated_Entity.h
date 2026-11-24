#pragma once
#include "Animated_Entity.h"

template <typename properties_package>
class Advanced_Animated_Entity : public Animated_Entity
{
public:
	properties_package properties;
};