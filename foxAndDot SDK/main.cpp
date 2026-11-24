#include "include/foxAndDot-SDK/Core.h"
#include "include/foxAndDot-SDK/Tools/fAD_Event_Handler.h"

#define PROJECTNAME "$(ProjectName)"

class Event_Listner
{
	
	void on_key_pressed(const sf::Keyboard::Scancode& key)
	{
		std::cout << "key_pressed\n";
	}
	void on_key_released(const sf::Keyboard::Scancode& key)
	{
		std::cout << "key_released\n";
	}

	void other_events(const std::optional<sf::Event>& evnt)
	{
		if (evnt->is<sf::Event::MouseMoved>())
		{
			sf::Vector2i pos = evnt->getIf<sf::Event::MouseMoved>()->position;
			std::cout << "mouse\n";
			std::cout << pos.x << ' ' << pos.y;
		}
	}

public:
	Event_Listner()
	{
		on_key_released_slot.reassign(&Event_Listner::on_key_released, this);
		on_key_pressed_slot.reassign(&Event_Listner::on_key_pressed, this);
		other_events_slot.reassign(&Event_Listner::other_events, this);

		connect(&fAD_Event_Handler::key_pressed, &this->on_key_pressed_slot);
		connect(&fAD_Event_Handler::key_released, &this->on_key_released_slot);
		connect(&fAD_Event_Handler::render_window_event, &this->other_events_slot);
	}

	Slot<std::optional<sf::Event>, Event_Listner> other_events_slot;
	Slot<sf::Keyboard::Scancode, Event_Listner> on_key_pressed_slot;
	Slot<sf::Keyboard::Scancode, Event_Listner> on_key_released_slot;

};

int main()
{
	Core the_core;
	Scene scene;
	fAD_Event_Handler evnt_handler;

	

	the_core.change_scene(&scene);
	the_core.set_event_handler(&evnt_handler);
	the_core.get_window().setVerticalSyncEnabled(true);
	

	the_core.run(600, 600, PROJECTNAME, 120, sf::State::Windowed);
}