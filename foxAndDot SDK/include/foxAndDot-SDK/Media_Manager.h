#pragma once

//sfml includes
#include "SFML/Audio.hpp"

//std includes
#include <string>
#include <map>
#include <iostream>


class  Media_Manager 
{
	struct sound_container
	{
		sf::SoundBuffer buffer;
		sf::Sound sound = sf::Sound(buffer);
	};
	//------------------------------------------------------------------------------------------------------------------
		static inline sound_container e_c;

		std::unordered_map<int, std::string> music_lib;
		std::unordered_map<int, sound_container> sound_lib;

		sf::Music music_player;		 //	Music player for music files
		std::string last_music_path;
	//------------------------------------------------------------------------------------------------------------------

public:

	Media_Manager()  = default;
	~Media_Manager() = default;

	//INTERFACE
	//==================================================================================================================

		void add_music(const int index, const std::string& path); //Add the path to the music in the library
		void add_sound(const int index, const std::string& path); //Add sound to the library

	//------------------------------------------------------------------------------------------------------------------
	
		void play_music(const int index); //play music
		void play_sound(const int index); //play sound

	//------------------------------------------------------------------------------------------------------------------
	
		void delete_music(const int index); //delete music from library

		void delete_sound(const int index); //delete sound from library

		void delete_all_music();            //clear music library

		void delete_all_sound();            //clear sound library

	//------------------------------------------------------------------------------------------------------------------

		sf::Music& get_music_player();			//get music player 

	//------------------------------------------------------------------------------------------------------------------

		sf::SoundBuffer& get_sound_buffer(const int& index); //get buffer of sound from library 
		
		sf::Sound& get_sound(const int& index);              //get sound from library 

	//==================================================================================================================
};