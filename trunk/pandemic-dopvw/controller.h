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
	int getPlayerTurn();  // returns whose turn it is
	int getPlayerMoves();  // returns how many turns current player has left
	int whereIsPlayer();  // returns which city current player is in
	int getCards();  // gets current players cards to display
	int getNumCubes(int city);  // returns number of infection cubes on city

	// * * functions to update model * *
	void setPlayerLocation();  // updates model where player has chosen to go
	void setPlayerCards();  // updates model what cards are now in players hand
	void setPlayerMoves();  // updates model on how many moves player has left
	void setNumCubes(int city);  // updates model on how many cubes are in city


private:
	// no data is stored in the controller
	PandModel model;
	PandView view;
	
};
#endif