#pragma once

#include "ILayer.h"

class InOutLayer : public ILayer
{
public:
	InOutLayer()
	{
		eventManager.registerFunc(this, &InOutLayer::onTextOutput);
	}
	~InOutLayer()
	{
		eventManager.unregisterListener(this);
	}
	void update() override;
private:
	void onTextOutput(const Events::TextOutputEvent*);
	void print(const std::string&);
	static const int m_txtWidth;
};
