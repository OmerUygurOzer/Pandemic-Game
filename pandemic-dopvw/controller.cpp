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
	string player1, player2, player3, player4;
	// Opening introduction and asking for number of players
	cout << "Welcome to Pandemic!" << endl; 
	cout << "Let's get started!" << endl; 
	cout << "How many Players will be playing?"<< endl;

	// Number of players input and validation
	cin >> numberofplayers;
        if (numberofplayers < 2 )
                {
                        cout << "There must be at least 2 players!" << endl;
                }
        else if (numberofplayers > 4)
                {
                        cout << "There cannont be more than 4 players!" << endl;
                }

	// Asking for Playyer names according to how many players 
	// there are
   
   
  //Added this part for role actions .
  char roles [7] = {'a','a' ,'a', 'a', 'a', 'a', 'a'};   //To keep a track of roles that are still available
	string rolenames[7] = {"Contingency Plan" , "Dispatcher" , "Medic" , "Operations Expert" , "Quarantine Specialist" , "Researcher" , "Scientist"}; //RoleNames
	RoleActions Role[numberofplayers];//Role Actions are being managed
   
  //Assigning the roles for both players
	// 't' means the profession is already taken
	// randomly assigns a profession to every player
	
	
	
	for (int ply = 0 ; ply<numberofplayers ; ply++){
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
	}
   
	if (numberofplayers == 2)
        {
                cout << "Please enter the name of the first player" << endl;
                cin >> player1;
                cout << "Please enter the name of the second player" << endl;
                cin >> player2;
        }
	if (numberofplayers == 3)
			{
                cout << "Please enter the name of the first player" << endl;
                cin >> player1;
                cout << "Please enter the name of the second player" << endl;
                cin >> player2;
                cout << "Please enter the name of the third player" << endl;
                cin >> player3;
			}
	if (numberofplayers == 4)
			{
                cout << "Please enter the name of the first player" << endl;
                cin >> player1;
                cout << "Please enter the name of the second player" << endl;
                cin >> player2;
                cout << "Please enter the name of the third player" << endl;
                cin >> player3;
                cout << "Please enter the name of the fourth player" << endl;
                cin >> player4;
			}
	
	PandModel GameInstance;
	GameInstance.setPlayerName(1,player1);
	GameInstance.setPlayerName(2,player2);
	//GameInstance.setPlayerName(3,player3);
	//GameInstance.setPlayerName(4,player4);

	
	PandView Screens(GameInstance);//need to copy current state of game
	//after each action, Screens will need to be updated to show current state of game

	Screens.showPlayerInfo(1);
	Screens.showPlayerInfo(2);
	Screens.showCityInfo(1);

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