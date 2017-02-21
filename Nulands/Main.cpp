#include <conio.h>
#include <time.h>

#include "NuGame.h"

using namespace std;


int main()
{	
	srand(time(NULL));
	NuGame *ng = new NuGame;

	while (true)
		ng->update();

	delete ng;

	_getch();
	return 0;

}