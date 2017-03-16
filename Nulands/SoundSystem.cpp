#include "SoundSystem.h"

SoundSystem::SoundSystem()
{
	eventManager.registerFunc(this, &SoundSystem::onSoundEvent);
	for (int i = 0; i < m_channelMax; ++i)
		m_channel.push_back(sf::Sound{});
}

void SoundSystem::onSoundEvent(const Events::SoundEvent *evnt)
{
	const Events::SoundEventType *t = &(evnt->type);
	std::string name{ evnt->name };

	if (*t == Events::SoundEventType::AddMusic)
	{
		m_music.openFromFile(evnt->fName);
	}
	if (*t == Events::SoundEventType::AddSound)
	{
		m_soundBuffer[evnt->name] = sf::SoundBuffer{};
		auto &s = m_soundBuffer.find(name)->second;
		s.loadFromFile(evnt->fName);
	}
	if (*t == Events::SoundEventType::PlayMusic)
	{
		m_music.setLoop(evnt->loop);
		m_music.setVolume(evnt->volume);
		m_music.play();
	}
	if (*t == Events::SoundEventType::PlaySound)
	{
		sf::Sound *channel = &m_channel[m_channelIndex];
		sf::SoundBuffer &buffer = m_soundBuffer.find(evnt->name)->second;
		channel->setBuffer(buffer);
		channel->setVolume(evnt->volume);
		channel->setLoop(evnt->loop);
		channel->play();

		++m_channelIndex;
		if (m_channelIndex > m_channelMax) m_channelIndex = 0;
	}
	if (*t == Events::SoundEventType::StopMusic)
	{
		m_music.stop();
	}
	if (*t == Events::SoundEventType::StopSound)
	{
		sf::SoundBuffer *compare = &m_soundBuffer.find(evnt->name)->second;
		for (auto &c : m_channel)
		{
			if (c.getBuffer() == compare)
			{
				c.stop();
				break;
			}
		}
	}
}