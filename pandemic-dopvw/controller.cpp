#include "controller.h"

PandController::PandController(PandModel m, PandView v){
	model = m;
	view = v;
}

void PandController::updateView(){
	// not done yet
}

int PandController::whereIsPlayer(){
	// not done yet
	return 0;
}

void PandController::setPlayerLocation(){
	// not done yet
}

void PandController::setPlayerMoves(){
	// not done yet
}

void PandController::NextTurn(){
	// not done yet
}

int main()
{
	PandModel GameInstance;
	PandView Screens;
	Screens.showCityInfo(1);
	Screens.showNeighbors(1);
	Screens.showActionMenu(1);
	int answer;
	std::cin>>answer;//modify to restrict input from 1-6
	//use answer to bring up other menu items.
	switch (answer)
	{
	case 1: Screens.showNeighbors(1);//and move to neighbor
		break;
	case 2: //use citycard
		break;
	case 3://remove cube
		break;
	case 4: //build research
		break;
	case 5: //show infected cities
		break;
	case 6://misc
		break;
	}
	return 0;
}