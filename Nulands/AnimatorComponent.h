#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "IComponent.h"
#include "GTypes.h"
#include "AutoList.h"
#include "Factory.h"

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
		Animation()
		{}
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
		m_animIndex = m_animation.end();
	}
	void play(const std::string &s)
	{
		auto a = std::find_if(m_animation.begin(), m_animation.end(), [s](const Animation &aa)
		{
			return aa.name == s;
		});
		if (a != m_animation.end() && a != m_animIndex)
		{
			m_animIndex = a;
			m_frameIndex = -1;
			m_counter = -1;
			m_animating = true;
		}
	}
	void stop()
	{
		m_animIndex = m_animation.end();
	}
	void initialize(const vector<string> &args) override
	{
		int animTotal = stoi(args[0]);
		int q = 1;
		for (int i = 0; i < animTotal; ++i)
		{
			Animation a;
			a.name = args[q];
			++q;
			int frameTotal = stoi(args[q]);
			++q;
			for (int j = 0; j < frameTotal; ++j)
			{
				a.frame.push_back(GTypes::Rect{ stof(args[q]), stof(args[q + 1]), stof(args[q + 2]), stof(args[q + 3]) });
				q += 4;
			}
			a.speed = stoi(args[q]);
			++q;
			if (args[q] == "true") a.loop = true;
			else a.loop = false;
			++q;
			addAnimation(a);
		}
	}
	void outState(std::ostream &ost) const override
	{
		ost << "{ Animator " << m_animation.size() << " ";
		for (auto &a : m_animation)
		{
			ost << a.name << " " << a.frame.size() << " ";
			for (auto f : a.frame)
				ost << f.x << " " << f.y << " " << f.w << " " << f.h << " ";
			ost << a.speed << " " << (a.loop ? "true" : "false") << "\n";
		}
		ost << "}\n";
	}
private:
	std::vector<Animation> m_animation;
	std::vector<Animation>::iterator m_animIndex{ m_animation.end() };
	int m_frameIndex;
	int m_counter;
	bool m_animating;
	static FactoryRegistry<AnimatorComponent> m_fReg;
};