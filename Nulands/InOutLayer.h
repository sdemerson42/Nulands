#pragma once

#include "ILayer.h"

class InOutLayer : public ILayer
{
public:
	InOutLayer()
	{
		registerFunc(this, &InOutLayer::onTextOutput);
	}
	void update() override;
private:
	void onTextOutput(const Events::TextOutputEvent*);
	void print(const std::string&);
	static const int m_txtWidth;
};
