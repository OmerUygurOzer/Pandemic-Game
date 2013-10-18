#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

using namespace std;

class PandController
{
public:

	PandController(PandModel m, PandView v);  // initializes the controller

	// * * functions to update view * *
	void updateView();  // updates the interface
	int whereIsPlayer();  // returns which city current player is in

	// * * functions to update model * *
	void setPlayerLocation();  // updates model where player has chosen to go
	void setPlayerMoves();  // updates model on how many moves player has left
	void NextTurn();  // ends current players turn and starts next players turn


private:
	// no data is stored in the controller
	PandModel model;
	PandView view;
	
};
#endif