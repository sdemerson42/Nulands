#pragma once

#include <vector>
#include <algorithm>

template<typename T>
class AutoList
{
public:
	AutoList()
	{
		m_refs.push_back(static_cast<T*>(this));
	}
	virtual ~AutoList()
	{
		T *targ = static_cast<T*>(this);
		auto p = std::find(m_refs.begin(), m_refs.end(), targ);
		if (p != m_refs.end()) m_refs.erase(p);
	}
	static int size()
	{
		return m_refs.size();
	}
	static T* get(int index)
	{
		return m_refs[index];
	}
private:
	static std::vector<T*> m_refs;
};

template<typename T>
std::vector<T*> AutoList<T>::m_refs;