#pragma once

#include "Executable.h"
#include "connect.h"

#include <SFML/Graphics/RenderWindow.hpp>

class fAD_Event_Handler : public Executable
{
	friend class Core;

	sf::RenderWindow* game_window = nullptr; // will be initialized when the first iteration of the game loop starts
	void operator()() override;

public:
	static inline Signal<std::optional<sf::Event>> render_window_event;
	
	static inline Signal<sf::Keyboard::Scancode> key_pressed;
	static inline Signal<sf::Keyboard::Scancode> key_released;

	fAD_Event_Handler() = default;
	~fAD_Event_Handler() = default;
};

