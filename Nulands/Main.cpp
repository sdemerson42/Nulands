#include <conio.h>
#include <time.h>

#include "NuScene.h"

using namespace std;


int main()
{	
	srand(time(NULL));
	NuScene *ng = new NuScene;

	while (true)
		ng->update();

	delete ng;

	_getch();
	return 0;

}