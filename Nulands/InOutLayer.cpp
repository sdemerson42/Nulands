#include "InOutLayer.h"
#include <string>
#include <iostream>

using namespace std;

const int InOutLayer::m_txtWidth = 100;

void InOutLayer::update()
{
	cout << ">";
	string in;
	getline(cin, in);
	if (in == "exit") setLayerState(false);
	Events::PlayerCommandEvent pce{ in };
	eventManager.broadcast(&pce);
}

void InOutLayer::onTextOutput(const Events::TextOutputEvent* evnt)
{
	print(evnt->text());
}

void InOutLayer::print(const std::string& s)
{
	string os;
	int i = 0;
	int spcIndex = 0;
	while (i < s.length())
	{
		if (s[i] == ' ') spcIndex = i;
		os += s[i];
		++i;
		if (i % m_txtWidth == 0 && spcIndex != 0)
			os[spcIndex] = '\n';
	}
	cout << os << endl;
}