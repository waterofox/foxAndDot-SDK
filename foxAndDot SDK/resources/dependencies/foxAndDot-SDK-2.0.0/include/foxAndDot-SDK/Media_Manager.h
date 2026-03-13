#pragma once

#include "SFML/Config.hpp"
#include "SFML/Audio.hpp"

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <filesystem>


class  Media_Manager 
{
	struct sound_container
	{
		sf::SoundBuffer buffer;
		sf::Sound sound = sf::Sound(buffer);
	};

public:

	Media_Manager();
	~Media_Manager();

//INTERFACE OF THE CLASS
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	void add_music(const int index, const std::string& path); //Add the path to the music in the library
	void add_sound(const int index, const std::string& path); //Add sound to the library

	void play_music(const int index); //play music
	void play_sound(const int index); //play sound

	void delete_music(const int index); //delete music from library
	void delete_sound(const int index); //delete sound from library
	void delete_all_music(); //clear music library
	void delete_all_sound(); //clear sound library

	sf::Music& get_music_player();			//get music player (You can control it)

	sf::SoundBuffer& get_sound_buffer(const int& index); //get buffer of sound from library (You can control it)
	sf::Sound& get_sound(const int& index);              //get sound from library (You can control it)

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:

	std::map<int, std::string> music_lib;
	std::map<int, sound_container> sound_lib;

	sf::Music music_player;
	std::string last_music_path;

};