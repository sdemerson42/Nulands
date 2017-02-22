#pragma once

namespace GTypes
{
	using EntityGuid = unsigned long long;

	struct Rect
	{
		Rect() {}
		Rect(float _x, float _y, float _w, float _h) :
			x{ _x }, y{ _y }, w{ _w }, h{ _h }
		{}
		float x{ 0 };
		float y{ 0 };
		float w{ 0 };
		float h{ 0 };
	};
};
