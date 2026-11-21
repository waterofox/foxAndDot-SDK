#pragma once
#include <queue>
#include <unordered_map>

#include "Connectable.h"

template<typename args_package>

class Connectee
{
	friend class Core;


	std::queue<Executable*>* core_queue = nullptr;

	std::unordered_map<Connectable<args_package>*, Connection_Types> next_c;
	
public:
	Connectee() = default;
	virtual ~Connectee()
	{
		for (auto& connected: next_c)
		{
			connected.connected_to.erase(this);
		}
		disconnect_all();
	}

	void disconnect(Connectable<args_package>* connected)                            
	{
		if (this->next_c.find(connected) != this->next_c.end())
		{
			connected.connected_to.erase(this);
			this->next_c.erase(connected);
		}
		else
		{
			printf("CONNECTY WARNING: Attempting to disconnect an unconnected slot or signal\n");
			return;
		}
	}

	void disconnect_all() 
	{ 
		this->next_c.clear();
	}
};

