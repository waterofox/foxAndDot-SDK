#include "../include/foxAndDot-SDK/Media_Manager.h"

void Media_Manager::add_music(const int index, const std::string& path)
{

	if (!std::filesystem::exists(path))
	{
		printf("MEDIA MANAGER ERROR: Media file <%d> does not exist in directory:", index);
		std::cout << path << std::endl;
		return;
	}

	music_lib[index] = path;

}

void Media_Manager::add_sound(const int index, const std::string& path)
{

	if (!std::filesystem::exists(path))
	{
		printf("MEDIA MANAGER ERROR: Media file <%d> does not exist in directory:", index);
		std::cout << path << std::endl;
		return;
	}
	sound_container cont;
	sound_lib[index] = cont;

	sound_container& cont_in_memory = sound_lib[index];
	
	if (cont_in_memory.buffer.loadFromFile(path))
	{
		cont_in_memory.sound.setBuffer(cont_in_memory.buffer);
	}
	else
	{
		printf("MEDIA MANAGER ERROR: Media file <%d> does not exist in directory:", index);
		std::cout << path << std::endl;
		return;
	}
}

void Media_Manager::play_music(const int index)
{
	if (!music_player.openFromFile(music_lib[index]))
	{
		printf("MEDIA MANAGER ERROR: Music file <%d>  reading error\n", index);
		return;
	}

	music_player.play();
	last_music_path = music_lib[index];

}

void Media_Manager::continue_music()
{
	if (music_player.getStatus() == sf::SoundSource::Status::Paused)
	{
		music_player.play();
	}
	else
	{
		printf("MEDIA MANAGER WARNING: No music is paused\n");
	}
}

void Media_Manager::pause_music()
{
	music_player.pause();
}

void Media_Manager::play_sound(const int index)
{
	auto iter_sound = sound_lib.find(index);
	if (iter_sound != sound_lib.end())
	{
		(*iter_sound).second.sound.play();
	}
	else
	{
		printf("MEDIA MANAGER ERROR: Sound <%d>  doese not exist in library\n", index);
		return;
	}
}

void Media_Manager::delete_music(const int index)
{
	if (last_music_path == music_lib[index] and
		music_player.getStatus() == sf::SoundSource::Status::Playing)
	{
		printf("MEDIA MANAGER ERROR: You cannot delete a music file <%d> while it is playing\n", index);
		return;
	}

	music_lib.erase(index);
}

void Media_Manager::delete_sound(const int index)
{
	auto iter_sound = sound_lib.find(index);
	if (iter_sound != sound_lib.end())
	{
		if ((*iter_sound).second.sound.getStatus() == sf::SoundSource::Status::Playing)
		{
			printf("MEDIA MANAGER ERROR: You cannot delete a sound <%d> while it is playing\n", index);
			return;
		}
		sound_lib.erase(index);
	}
}



void Media_Manager::delete_all_music()
{
	music_player.stop();
	music_lib.clear();
}

void Media_Manager::delete_all_sound()
{
	for (auto& elem : sound_lib)
		elem.second.sound.stop();

	sound_lib.clear();

}

sf::Music& Media_Manager::get_music_player()
{
	return music_player;
}

sf::SoundBuffer& Media_Manager::get_sound_buffer(const int& index)
{
	auto iter_sound = sound_lib.find(index);
	if (iter_sound != sound_lib.end())
	{
		return (*iter_sound).second.buffer;
	}
	else
	{
		printf("MEDIA MANAGER ERROR: Sound <%d>  doese not exist in library\n", index);
		return e_c.buffer;
	}
}

sf::Sound& Media_Manager::get_sound(const int& index)
{
	auto iter_sound = sound_lib.find(index);
	if (iter_sound != sound_lib.end())
	{
		return (*iter_sound).second.sound;
	}
	else
	{
		printf("MEDIA MANAGER ERROR: Sound <%d>  doese not exist in library\n", index);
		return e_c.sound;
	}
}

