#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "IComponent.h"
#include "GTypes.h"
#include "AutoList.h"

class AnimatorSystem;

class AnimatorComponent : public IComponent, public AutoList<AnimatorComponent>
{
	friend class AnimatorSystem;
public:
	AnimatorComponent(Entity *parent) :
		IComponent{ parent }
	{}
	void update() override
	{}
	
	struct Animation
	{
		Animation(const std::string &_name, std::vector<float> _rectVals, int _speed, bool _loop = true) :
			name{ _name }, speed{ _speed }, loop{ _loop }
		{
			int i = 0;
			while (i < _rectVals.size())
			{
				frame.push_back(GTypes::Rect{ _rectVals[i], _rectVals[i + 1], _rectVals[i + 2], _rectVals[i + 3] });
				i += 4;
			}
		}
		std::string name;
		std::vector<GTypes::Rect> frame;
		bool loop;
		int speed;
	};

	void addAnimation(const Animation &a)
	{
		m_animation.push_back(a);
	}
	void play(const std::string &s)
	{
		auto a = std::find_if(m_animation.begin(), m_animation.end(), [s](const Animation &aa)
		{
			return aa.name == s;
		});
		if (a != m_animation.end())
		{
			m_animIndex = a;
			m_frameIndex = 0;
			m_counter = 0;
			m_animating = true;
		}
	}
	void stop()
	{
		m_animIndex = m_animation.end();
	}
private:
	std::vector<Animation> m_animation;
	std::vector<Animation>::iterator m_animIndex{ m_animation.end() };
	int m_frameIndex;
	int m_counter;
	bool m_animating;
};