#pragma once

#include "ISystem.h"
#include "SFML\Audio.hpp"
#include "Events.h"
#include <map>
#include <vector>
#include <string>

class SoundSystem : public ISystem
{
public:
	SoundSystem();
	~SoundSystem()
	{
		eventManager.unregisterListener(this);
	}
	void update() override
	{}
private:
	std::map<std::string, sf::SoundBuffer> m_soundBuffer;
	sf::Music m_music;
	std::vector<sf::Sound> m_channel;
	int m_channelIndex{ 0 };
	const int m_channelMax = 4;
	void onSoundEvent(const Events::SoundEvent *evnt);
};