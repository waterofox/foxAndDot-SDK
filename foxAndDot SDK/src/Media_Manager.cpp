#include "../include/foxAndDot-SDK/Media_Manager.h"

#define EMEDMAN std::string("MEDIA MANAGER ERROR: ")
#define ERROR(error_location,error_message) error_location + error_message

Media_Manager::Media_Manager()
{
}

Media_Manager::~Media_Manager()
{
}

void Media_Manager::add_music(const int index, const std::string& path)
{

	if (!std::filesystem::exists(path))
	{
		std::cerr << ERROR(EMEDMAN,"media file: " + path + " does not exist");
		return;
	}

	music_lib[index] = path;

}

void Media_Manager::add_sound(const int index, const std::string& path)
{

	if (!std::filesystem::exists(path))
	{
		std::cerr << ERROR(EMEDMAN, "media file: " + path + " does not exist");
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
		std::cerr << ERROR(EMEDMAN, "media file: " + path + " reading error");
		sound_lib.erase(index);
		return;
	}
}

void Media_Manager::play_music(const int index)
{
	if (!music_player.openFromFile(music_lib[index]))
	{
		std::cerr << ERROR(EMEDMAN, "media file: " + music_lib[index] + " reading error");
		return;
	}

	music_player.play();
	last_music_path = music_lib[index];

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
		std::cerr << ERROR(EMEDMAN, "sound does not exist");
		return;
	}
}

void Media_Manager::delete_music(const int index)
{
	if (last_music_path == music_lib[index] and
		music_player.getStatus() == sf::SoundSource::Status::Playing)
	{
		std::cerr << ERROR(EMEDMAN, "You can't delete media whet it's playing");
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
			std::cerr << ERROR(EMEDMAN, "You can't delete media whet it's playing");
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
		std::cerr << ERROR(EMEDMAN, "sound does not exist");
		assert(false);
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
		std::cerr << ERROR(EMEDMAN, "sound does not exist");
		assert(false);
	}
}

