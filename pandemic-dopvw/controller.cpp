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
	return 0;
}