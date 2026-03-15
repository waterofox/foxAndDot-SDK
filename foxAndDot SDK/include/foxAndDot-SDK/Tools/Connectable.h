#pragma once
#include "Executable.h"

template <typename args_package>
class Connectable : public Executable
{

protected:

	//-------------------------------------------------------------------------------------------------
		
		args_package args; // Parameters passed

	//-------------------------------------------------------------------------------------------------

public:

	Connectable() = default;
	virtual ~Connectable() = default;
	
	//INTERFACE
	//=================================================================================================
		
		virtual void push_args(const args_package& package) // Send parameters
		{
			this->args = package;
		}

	//-------------------------------------------------------------------------------------------------

		virtual void operator()() override 
		{
			this->args = args_package();
		}

	//=================================================================================================
};

