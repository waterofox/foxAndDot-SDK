#pragma once
#include "Executable.h"
#include <unordered_set>

enum class Connection_Types
{
	Undefined = -1,
	Signal = 0,
	Slot = 1,
};

template <typename s_args_package>
class Signal;

template <typename args_package>
class Connectable : public Executable
{
	friend class Signal<args_package>;

protected:

	//-------------------------------------------------------------------------------------------------
		
		args_package args; // Parameters passed
		std::unordered_set<Connectable<args_package>*> connected_to;

	//-------------------------------------------------------------------------------------------------

public:
	virtual void back_disconnect(Connectable<args_package>* connected) = 0;
	virtual void disconnect(Connectable<args_package>* connected) = 0;


	Connectable() = default;
	virtual ~Connectable()
	{
		if (connected_to.size() !=0)
		{
			for (auto& connectee : this->connected_to)
			{
				connectee->back_disconnect(this);
				if (connected_to.size() == 0)
				{
					break;
				}
			}
		}

	}

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

