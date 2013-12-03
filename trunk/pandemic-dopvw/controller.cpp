#include "controller.h"
#include <time.h>
#include <stack>
#include <string>
#include <algorithm>
#include <Windows.h>


using namespace std;


string delSpaces(string &str);

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
	//PIPING DATA TO WINDOWS FORM
	system("mkdir C:\\Pand");
	std::ofstream("C:\\Pand\\hfile.txt", std::ios::out).close();
	fstream tempfile;
	tempfile.open("C:\\Pand\\hfile.txt");
	tempfile << "Name -1 -1 -1 -1 -1 -1 -1 -1 ";
	tempfile.close();
	//PIPING DONE
	


	
	int numberofplayers;
	string player[4];
	PandModel GameInstance;//start game
	PandView Screens(GameInstance);//need to copy current state of game
	//after each action, Screens will need to be updated to show current state of game

	//Added this part for role actions ./////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char roles[7] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a' };   //To keep a track of roles that are still available
	string rolenames[7] = { "Contingency Plan", "Dispatcher", "Medic", "Operations Expert", "Quarantine Specialist", "Researcher", "Scientist" }; //RoleNames


	// Opening introduction and asking for number of players
	Screens.showIntro();

	
	int loadfile, savefile;
	char yn;

	// New Game or Load Game
	int opt;


	cin >> opt;

	while ((opt < 0) || (opt >2)){
		cout << "Invalid Input. Must be 1 or 2." << std::endl;
		cin >> opt;
	}

	if (opt == 2){ //Load

		load:
		system("CLS");
		for (int i = 0; i < 6; i++){
			cout << i + 1 << " - " << "Slot:" << GameInstance.GetAvail(i) << "	Game Name:" << GameInstance.GetGameName(i) << std::endl;
		}
		cout << "Chose a file to load from:";
		cin >> loadfile;

		while ((loadfile < 0) || (loadfile >6) || (GameInstance.GetAvail(loadfile - 1) == "Empty")){
			cout << "Invalid Input or Empty File. Can not Load." << std::endl;
			cin >> loadfile;
		}

		GameInstance.Load(loadfile);
		system("CLS");
		cout << "Game " << GameInstance.GetGameName(loadfile - 1) << " has been loaded from the file!" << std::endl;
		goto start;
	}
	

	system("CLS");
	Screens.askPlayerNumber();

	// Number of players input and validation
	//cin >> numberofplayers;
	bool validPlayer;
	validPlayer = false;

	while(!validPlayer)
	{
		char num[256];
		std::cout<<"Enter how many players: ";
		std::cin >> num;//this is being skipped the second time around for some reason.
		numberofplayers = atoi(num);
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

  
	GameInstance.setnumberOfPlayers(numberofplayers);
	GameInstance.assignRoles();//Assigns random roles

	for(int i = 0; i < numberofplayers; i++) 
	{
		cout << "Please enter the name of player " <<i+1<< endl;
		cin >> player[i];
		GameInstance.setPlayerName(i,player[i]);//set player names
	}
	////////////////////////////////////////////////////////////////////////


start:
	int charnum; //temp variable
	charnum = GameInstance.getTurn();
	// debug cout << charnum << endl;





	//Starting hand //need to check for epidemic cards
	for(int i = 0; i < numberofplayers; i++) 
	{
		int numofCards;
		playerCard tempCard;
		if(numberofplayers == 2) numofCards = 4;//2 players get 4 cards at start
		if(numberofplayers == 3) numofCards = 3;//3 players get 3 cards at start
		if(numberofplayers == 4) numofCards = 2;//4 players get 2 cards at start
		for (int j = 0; j<numofCards; j++)
		{
			tempCard = GameInstance.drawPlayerCard();//will draw from the shuffled player cards deck
			if(tempCard.value >47 && tempCard.value < 54)
			{
				j--;//epidemic card, do not store//
				//will need to reinsert epidemic card if drawn
			}
			else//there's a bug here when there are 4 players, hand is incorrect
				GameInstance.ReceiveCard(i+1,tempCard);//need to modify RecieveCard to take in an object of playercard. and store it on hand
		}
	}
	/////Hardcoded Cards for testing
	playerCard TESTcard;
	TESTcard.value = 55; //Testing 55 = Forecast
	TESTcard.cardDescription = "ForecastTest";
	GameInstance.ReceiveCard(1, TESTcard);

	playerCard TESTcard2;
	TESTcard2.value = 56;
	TESTcard2.cardDescription = "GovGrantTEST";
	GameInstance.ReceiveCard(1, TESTcard2);
	
	///////////////////////////////


	//while(game not ended yet) //STUB
	while(charnum != -1) //Temp infinite loop - Insert a bool here to check if the game has ended
	{


		if (GameInstance.getloadflag()){
			//in case we add a mid game load function
			GameInstance.setloadflag(0);
		}
		else{
			//if player = special profession
			//GameInstance.setActionsLeft(charnum, #)
			//else
			GameInstance.setActionsLeft(charnum, 4);//default 4 actions per turn
			
			} 
		//Change the second argument here for base # of moves
		//Default: Set to 3 for quicker play while debugging


		//DEBUG cout << "Debug actionsleft:" << GameInstance.getActionsLeft(charnum) << endl << endl;
		//Prints out actions left directly to see how many turns you have before anything happens

		while(GameInstance.getActionsLeft(charnum) != 0 ) //while player is not out of actions
		{
		into:
			system("CLS");
			GameInstance.updateHandsFile(charnum);
			//cout << string(50, '\n'); //Screen clearer.
			cout << "Actions Remaining: " << GameInstance.getActionsLeft(charnum) << endl;
			//GameInstance.loadActionsLeft(charnum, GameInstance.getActionsLeft(charnum) - 1);
			PandView newScreen(GameInstance);//will refresh when it goes through loop
			Playerchar temp = GameInstance.getPlayerInfo(charnum);
			city tempcity = GameInstance.getCityInfo(charnum+1);
			newScreen.showPlayerInfo(charnum+1);
			newScreen.showCityInfo(temp.location);

			newScreen.showActionMenu(temp.profession);
			string ans;
			cin>>ans;


			///////////Adjacent Movement////////////////////
			if(ans == "1")
			{
				cout<<"Where would you like to move :" <<endl;//will move to view.h
				newScreen.showNeighbors(temp.location);
				int moveto;
				cin>>moveto;
				//need a way to determine if the input is valid
				//The amount of cities vary.. should we just assume the player will make the correct input?
				GameInstance.setPlayerLocation(charnum+1, newScreen.getNeighbor(temp.location, moveto-1));//set player location to new location.
				cout << string(10, '\n');
			}
			
			/////////////Use Card/////////////////////////////
			if(ans == "2")
			{
				if(GameInstance.CheckHand(charnum+1) == 0)
				{
				cout << endl << endl << "You have no cards!" << endl << endl; //Maybe I'll move this to model. -Vu
				GameInstance.setActionsLeft(charnum, 1); //Return action used to Play Card
				}
				if(GameInstance.CheckHand(charnum+1) == 1) //If player has card, allow to play card
				{GameInstance.PlayCard(charnum+1);}



			////////EVENT CARD: FORECAST////////////////////
				if(GameInstance.ReturnForecast() == 1)
				{
					cout << "Forecast is being played!  Drawing 6 cards..." << endl;
					//cout << "Not implemented yet!" << endl << endl;
					int cardplace;
					infectionCard rearrange[6];

					for(int i = 0; i < 6; i++) //Draw 6 cards
					{
					infectionCard tempInfectCard = GameInstance.drawInfectionCard();
					PandView newCards(GameInstance);
					rearrange[i] = tempInfectCard;
					}

					int doneYet = 0;

					//Note: I'm using a copy of the cards inside rearrange. Instead of making a new flag
					//I just use .colors as my flag and change it. Game is unaffected.  -Vu
					while(doneYet != 1) //while cards not all placed
					{
						for(int i = 0; i < 6; i++)
						{
							if(rearrange[i].color != -1)
							{cout << i+1 << ". " << "Infection:  " << rearrange[i].cardDescription << endl;}
							//DEBUG : Test to see if flags for card already used is set
							//cout << "DEBUG #" << i+1 << " = " << rearrange[i].color << endl;
						}
						cout << "Choose which card to place on top of the deck (1-6): ";
						cin >> cardplace;
						while(cardplace < 1 || cardplace > 6)
						{cout << "Invalid Input!" << endl; cin >> cardplace;}
						cardplace = cardplace -1; //1 to 0 fix
						
						if(rearrange[cardplace].color != -1)
						{
							GameInstance.placeInfectionCard(rearrange[cardplace]);
							rearrange[cardplace].color = -1;
						}
						else{cout << "Card already chosen!" << endl;}


						//Loop had issues.. trying the long way  -  Tested and it works.
						if(rearrange[0].color == -1 && rearrange[1].color == -1 && rearrange[2].color == -1 && 
							rearrange[3].color == -1 && rearrange[4].color == -1 && rearrange[5].color == -1)
						{doneYet = 1;}
						cout << endl;
					}

					GameInstance.setForecastPlayed(0); //Forecast has been played and ended
					//DEBUG////////////
					/*
					cout << "DEBUG: DRAWING TOP CARD (should be last card you put in)" << endl;
					infectionCard tempInfectCard = GameInstance.drawInfectionCard();
					PandView newCards(GameInstance);
					newCards.showInfectCard(tempInfectCard);//display infection card drawn
					*/
					cout << endl << endl;
					//////////////////
				}

			}

			if(ans == "3") // treat city
			{
				int cubecolor;
				cout << "What color cube would you like to treat?(r, g ,b , y)\n";
				cin >> cubecolor;
				while (cubecolor != 'r' && cubecolor != 'g' && cubecolor != 'b' && cubecolor != 'y')
				{
					cout << "Please enter valid cube color: r, g, b, or y\n";
					cin >> cubecolor;
				}
				GameInstance.treatCity(GameInstance.getPlayerLocation(charnum), cubecolor, GameInstance.getPlayerRole(charnum));
			}

			if(ans == "4")//shuttleFlight
			{GameInstance.ShuttleFlight(charnum+1);}

			if(ans == "5")
			{
				newScreen.showCubeLocations();
				GameInstance.setActionsLeft(charnum, 1);
			}



			if(ans == "6") //Tester: This prints all the cities in 3 columns, no additional info.
			{
				int printchoice;
				cout << "1. Cities only" << endl;
				cout << "2. Infected Cities" << endl;
				cout << "3. Research Centers" << endl;
				cout << endl << "What would you like shown? : ";
				cin >> printchoice;
				cout << endl;
				if(printchoice == 1)
				{newScreen.printCityColumns();}
				if(printchoice == 2)
				{newScreen.showCubeLocations();}
				if(printchoice ==3)
				{newScreen.printResearchCenters();}
				GameInstance.setActionsLeft(charnum,1);
			}

			if (ans == "9")//game save
			{
			save:	
				string sfname;
				system("CLS");
				for (int i = 0; i < 6; i++){
					cout << i + 1 << " - " << "Slot:" << GameInstance.GetAvail(i) << "	Game Name:" << GameInstance.GetGameName(i) << std::endl;
				}
				cout << "Slot Number:";
				cin >> savefile;
				cout << std::endl;

				while ((savefile < 0) || (savefile >6) ){
					cout << "Invalid Input. Can not save." << std::endl;
					cout << "Slot Number:";
					cin >> savefile;
					cout << std::endl;
				}
				if (GameInstance.GetAvail(savefile - 1) == "Used"){
					
					cout << std::endl << "File is already used. Overwrite? (Y/N)";
				ynInput:
					cin >> yn;
					if ((yn == 'y') || (yn == 'Y')){
						cout << std::endl;
						cout << "Name of your game:";
						cin >> sfname;
						cout << std::endl;
						
						//sfname = delSpaces(sfname);
						

						GameInstance.Save(savefile,sfname,charnum);
						system("CLS");
						cout << "GAME HAS BEEN SAVED INTO SLOT " << savefile << "." << std::endl << std::endl;
						goto into;
					}
					else if ((yn == 'n') || (yn == 'N')){
						goto save;
					}
					else{
						cout << std::endl << "Y/N ?";
						goto ynInput;
					}
				}
				else
				{
					cout << std::endl;
					cout << "Name of your game:";
					cin >> sfname;
					cout << std::endl;
					
					//sfname = delSpaces(sfname);
					

					GameInstance.Save(savefile,sfname,charnum);
					system("CLS");
					cout << "GAME HAS BEEN SAVED INTO SLOT " << savefile << "." << std::endl << std::endl;
					goto into;
				}





			}

			if (ans == "10")
			{
				goto load;
			}
			// Only these role have active abilities: "Contingency Plan", "Dispatcher","Operations Expert","Researcher"

			if (ans == "a"){ ////////////////////// ===ACTIVE ROLE ABILITES SHOULD BE CALLED HERE
				if (GameInstance.getPlayerRole(charnum) == 0){//"Contingency Plan"

				}
				if (GameInstance.getPlayerRole(charnum) == 1){//"Dispatcher"
					
					for (int i = 0; i < GameInstance.getnumberOfPlayers(); i++){
						if (charnum != i)cout << i << ")" << GameInstance.getPlayerName(i) << " @ " << GameInstance.getCityName(GameInstance.getPlayerLocation(i)) << endl;

					}
					cout << "Chose a player pawn to move:";
					int pick;
					cin >> pick;
					while (pick<0 || pick > GameInstance.getnumberOfPlayers()-1 || pick == charnum){
						cout << endl << "Invalid Entry. Try Again:";
						cin >> pick;
						cout << endl;
					}
					
					for (int i = 0; i < GameInstance.getnumberOfPlayers(); i++){
						if (i != pick){ cout << i << ")" << GameInstance.getCityName(GameInstance.getPlayerLocation(i)) << endl; }

					}

					cout << "Where would you like to move " << GameInstance.getPlayerName(pick)<<"?";
					int target;
					int loc;
					cin >> target;
					while (target<0 || target>GameInstance.getnumberOfPlayers()-1 || target == pick){
						cout << endl << "Invalid Entry. Try Again:";
						cin >> target;
						cout << endl;
					}
					loc = GameInstance.getPlayerLocation(target);
					GameInstance.setPlayerLocation(pick+1, loc);


				}
				if (GameInstance.getPlayerRole(charnum) == 3){//"Operations Expert"

				}
				if (GameInstance.getPlayerRole(charnum) == 5){//"Researcher"

				}

			}
			if (ans == "b"){ ///////////////////// ====AND HERE
				if (GameInstance.getPlayerRole(charnum) == 1){//"Dispatcher"
					for (int i = 0; i < GameInstance.getnumberOfPlayers(); i++){
						if (charnum != i)cout << i << ")" << GameInstance.getPlayerName(i) << " @ " << GameInstance.getCityName(GameInstance.getPlayerLocation(i))<< endl;

					}
					cout << "Chose a player pawn to move:";
					int pick;
					cin >> pick;
					while (pick<0 || pick>GameInstance.getnumberOfPlayers()-1 || pick == charnum){
					cout << endl << "Invalid Entry. Try Again:";
					cin >> pick;
					cout << endl;
					}
					Screens.showNeighbors(GameInstance.getPlayerLocation(pick));
					int moveto;
					Playerchar temploc = GameInstance.getPlayerInfo(pick);
					cin >> moveto;
					GameInstance.setPlayerLocation(pick+1, newScreen.getNeighbor(temploc.location, moveto - 1));//set player location to new location.
				}

			}




			////////////Exit Function//////////////////////
			if(ans == "11")
			{
				charnum = -2; //Will add up to -1 and cause while loop to end. Kind of just crashes the program
			}

			//research cure
			if(ans == "12")
			{
				newScreen.showPlayerHand(charnum+1);
				

				bool researchSuccess = GameInstance.researchCure(charnum+1);
				if(!researchSuccess)//if research not successful
					GameInstance.setActionsLeft(charnum, 1);//give back 1 action pt.
				
			}

			GameInstance.cleanHand(charnum+1);
			GameInstance.setActionsLeft(charnum, -1); //Subtracts one action

		}//end of player turn

		//draw 2 player cards
		cout<<"Draw 2 player cards \n";
		for(int i = 0; i < 2; i++)
		{
			playerCard drawn = GameInstance.drawPlayerCard();//draw from deck
			PandView newCards(GameInstance);
			newCards.showPlayCard(drawn);//display play card drawn
			//if epidemic card
			if(drawn.value > 47 && drawn.value < 54)//if epidemic card
				GameInstance.epidemicDrawn();//call epidemic function

			else{
			//else store in hand
			cout << "Debug: You are player #" << charnum << endl << endl;
			GameInstance.ReceiveCard(charnum+1, drawn);//draw card and store in hand
			newCards.showHowManyPlayerCardsLeft();
			}
		}
		system("pause");

		//draw 2-4 infection cards. How many drawn depends on infection rate.
		cout<<"Draw " << GameInstance.getInfectionRate() << " infection cards\n";
		for(int i = 0; i < GameInstance.getInfectionRate(); i++)
		{
			infectionCard tempInfectCard = GameInstance.drawInfectionCard();
			PandView newCards(GameInstance);
			newCards.showInfectCard(tempInfectCard);//display infection card drawn
			GameInstance.addDiseaseCubes(tempInfectCard.city, tempInfectCard.color);//if 3 cubes already exist, if so, dont add 3 but cause outbreak. Done in model
		}
		system("pause");

		//Next Player
		if(charnum != (numberofplayers-1) ) //If last player, go to first player
		{charnum++;} //0
		else if(charnum == numberofplayers-1){charnum = 0;} //go to next player



		
		cout << string(10, '\n');

		//system("CLS");
	}


	system("pause");
	return 0;
}
// Does not work. So irritated :D supposed to return the same string with all the spaces replaced with underscores
string delSpaces(string &str)
{
	int size = str.length();
	for (int j = 0; j < size; j++)
	{
		if (isspace(str[j])){ str.replace(j, 1, "_"); }
	}
	return str;
}



