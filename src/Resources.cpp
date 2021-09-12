#include "Resources.h"
#include "Macros.h"

#include <fstream>
#include <iostream>

Resources::Resources()
{
	setTextures();

	m_font.loadFromFile("C:/Windows/Fonts/COOPBL.ttf");

	setMusic();
	
	setSound();
}

void Resources::setTextures()
{
	std::ifstream textureNames;

	textureNames.open("TextureNames.txt");
	if (!textureNames.is_open())
	{
		std::cout << "Cannot open TextureNames.txt" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string newName;

	for (int texture = 0; !textureNames.eof(); texture++)
	{
		sf::Texture newTexture;
		std::getline(textureNames, newName);

		newTexture.loadFromFile(newName);
		m_textures.push_back(newTexture);
	}
	textureNames.close();
}

void Resources::setMusic()
{
	if (!m_music.openFromFile("GameMusic.wav"))
	{
		exit(EXIT_FAILURE);
	}
	m_music.setLoop(true);
	m_music.setVolume(10);
}

void Resources::setSound()
{
	std::ifstream soundNames;

	soundNames.open("SoundNames.txt");
	if (!soundNames.is_open())
	{
		std::cout << "Cannot open SoundNames.txt" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string newName;
	sf::SoundBuffer newSoundBuffer;

	for (int sound = 0; !soundNames.eof(); sound++)
	{
		std::getline(soundNames, newName);

		if (!newSoundBuffer.loadFromFile(newName))
		{
			exit(EXIT_FAILURE);
		}
		m_soundBuffers.push_back(newSoundBuffer);
	}
	soundNames.close();

	sf::Sound newSound;

	for (int sound = 0; sound < m_soundBuffers.size(); sound++)
	{
		newSound.setBuffer(m_soundBuffers[sound]);
		m_sounds.push_back(newSound);
	}
}

sf::Sprite Resources::getSprite(int object)
{
	return sf::Sprite(m_textures[object]);
}

sf::Text Resources::getText()
{
	sf::Text text;
	text.setFont(m_font);

	return text;
}

void Resources::playSound(int sound)
{
	m_sounds[sound].play();
}

void Resources::stopSound(int sound)
{
	m_sounds[sound].stop();
}

void Resources::playMusic()
{
	m_music.play();
}

void Resources::pauseMusic()
{
	m_music.pause();
}

Resources& Resources::getResources()
{
	static Resources resources;
	return resources;
}