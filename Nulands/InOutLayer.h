#pragma once

#include "ILayer.h"

class InOutLayer : public ILayer
{
public:
	void update() override
	{}
private:
	void print(const std::string&);
};
