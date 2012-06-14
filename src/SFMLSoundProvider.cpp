#include "stdafx.h"
#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"

SFMLSoundProvider::SFMLSoundProvider() :
	_currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename)
{
	int availChannel = -1;

	for(int i = 0;i < MAX_SOUND_CHANNELS;i++)
	{
		if(_currentSounds[i].GetStatus() != sf::Sound::Playing)
		{
			availChannel = i;
			break;
		}
	}

	if (availChannel != -1)
	{
		try
		{
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].Play();
		}
		catch(SoundNotFoundException& snfe)
		{
			//I AM ERROR
			//I DO NOTHING
			//
		}
	}
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	sf::Music * currentSong;
	try
	{
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch(SoundNotFoundException & snfe)
	{
		//OHH CRAP NO MUSIC
		return;
	}

	if(_currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if(priorSong->GetStatus() != sf::Sound::Stopped)
			{
				priorSong->Stop();
			}
		}
		catch(SoundNotFoundException&)
		{
			//AMAZING, NOTHING HAPPENS
		}
	}
	_currentSongName = filename;
	currentSong->SetLoop(looping);
	currentSong->Play();
}

void SFMLSoundProvider::StopAllSounds()
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].Stop();
	}
	if(_currentSongName != "")
	{
		sf::Music * currentSong = _soundFileCache.GetSong(_currentSongName);
		if(currentSong->GetStatus() == sf::Sound::Playing)
		{
			currentSong->Stop();
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying()
{
	for(int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if(_currentSounds[i].GetStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

bool SFMLSoundProvider::IsSongPlaying()
{
	if(_currentSongName != "")
	{
		return _soundFileCache.GetSong(_currentSongName)->GetStatus() == sf::Music::Playing;
	}
	return false;
}
