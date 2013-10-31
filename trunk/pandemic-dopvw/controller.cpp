#include "controller.h"
#include "roleactions.h"

PandController::PandController(PandModel m, PandView v){
	model = m;
	view = v;
	updateView(); // updates the interface with starting information from model
}

void PandController::updateView(){
	/* Will update view from information from model
		and prompt current player for his action
	*/
	int playerchoice, currentplayer;

	currentplayer = currentPlayer(); // sets current player

	// Show menu and prompt player for action (4 actions) 
	for(int i = 0; i < 4; i++){
		view.showActionMenu();  // display the action menu
		cin >> playerchoice;
		cout << "Player " << currentplayer << " has chosen action " << playerchoice << ".";
		// will have a call to the model here depending on action
	}

	NextTurn(); // starts next players turn

}

int PandController::whereIsPlayer(){
	// not done yet
	return 0;
}

int PandController::currentPlayer(){
	// not done yet
	return 0;
}

void PandController::setPlayerLocation(int player){
	// not done yet
}

void PandController::setPlayerMoves(int player){
	// not done yet
}

void PandController::NextTurn(){
	// not done yet
}

int main()
{
	int numberofplayers;
	string player[4];
	PandModel GameInstance;//start game
	PandView Screens(GameInstance);//need to copy current state of game
	//after each action, Screens will need to be updated to show current state of game

	// Opening introduction and asking for number of players
	Screens.showIntro();

	// Number of players input and validation
	//cin >> numberofplayers;
	bool validPlayer;
	validPlayer = false;

	while(validPlayer == false)
	{
		cin >> numberofplayers;
        if (numberofplayers < 2 )
                {
                        cout << "There must be at least 2 players!" << endl;
                }
        else if (numberofplayers > 4)
                {
                        cout << "There cannont be more than 4 players!" << endl;
                }
		if(numberofplayers >= 2 && numberofplayers <= 4) //if 2 or higher and 4 or less, approve
		{validPlayer = true;}
	}

  //Added this part for role actions ./////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  char roles [7] = {'a','a' ,'a', 'a', 'a', 'a', 'a'};   //To keep a track of roles that are still available
	string rolenames[7] = {"Contingency Plan" , "Dispatcher" , "Medic" , "Operations Expert" , "Quarantine Specialist" , "Researcher" , "Scientist"}; //RoleNames
	//RoleActions Role[numberofplayers];//Role Actions are being managed
   
  //Assigning the roles for both players
	// 't' means the profession is already taken
	// randomly assigns a profession to every player
	
	
	
	/*for (int ply = 0 ; ply<numberofplayers ; ply++){
		srand (time(NULL));
		bool taken = false;
		while (taken == false){
			int p = rand() % 7;
				if (!(roles [p] == 't')){
					//cout <<p<<endl;
					Players[ply].profession = p ;
					Role[ply].setPlayer(ply);
					Role[ply].setProfession(p);        
					roles[p] = 't';
					taken = true;
			}
		}
	}*/
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for(int i = 0; i < numberofplayers; i++)
	{
		cout << "Please enter the name of player " <<i+1<< endl;
		cin >> player[i];
		GameInstance.setPlayerName(i,player[i]);//set player names
	}

	//card draw test. Should pull Atlanta city card///////////
	PandView tempCard;
	playerCard tempHand = tempCard.drawPlayerCard(1);
	cout<<tempHand.cardType<<endl;
	cout<<tempHand.cardDescription<<endl;
	cout<<endl;
	//////////////////////////////////////////////////////////
	system("CLS");
	


	//Going to replace this with a while loop that checks for player's remaining moves
	//We just need to pay attention and have the actions remaining counter reset     -Vu
	for(int i = 1; i<numberofplayers+1; i++)////////////////////goes through 2 players 4 action of moving to neighboring cities. Will merge to updateview()
	{
		for(int j = 0; j<4; j++)
		{
			std::cout << std::string(50, '\n'); //temporary solution to reduce screen clutter

			PandView newScreen(GameInstance);//will refresh when it goes through loop
			Playerchar temp = GameInstance.getPlayerInfo(i-1);
			city tempcity = GameInstance.getCityInfo(i);
			newScreen.showPlayerInfo(i);
			newScreen.showCityInfo(temp.location);

			newScreen.showActionMenu();
			int ans;
			cin>>ans;
			if(ans == 1)
			{
				cout<<"Where would you like to move :" <<endl;//will move to view.h
				newScreen.showNeighbors(temp.location);
				int moveto;
				cin>>moveto;
				GameInstance.setPlayerLocation(i, newScreen.getNeighbor(temp.location, moveto-1));//set player location to new location.
			}
		}
		system("CLS");
	}
	system("pause");
	return 0;
}