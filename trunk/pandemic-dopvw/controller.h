#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "view.h"

using namespace std;

class PandController
{
public:
	PandController(PandModel m, PandView v);  // initializes the controller
	void updateView();  // updates the interface
	void setPlayerTurn(int whoseturn);  // sets new players turn in model
	int getPlayerTurn();  // returns whose turn it is
	int getPlayerMoves();  // returns how many turns current player has left
	int whereIsPlayer();  // returns which city current player is in
	void setPlayerLocation();  // updates model with where current player is
	int getCard();  // draws next card from model


private:
	PandModel model;
	PandView view;
	
};
#endif