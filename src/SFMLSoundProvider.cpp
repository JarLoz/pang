#include "stdafx.h"
#include "SFMLSoundProvider.h"

SFMLSoundProvider::SFMLSoundProvider()
{
	_sound.SetVolume(100.0f);
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
	if(_soundBuffer.GetDuration() == 0)
	{
		_soundBuffer.LoadFromFile(filename);
	}
	if(_sound.GetStatus() == sf::Sound::Playing)
	{
		_sound.Stop();
	}
	_sound.SetBuffer(_soundBuffer);
	_sound.Play();
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	_music.OpenFromFile(filename);
	_music.SetLoop(looping);
	_music.Play();
}

void SFMLSoundProvider::StopAllSounds()
{
	if(_sound.GetStatus() == sf::Sound::Playing)
		_sound.Stop();
	if(_music.GetStatus() == sf::Sound::Playing)
		_music.Stop();
}

bool SFMLSoundProvider::IsSoundPlaying()
{
	return _sound.GetStatus() == sf::Sound::Playing;
}

bool SFMLSoundProvider::IsSongPlaying()
{
	return _music.GetStatus() == sf::Sound::Playing;
}
