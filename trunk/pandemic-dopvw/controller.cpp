#include "controller.h"
#include "roleactions.h"
#include <time.h>
#include <stack>
using namespace std;

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
		view.showActionMenu(model.getPlayerRole(i));  // display the action menu 
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
   



	for(int i = 0; i < numberofplayers; i++) 
	{
		cout << "Please enter the name of player " <<i+1<< endl;
		cin >> player[i];
		GameInstance.setPlayerName(i,player[i]);//set player names
		srand(time(NULL));
		bool taken = false;
		while (taken == false){ //Player roles are set(randomly)
			int p = rand() % 7;
			if (!(roles[p] == 't')){
				GameInstance.setPlayerRole(i, p, rolenames[p]);
				roles[p] = 't';
				taken = true;
			}
		}
	}

	//card draw test. Should pull Atlanta city card///////////
	PandView tempCard;
	playerCard tempHand = tempCard.drawPlayerCard(1);
	cout<<tempHand.cardType<<endl;
	cout<<tempHand.cardDescription<<endl;
	cout<<endl;
	//////////////////////////////////////////////////////////
	system("CLS");

	//Outbreak Test
	PandModel OutbreakTest;
	OutbreakTest.outbreak(1);
	OutbreakTest.outbreak(3);
	city tempcity = OutbreakTest.getCityInfo(9);//chicago has a red infection cube
	//Show Infection Test
	PandView InfectionTest(OutbreakTest);
	InfectionTest.showCubeLocations();

	//display role test
	PandView showRoleTest(GameInstance);
	showRoleTest.showPlayerRoleInfo(1);

	//shuffled infection deck ////////may turn this into a function in model.h void shuffledeck(int array[], maxnum);
	int shuffleInfection[48];
	const int infectionMax = 48;
	{
		srand(time(NULL));
		for(int i = 0; i<48;i++)
		{
			bool taken;
			int infectcardnum;
			do
			{
				infectcardnum = rand()%infectionMax;
				taken = true;
				for(int j = 0; j<i; j++)
					if(infectcardnum == shuffleInfection[j])
					{
						taken = false;
						break;
					}
			}while(!taken);
			shuffleInfection[i] = infectcardnum;
		}
	}///////////////////////////////////////////////////////////////////////////////

	stack<int> infectionDeck;////storing the array of randoms in a stack
	stack<int> discardInfectionDeck;//store discarded infection cards
	for(int i = 0; i <48; i++)
		infectionDeck.push(shuffleInfection[i]);
	////test draw infection card
	PandView tempinfect;
	infectionCard tempinfechand = tempinfect.drawInfectionCard(); // removed 'infectionDeck.top()' from function input because not needed
	cout<<tempinfechand.cardDescription<<" infected city \n";
	system("CLS");
	
//New Turn system		

	int charnum; //temp variable
	charnum = 0;

	//Initialize all turns to 0. // done in constructor
	/*Could someone do a constructor to automatically set this up?
	for(int i = 0; i < numberofplayers; i++)
	{
		GameInstance.ActionsInitialize(i);
	}*/

	//Gonna give the players some cards
	GameInstance.ReceiveCard(1, 0);
	GameInstance.ReceiveCard(1, 1);
	GameInstance.ReceiveCard(1, 9);
	GameInstance.ReceiveCard(2, 2);
	GameInstance.ReceiveCard(2, 46);
//	GameInstance.ReceiveCard(3, 4);
//	GameInstance.ReceiveCard(4, 6);



	//while(game not ended yet)
	while(charnum != -1) //Temp infinite loop - Insert a bool here to check if the game has ended
	{
		//if player = special profession, give them a different num of moves
		// { GameInstance.setActionsLeft(charnum, 6); }
		//else
		GameInstance.setActionsLeft(charnum, 3); //Change the second argument here for base # of moves
		//Set to 3 for quicker play


		//DEBUG cout << "Debug actionsleft:" << GameInstance.getActionsLeft(charnum) << endl << endl;


		while(GameInstance.getActionsLeft(charnum) != 0 ) //while player is not out of actions
		{
			//cout << string(50, '\n');
			cout << "Actions Remaining: " << GameInstance.getActionsLeft(charnum) << endl;
			PandView newScreen(GameInstance);//will refresh when it goes through loop
			Playerchar temp = GameInstance.getPlayerInfo(charnum);
			city tempcity = GameInstance.getCityInfo(charnum+1);
			newScreen.showPlayerInfo(charnum+1);
			newScreen.showCityInfo(temp.location);

			newScreen.showActionMenu(temp.profession);
			int ans;
			cin>>ans;


			/////////////////////////////////////////////////
			///////////Adjacent Movement////////////////////
			if(ans == 1)
			{
				cout<<"Where would you like to move :" <<endl;//will move to view.h
				newScreen.showNeighbors(temp.location);
				int moveto;
				cin>>moveto;
				//while (  validNeighbor(current location, moveto)   )
				//True =
				GameInstance.setPlayerLocation(charnum+1, newScreen.getNeighbor(temp.location, moveto-1));//set player location to new location.
				//False =
				//cin >>moveto
				cout << string(10, '\n');
			}
			////////////
			//Use card
			if(ans == 2)
			{
				if(GameInstance.CheckHand(charnum+1) == 0)
				{
				cout << endl << endl << "You have no cards!" << endl << endl;
				GameInstance.setActionsLeft(charnum, 1); //Return action used to Play Card
				}
				if(GameInstance.CheckHand(charnum+1) == 1) //If player has card, allow to play card
				{GameInstance.PlayCard(charnum+1);}

				


			}

			if(ans == 4)
			{
				GameInstance.ShuttleFlight(charnum+1);
			}




			///////////////////////////////////////////////////////////
			// WILL WORK ON IT LATER
			/*if (ans == 7)
			{
				if ((temp.profession == 0) & !(temp.extracardFlag)){
					
					cout << endl << "Pick a card:";
					GameInstance.performRoleActions(charnum, 7,0);

				}
				if ((temp.profession == 0) & (temp.extracardFlag)){
					cout << endl << "You already have a card!";
				}
				if (temp.profession == 1){

					Screens.showPlayersLocation(numberofplayers);
					cout << 
					GameInstance.performRoleActions(charnum, 7,0);

				}

			
			}

			*/



			////////////
			//Profession Ability



			/////////


			////////////Exit Function//////////////////////
			if(ans == 10)
			{
				charnum = -2; //Will add up to -1 and cause while loop to end
			}

			GameInstance.setActionsLeft(charnum, -1); //Subtracts one action
		}

		
		//Debug outputs show the current # of player before and after the changes
		//cout << "debug charnum before" << charnum << endl;
		//Next Player
		if(charnum != (numberofplayers-1) ) //If last player, go to first player
		{charnum++;} //0
		else if(charnum == numberofplayers-1){charnum = 0;} //go to next player


		//cout << "debug charnum after" << charnum << endl;
		
		cout << string(10, '\n');

		//system("CLS");
	}


	system("pause");
	return 0;
}