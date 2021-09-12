#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>

class Resources
{
public:
	//d-tor:
	~Resources() = default;

	//other function:
	static Resources& getResources();
	sf::Sprite getSprite(int);
	sf::Text getText();
	void playSound(int);
	void playMusic();
	void pauseMusic();
	void stopSound(int sound);

private:
	//c-tor:
	Resources();

	//members:
	std::vector<sf::Texture > m_textures;
	sf::Font m_font;
	sf::Music m_music;
	std::vector<sf::SoundBuffer> m_soundBuffers;
	std::vector<sf::Sound> m_sounds;

	//private function:
	void setTextures();
	void setSound();
	void setMusic();
};