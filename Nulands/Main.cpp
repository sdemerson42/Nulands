#include <conio.h>

using namespace std;

#include "InOutLayer.h"
#include "WorldLayer.h"

int main()
{
	vector<shared_ptr<ILayer>> v;
	v.push_back(make_shared<InOutLayer>());
	v.push_back(make_shared<WorldLayer>());

	while (true)
	{
		for (auto& sp : v)
			sp->update();
	}


	
	_getch();
	return 0;

}