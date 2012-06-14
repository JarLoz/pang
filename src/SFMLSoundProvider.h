#pragma once

#include "stdafx.h"
#include "IAudioProvider.h"

class SFMLSoundProvider : public IAudioProvider
{
	public:
		SFMLSoundProvider();

		void PlaySound(std::string filename);
		void PlaySong(std::string filename, bool looping = false);
		void StopAllSounds();

		bool IsSoundPlaying();
		bool IsSongPlaying();

	private:
		sf::SoundBuffer _soundBuffer;
		sf::Sound _sound;
		sf::Music _music;
};

