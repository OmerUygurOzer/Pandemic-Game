#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <deque>
#include <time.h>
#include <fstream>




////Just gonna include these for now for my functions to work   -Vu
using namespace std;
#include <iostream>
//////////////////////////////////////////

struct city//empty city container
{
	std::string cityName;//city name
	int adjacentCities[7];//I don't think any city has more than 6 adjacent cities, so 7
						  //adjacentCities will house the values of cities that are adjacent to the selected city
	char cityColor;//city color
	int diseasecubes[4]; //Number of disease cubes currently for each of the 4 colors(0,1,2,3 = red,black,blue,yellow)
	bool researchcenter; //Could be a bool instead, 0 or 1 to indicate presence of a research center
	
};

struct playerCard
{
	int value; //Holds the card's number
	std::string cardType;
	std::string cardDescription;
	char color;
};
struct infectionCard
{
	std::string cardType;
	std::string cardDescription;
	int city; // city of the card
	int color; // color of the card (0,1,2,3 = red,black,blue,yellow)
};

struct Playerchar  //Probably want to change to a class when we do the cards in hand data
{
	std::string playerName;
	int profession; //Player's profession will be designated by a value. Something else will transfer the value to
	//the data holding all of the professions and all of their effects
	std::string profName; //The name of their profession
	int location; //This will be the ID number of the city the character is currently located.
	

	////change cardsonhand to linked list
	playerCard cardsonhand[7]; //Player can hold 7 cards
	playerCard CPextracard; //Extra card for the contigency planner
	bool extracardFlag;// = false; //whether a card is chosen already or not


	//If player draws a card and num of cards > 7, player can use cards until less than 7, or discard.
	bool cardSlotAvailable[7];//if player uses a card from anywhere but end we'll need to keep track or use a shift

	int ActionsLeft; //This is an int that we'll be accessing to determine the remaining actions a player has left
};


class PandModel
{
	city cities[48];//48 cities, will fill in values with the constructor
	Playerchar players[4];//maximum 4 players
	playerCard playerDeck[59];//59 Player cards
	std::deque<playerCard> PlayerDeckD;//can use shufflePlayerDeck to shuffle
	std::deque<infectionCard> infectionDeck;//48 infection cards shuffled
	std::deque<infectionCard> discardInfectionDeck;//discarded infection cards
	std::deque<playerCard> discardPlayerDeckD;//discarded player cards
	int diseaseCubes[4]; // number of disease cubes left for each color, (0,1,2,3 = red,black,blue,yellow)
	int outbreakLevel;//0-8, if 8 game is over?
	int infectionRate;//not sure why this was removed before. Will need to reimplement to match board rate level/ ex: 2-2-2-3-3-4-4 maybe stack<int> infectionRate; populate in constructor and use increaseInfectRate();
	

	//SAVE-LOAD VARIABLES////////////////////////////
	string availability[6]; //availabilty of the files
	string gameName[6];
	int numberOfPlayers;
	int playerturn;
	bool loadflag;
	/////////////////////////////////////////////////
public:
	PandModel();
	//observers
	city getCityInfo(int citynum) {return cities[citynum];}//maybe seperate into getcityname, getadjcities, getcubes...etc
	int getNeighbor(int currentcity, int nextcity){return cities[currentcity].adjacentCities[nextcity];}
	bool validNeighbor(int currentcity, int nextcity); //stub - need function to work with Ly's new movement function to check adjacency
	int getnumberOfPlayers();
	string getPlayerName(int pno);
	int getPlayerLocation(int pno);
	//int getActionsLeft(int pno);
	char getCityColor(int cno);
	int getDiseaseCubes(int cno, int a);
	int getRCenter(int cno);
	int getoutbreakLevel();
	int getDCLeft(int a);//Disease cubes left
	int getTurn();
	bool getloadflag(){ return loadflag; };//Whether the game is being loaded or starting as a new game
	void setloadflag(int x){ loadflag = x; };

	Playerchar getPlayerInfo(int playernum){return players[playernum];}
	playerCard drawPlayerCard();//will draw from playerDeckD and return card on top of deck
	infectionCard drawInfectionCard();//will draw from top of infection deck
	void discardPlayCard(playerCard discarding);//add a discarded card to discarded player card pile
	bool returnResearch(int citynum){return cities[citynum].researchcenter;}

	void PrintAdjacent();
	void FillAdjacent(int a, int b, int c, int d, int e, int f, int g, int citynum);
	//void FillValue(int x) {value = x;};
	bool isAdjacent(int x);	//For ground travel, will check if desired destination is included in adjacentCities
	//setters
	void setPlayerName(int playernum, std::string name);
	void setPlayerRole(int playernum, int profession, std::string profName);
	void setPlayerLocation(int playernum, int location);//use to set new location
	void setDiseaseCubes(int cno, int a, int b, int c, int d);
	void ShuttleFlight(int playernum);
	//void ActionsInitialize(int playernum) {players[playernum].ActionsLeft = 0;}
	void setActionsLeft(int playernum, int addAction); // {Playerchar.ActionsLeft += addAction;       }
	int getActionsLeft (int playernum) {return players[playernum].ActionsLeft;}
	

	int getInfectionRate(){return infectionRate;}//for view to access/display infection rate
	int getPlayerRole(int playerNo){ return players[playerNo].profession; } //returns the player role
	void setInfectionRate();//stub
	void setOutbreakLevel();//stub
	void addResearchCenter(int city){cities[city].researchcenter=true;}//build research center at current city. Will need a check to see if research center already exists
	
	void shuffleInfectionDeck(deque<infectionCard> &shuffleDeck);//shuffle infection deck pass in a deque<infectionCard>
	void shufflePlayerDeck(deque<playerCard> & shuffleDeck);//shuffle player deck pass in a deque<playerCard>
	void outbreak(int city);//stub
	//Role action:
	void performRoleActions(int playernum, int actionNo , int loc); //Performs unique player actions
	
	void PlayCard(int playernum); //Stub
	int CheckHand(int playernum) {	//If player has non-blank card, return 1
		int z = 0;
		for(int i = 0; i < 7; i++)
		{if(players[playernum].cardsonhand[i].value != -1)
		{z = 1;}
		}
		return z;
	}
	void ReceiveCard(int playernum, int cardnum); //Player # - Receives card #  -Functional but not complete    -Vu

	// SAVE-LOAD/////////////////////////////////////////////////////////////////////////////////////////////////////
	void Save(int loadf, string sfname, int turn);
	void Load(int loadf);
	void Update();
	string GetAvail(int x);
	string GetGameName(int x);
	void loadPlayerLocation(int playernum, int location);
	void setnumberOfPlayers(int pno);
	void loadActionsLeft(int pno, int act);
	void loadCityColor(int cno, char c);
	void loadRcenter(int cno, int rc);
	void loadoutbreakLevel(int obl);
	void loadinfectionRate(int ir);
	void loadDCLeft(int a, int b, int c, int d);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

PandModel::PandModel()//constructor
{
	outbreakLevel = 0;
	infectionRate = 0;
	playerturn = 0; //turn indicator
	loadflag = false;

	//SAVE-LOAD ////////////////////////////////////////////////////////////////////////////////////////////////
	string str;//temporary string
	int iterator = 0;
	fstream mainf("SaveMain.txt");
	while (mainf >> str)
	{
		if (str == "#"){
			//Do Nothing
		}
		else{
			availability[iterator] = str;
			mainf >> str;
			gameName[iterator] = str;
			iterator++;
		}
	}
	mainf.close();


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	char citycolors[48]= {'G', 'B', 'G', 'R', 'R', 'Y', 'Y', 'G', 'G', 'B',
							'G', 'B', 'R', 'R', 'G', 'R', 'Y', 'G', 'Y', 'Y',
                            'G', 'Y', 'Y', 'B', 'Y', 'B', 'R', 'Y', 'Y', 'B',
                            'G', 'G', 'B', 'R', 'B', 'G', 'B', 'Y', 'Y', 'R',
                            'R', 'B', 'R', 'R', 'G', 'R', 'B', 'B'};
	for(int i = 0; i<48; i++)
		cities[i].cityColor = citycolors[i];//assign city colors to cities

	 std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
                            "Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
                            "Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
                            "Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};

	 for(int i = 0; i<4; i++){ // have 24 disease cubes of each color at start of game
		 diseaseCubes[i] = 24;
	 }

	 for(int i = 0; i < 7; i++) //Empty player hand initialize    -Vu
	 {
		 players[0].cardsonhand[i].value = -1; //Basically with value =-1, the player is holding "blank" cards
		 players[1].cardsonhand[i].value = -1; //If card is a blank, allow receiving of a real card
		 players[2].cardsonhand[i].value = -1; //Initialize all players to blank
		 players[3].cardsonhand[i].value = -1;
	 }
	 infectionCard infectCard;
	 for(int i = 0; i<48; i++)//city cards for infection deck populated but not shuffled
	 {
		 infectCard.cardType = "City";
		 infectCard.cardDescription = cityname[i];
		 infectCard.city = i;
		 infectCard.color = citycolors[i];  // needs to be set to correct color depending on city name
		 infectionDeck.push_back(infectCard);//add onto infectiondeck after info populated 
	 }
	 shuffleInfectionDeck(infectionDeck);//shuffle deck at start of game

	 for(int i = 0; i<48; i++)//city cards for player deck
	 {
		 playerDeck[i].cardType = "City";
		 playerDeck[i].cardDescription = cityname[i];
		 playerDeck[i].value = i;
		 playerDeck[i].color = citycolors[i];
	 }
	 for(int i = 48; i<54; i++)//epidemic cards for player deck
	 {
		 playerDeck[i].cardType = "Epidemic";
		 playerDeck[i].cardDescription = "1.Increase\n 2.Infect\n 3.Intensify\n";
	 }
	 ////////////////////////////////////////////////Special Event Cards for player deck
	 playerDeck[54].cardType = "Special Event";
	 playerDeck[54].cardDescription = "Airlift: Move a pawn ( yours or another player's) to any city. You must have a player's permission to move their pawn \n";

	 playerDeck[55].cardType = "Special Event";
	 playerDeck[55].cardDescription = "Forecast: Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile. \n";

	 playerDeck[56].cardType = "Special Event";
	 playerDeck[56].cardDescription = "Government Grant: Add a Research Station to any city for free \n";

	 playerDeck[57].cardType = "Special Event";
	 playerDeck[57].cardDescription = "One Quiet Night: The next player to begin the Playing the Infector phase of their turn may skip that phase entirely \n";

	 playerDeck[58].cardType = "Special Event";
	 playerDeck[58].cardDescription = "Resilient Population: Take a card from the Infection Discard Pile and remove it from the game \n";

	 for(int i = 0; i < 59; i++)
		 PlayerDeckD.push_back(playerDeck[i]);
	 shufflePlayerDeck(PlayerDeckD);


	 for(int i = 0; i < 48; i++)
	{
		cities[i].cityName = cityname[i];
		cities[i].cityColor = citycolors[i];
		cities[i].researchcenter = 0;
		for(int j = 0; j < 5; j++)
			cities[i].diseasecubes[j] = 0;//initialize cube count to 0

	}
/* This was causing program to crash upon run
	 // ** Place starting infection cubes **
	for(int i = 3; i > 0; i--){
		infectionCard current;
		for(int f = 0; f < 3; f++){
			current = drawInfectionCard();  // Draw next card in infection deck
			cities[current.city].diseasecubes[current.color] = i;  // place i cubes of color and city matching drawn card
			diseaseCubes[current.color] -= i;  // remove the disease cubes from remaining
		}
	}
*/
	//-1 Is a filler
        FillAdjacent(25,34,14,7, -1, -1, -1, 0);
        FillAdjacent( 9, 47, 28, -1, -1, -1, -1, 1);
        FillAdjacent( 14, 7, 35, 17, 44, -1, -1, 2);
        FillAdjacent( 20, 8, 15, 12, 13, -1, -1, 3);
        FillAdjacent( 40, 39, -1, -1, -1, -1, -1, 4);
        FillAdjacent( 27, 28, 22, 6, 38, -1, -1, 5);
        FillAdjacent( 5, 38, -1, -1, -1, -1, -1, 6);
        FillAdjacent( 0, 14, 2, 35, 18, -1, -1, 7);
        FillAdjacent( 31, 10, 20, 3, 15, -1, -1, 8);
        FillAdjacent( 36, 24, 27, 1, 46, -1, -1, 9);
        FillAdjacent( 44, 17, 31, 8, 20, -1, -1, 10);
        FillAdjacent( 23, 34, 29, 41, -1, -1, -1, 11);
        FillAdjacent( 15, 3, 13, 26, -1, -1, -1, 12);
        FillAdjacent( 20, 3, 12, 26, 43, 40, -1, 13);
        FillAdjacent( 41, 29, 0, 7, 2, 30, -1, 14);
        FillAdjacent( 3, 8, 42, 12, -1, -1, -1, 15);
        FillAdjacent( 19, 18, -1, -1, -1, -1, -1, 16);
        FillAdjacent( 44, 2, 35, 31, 10, -1, -1, 17);
        FillAdjacent( 7, 21, 19, 16, -1, -1, -1, 18);
        FillAdjacent( 21, 18, 16, -1, -1, -1, -1, 19);
        FillAdjacent( 10, 8, 3, 13, -1, -1, -1, 20);
        FillAdjacent( 38, 19, 18, -1, -1, -1, -1, 21);
        FillAdjacent( 27, 5, 37, -1, -1, -1, -1, 22);
        FillAdjacent( 32, 25, 34, 11, -1, -1, -1, 23);
        FillAdjacent( 36, 9, 27, 42, -1, -1, -1, 24);
        FillAdjacent( 32, 23, 34, 0, 38, -1, -1, 25);
        FillAdjacent( 43, 13, 12, 42, 36, -1, -1, 26);
        FillAdjacent( 9, 24, 22, 5, 28, -1, -1, 27);
        FillAdjacent( 1, 27, 5, 47, -1, -1, -1, 28);
        FillAdjacent( 11, 34, 14, -1, -1, -1, -1, 29);
        FillAdjacent( 41, 14, 44, -1, -1, -1, -1, 30);
        FillAdjacent( 17, 10, 8, -1, -1, -1, -1, 31);
        FillAdjacent( 23, 25, 46, 47, -1, -1, -1, 32);
        FillAdjacent( 45, 43, -1, -1, -1, -1, -1, 33);
        FillAdjacent( 11, 23, 25, 0, 29, -1, -1, 34);
        FillAdjacent( 17, 2, 7, -1, -1, -1, -1, 35);
        FillAdjacent( 45, 26, 9, 24, -1, -1, -1, 36);
        FillAdjacent( 22, -1, -1, -1, -1, -1, -1, 37);
        FillAdjacent( 5, 6, 21, 25, -1, -1, -1, 38);
        FillAdjacent( 4, 40, 45, -1, -1, -1, -1, 39);
        FillAdjacent( 4, 39, 45, 43, 13, -1, -1, 40);
        FillAdjacent( 11, 30, 14, -1, -1, -1, -1, 41);
        FillAdjacent( 24, 26, 15, -1, -1, -1, -1, 42);
        FillAdjacent( 33, 40, 13, 26, -1, -1, -1, 43);
        FillAdjacent( 30, 2, 17, 10, -1, -1, -1, 44);
        FillAdjacent( 36, 33, 40, 39, -1, -1, -1, 45);
        FillAdjacent( 32, 47, 9, -1, -1, -1, -1, 46);
        FillAdjacent( 46, 32, 28, 1, -1, -1, -1, 47);

		players[0].location = 1;//default start location Atlanta CDC
		players[1].location = 1;//default start location Atlanta CDC
		players[2].location = 1;//default start location Atlanta CDC
		players[3].location = 1;//default start location Atlanta CDC

		players[0].ActionsLeft = 0;//actions left initialized to 0
		players[1].ActionsLeft = 0;//actions left initialized to 0
		players[2].ActionsLeft = 0;//actions left initialized to 0
		players[3].ActionsLeft = 0;//actions left initialized to 0
		
		addResearchCenter(1);//Atlanta CDC research center default
}




void PandModel::FillAdjacent(int a, int b, int c, int d, int e, int f, int g, int citynum)
	{
		cities[citynum].adjacentCities[0] = a;
		cities[citynum].adjacentCities[1] = b;
		cities[citynum].adjacentCities[2] = c;
		cities[citynum].adjacentCities[3] = d;
		cities[citynum].adjacentCities[4] = e;
		cities[citynum].adjacentCities[5] = f;
		cities[citynum].adjacentCities[6] = g;
	};

//FOR SAVE AND LOAD /////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PandModel::setnumberOfPlayers(int pno){ numberOfPlayers = pno; }
void PandModel::loadActionsLeft(int pno, int act){ players[pno].ActionsLeft = act; }
void PandModel::loadCityColor(int cno, char c){ cities[cno].cityColor = c; }
void PandModel::loadRcenter(int cno, int rc){ cities[cno].researchcenter = rc; }
void PandModel::loadoutbreakLevel(int obl){ outbreakLevel = obl; }
void PandModel::loadinfectionRate(int ir){ infectionRate = ir; }
void PandModel::loadDCLeft(int a, int b, int c, int d){ diseaseCubes[0] = a; diseaseCubes[1] = b; diseaseCubes[2] = c; diseaseCubes[3] = d; }
int PandModel::getnumberOfPlayers(){ return numberOfPlayers; }
string PandModel::getPlayerName(int pno){ return players[pno].playerName; }
int PandModel::getPlayerLocation(int pno){ return players[pno].location; }
int PandModel::getTurn(){ return playerturn; }
void PandModel::loadPlayerLocation(int playernum, int location){
	players[playernum].location = location;
}
void PandModel::Update(){
	string str;//temporary string
	int iterator = 0;
	fstream mainf("SaveMain.txt");
	while (mainf >> str)
	{
		if (str == "#"){
			//Do Nothing
		}
		else{
			availability[iterator] = str;
			mainf >> str;
			gameName[iterator] = str;
			iterator++;
		}
	}
	mainf.close();
}

string PandModel::GetAvail(int x){ return availability[x]; }
string PandModel::GetGameName(int x){ return gameName[x]; }

char PandModel::getCityColor(int cno){ return cities[cno].cityColor; }
int PandModel::getDiseaseCubes(int cno, int a){ return cities[cno].diseasecubes[a]; }
int PandModel::getRCenter(int cno){ if (cities[cno].researchcenter) { return 1; } else{ return 0; } }
int PandModel::getoutbreakLevel(){ return outbreakLevel; }
int PandModel::getDCLeft(int a){ return diseaseCubes[a]; }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PandModel::setPlayerName(int playernum, std::string name)
{
	players[playernum].playerName = name;
}

void PandModel::setPlayerLocation(int playernum, int location)
{
	players[playernum-1].location = location;
}

void PandModel::setActionsLeft(int playernum, int addAction)
{
	players[playernum].ActionsLeft = players[playernum].ActionsLeft + addAction;
}
void PandModel::setDiseaseCubes(int cno, int a, int b, int c, int d){
	cities[cno].diseasecubes[0] = a;
	cities[cno].diseasecubes[1] = b;
	cities[cno].diseasecubes[2] = c;
	cities[cno].diseasecubes[3] = d;
}

////////////////CURRENTLY WORKING ON   -VU////////////////////////////////
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void PandModel::ReceiveCard(int playernum, int cardnum)
{
	int z = 0; //Variable check

	for(int i = 0; i < 7; i++)
	{
		if(players[playernum].cardsonhand[i].value == -1)
		{
			players[playernum].cardsonhand[i].value = playerDeck[cardnum].value;
			players[playernum].cardsonhand[i].cardType = playerDeck[cardnum].cardType;
			players[playernum].cardsonhand[i].cardDescription = playerDeck[cardnum].cardDescription;
			players[playernum].cardsonhand[i].color = playerDeck[cardnum].color;
			
			i = 10; //If card placed into hand, end loop
			z = 1; //Card Received
		}
		
	}

	//Alter this later for when the player hits maximum cards

	
}

void PandModel::PlayCard(int playernum)
{
	//Print cards in hand/////////////////////////////////////////
	cout << "Cards on hand:" << endl;
	//cout << "Color || Type || Name - Effect" << endl;

	for(int i = 0; i < 7; i++)
	{
		
		if(players[playernum].cardsonhand[i].value != -1)
		{
			cout << "#" << i+1 << "    ";
			cout << players[playernum].cardsonhand[i].color << " || ";
			cout << players[playernum].cardsonhand[i].cardType << " || ";
			cout << players[playernum].cardsonhand[i].cardDescription << endl;
		}
	}
	////////////////Hand print end////////////////////////////////

	int cardchoose;
	cout << "Choose your card: ";
	cin >> cardchoose;
	cardchoose = cardchoose - 1; //Player displays cards as 1 to 7. If select 1, we need to access deck[0]

	//if cardchoose = not valid
	//cin >> cardchoose

	//ifcardchoose = 8 (exit)     //If we want to give an option to cancel using a card
	// playerturn +1  (player gains back used turn)

	if(players[playernum].cardsonhand[cardchoose].value < 48 && players[playernum].cardsonhand[cardchoose].value >= 0)
	{
		if(players[playernum-1].location == players[playernum].cardsonhand[cardchoose].value)
		{
			cout << "Card matches current city." << endl;
			cout << "1. Charter Flight" << endl;
			cout << "2. Build a research station" << endl;
			int choice = 0;
			cout << "Selection: ";
			cin >> choice;
			cout << string(10, '\n');

			if(choice == 1)
			{
			cout << "Charter Flight!   Choose your new location: ";
			int newlocation;
			cin >>newlocation;

			players[playernum-1].location = newlocation;
			players[playernum].cardsonhand[cardchoose].value = -1;
			cout << endl << "You have moved to : " << cities[newlocation].cityName << endl << endl;
			}

			if(choice ==2)
			{
			if(cities[players[playernum].cardsonhand[cardchoose].value].researchcenter == true)
			{
				cout << "This city already has a research center!" << endl << endl;
				setActionsLeft(playernum-1, 1);
			}
			if(cities[players[playernum].cardsonhand[cardchoose].value].researchcenter == false)
			{
			addResearchCenter(players[playernum].cardsonhand[cardchoose].value);
			cout << "A Research Center has been constructed in " << cities[players[playernum].cardsonhand[cardchoose].value].cityName;
			players[playernum].cardsonhand[cardchoose].value = -1;
			cout << string(5, '\n');
			}


			}

		}
		else
		{
		cout << "City Card chosen, you have been moved to: " << players[playernum].cardsonhand[cardchoose].cardDescription << endl;
		players[playernum-1].location = players[playernum].cardsonhand[cardchoose].value;
		players[playernum].cardsonhand[cardchoose].value = -1;
		cout << endl << endl;
		}
	}

}

void PandModel::ShuttleFlight(int playernum)
{
	int z = 0; //Stays 0 if no Research centers found
	cout << "Cities with research centers:" << endl;
	for(int i = 0; i < 48; i++)
	{
		if(cities[i].researchcenter == true)
		{
			cout << '#' << i << "	" << cities[i].cityName << endl;
			z = 1;
		}
	}


	if(cities[players[playernum-1].location].researchcenter == true) //If current city has researchcenter
	{

	if(z == 1)
	{
	cout << endl << endl << "Please choose a location: ";
	int choice;
	int x = 0;

	while(x != 1) //Until player chooses valid location
	{
	cin >> choice;
	if(cities[choice].researchcenter == true && (players[playernum-1].location != choice) )
		{
		players[playernum-1].location = choice;
		x = 1;}
	if(x == 0)
	{cout << "Invalid Choice!" << endl;}
	}
	}
	}

	if(cities[players[playernum-1].location].researchcenter == false)
	{
		cout << "You can only use Shuttle Flight when you're on a city with a Research Center!" << endl;
		cout << endl;

		setActionsLeft(playernum, 1); //Returns action

	}



}


///////////////////END COMMENT///////////////////////////////////////////////

void RandomizeCubes()//<------------needs to be a member function
{
     // Randomizing the cubes. 
     // Something we'll need??
}

void PandModel::setPlayerRole(int playernum, int profession, std::string pName){
	players[playernum].profession = profession;
	players[playernum].profName = pName;

}

void PandModel::performRoleActions(int playernum, int actionNo, int loc){
	int temp;
	temp = players[playernum].profession;

	if ((temp == 0) & (actionNo)){ //Will come back here

	}

}

playerCard PandModel::drawPlayerCard()
{
	playerCard temp;
	temp = PlayerDeckD.front();//from the top
	PlayerDeckD.pop_front();//remove top card
	return temp; 
}

infectionCard PandModel::drawInfectionCard()//will draw from the top of the deck
{
	infectionCard temp;
	temp = infectionDeck.front();//from the top
	discardInfectionDeck.push_back(temp);//add to discarded cards deck
	infectionDeck.pop_front();//remove top card
	return temp;  
}

void PandModel::discardPlayCard(playerCard discarding)
{
	discardPlayerDeckD.push_back(discarding);
}


void PandModel::setOutbreakLevel()//stub
{
			//std::cout<<"Outbreak Level Increases \n";
}

void PandModel::outbreak(int cityNum)//stub
{
	city temp = getCityInfo(cityNum);

	//std::cout<<"Outbreak will infect neighboring cities with current city color infection \n";
	//when outbreak occurs. move outbreak marker forward 1 space.(increase outbreak level by 1)
	outbreakLevel++;
	char cubeColor = temp.cityColor;
	//0,1,2,3 = red,black,blue,yellow
	int infectIndex;
	if(cubeColor == 'R') infectIndex = 0;
	else if(cubeColor == 'G') infectIndex = 1;
	else if(cubeColor == 'B') infectIndex = 2;
	else if(cubeColor == 'Y') infectIndex = 3;
	//Then place 1 disease cube of the same color on every city connected to that city where outbreak originates.
	int i = 0;
	while(cities[cityNum].adjacentCities[i] != -1)
	{
		//infect cities with cubes of city colors
		//if neighbor has 3 already, do not add 4th
		//instead of adding 4th, a chain reaction outbreak occurs after current outbreak is complete
		if(cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] < 3)
			cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex]++;//increase disease cube count by 1 at neighbors
		else if (cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] == 3)
			//cause a chain reaction outbreak
			outbreakLevel++;//when chain reaction outbreak occurs, move outbreak marker by 1(increase outbreak level by 1)
			//(phat)do I want to do a recursive call?
		i++;
	
	
	
	//Then place 1 disease cube of the same color on every city connected to that city where outbreak originates.
		//(phat)found city with 3 cubes, infect neighbors if not already infected. Check through array
	//except do not add to cities that have already had an outbreak or chain outbreak.
		//(phat)keep track of cities that have already been infected maybe with an array of already infected cities.
	//cities can have up to 3 diseasce cubes of each color.
	}
}

void PandModel::Load(int loadf){
	string temp;
	int tempint;
	fstream savef;
	int playernum;
	int dcubes[4];
	loadflag = true;

	if (loadf == 1){savef.open("Save#1.txt");}
	if (loadf == 2){savef.open("Save#2.txt");}
	if (loadf == 3){savef.open("Save#3.txt");}
	if (loadf == 4){savef.open("Save#4.txt");}
	if (loadf == 5){savef.open("Save#5.txt");}
	if (loadf == 6){savef.open("Save#6.txt");}


	savef >> temp; //"Turns:";
	savef >> temp;
	tempint = atoi(temp.c_str());
	playerturn = tempint;
	savef >> temp;// "NumberOfPlayers:";
	savef >> temp; 
	playernum = atoi(temp.c_str());
	setnumberOfPlayers(playernum);
	savef >> temp; // "PlayerNames:";
	for (int i = 0; i < playernum; i++){
		savef >> temp; 
		setPlayerName(i,temp);
	}
	savef >> temp; // "PlayerRoles:";
	for (int i = 0; i < playernum; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		string rolenames[7] = { "Contingency Plan", "Dispatcher", "Medic", "Operations Expert", "Quarantine Specialist", "Researcher", "Scientist" }; //RoleNames
		setPlayerRole(i, tempint, rolenames[tempint]);
	}
	savef >> temp;// "PlayerLocations:";
	for (int i = 0; i < playernum; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		loadPlayerLocation(i, tempint);
	}

	savef >> temp;// "ActionsLeft:";
	for (int i = 0; i < playernum; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		loadActionsLeft(i,tempint);
	}
	savef >> temp; // "CityProperties:";
	for (int i = 0; i < 48; i++){
		savef >> temp; // getCityColor(i);
		loadCityColor(i, temp[0]);
		savef >> temp; //getRCenter(i);
		tempint = atoi(temp.c_str());
		loadRcenter(i, tempint);
		savef >> temp; // getDiseaseCubes(i, 0);
		dcubes[0] = atoi(temp.c_str());
		savef >> temp; // getDiseaseCubes(i, 0);
		dcubes[1] = atoi(temp.c_str());
		savef >> temp; // getDiseaseCubes(i, 0);
		dcubes[2] = atoi(temp.c_str());
		savef >> temp; // getDiseaseCubes(i, 0);
		dcubes[3] = atoi(temp.c_str());
		setDiseaseCubes(i, dcubes[0], dcubes[1], dcubes[2], dcubes[3]);

	}
	savef >> temp; // "PandModelVariables:";
	savef >> temp;
	tempint = atoi(temp.c_str());
	loadoutbreakLevel(tempint);
	savef >> temp;
	tempint = atoi(temp.c_str());
	loadinfectionRate(tempint);
	savef >> temp;
	dcubes[0] = atoi(temp.c_str());
	savef >> temp;
	dcubes[1] = atoi(temp.c_str());
	savef >> temp;
	dcubes[2] = atoi(temp.c_str());
	savef >> temp;
	dcubes[3] = atoi(temp.c_str());
	loadDCLeft(dcubes[0], dcubes[1], dcubes[2], dcubes[3]);
	savef.close();


}

void PandModel::Save(int savefile , string sfname, int turn){
	int counter = 0 , strc = 1, strbeg=0;
	string str;
	string contents="";
	fstream savef;
	bool begfound=false;
	if (savefile == 1){
		std::ofstream("Save#1.txt", std::ios::out).close();
		savef.open("Save#1.txt");
	}
	if (savefile == 2){
		std::ofstream("Save#2.txt", std::ios::out).close();
		savef.open("Save#2.txt");
	}
	if (savefile == 3){
		std::ofstream("Save#3.txt", std::ios::out).close();
		savef.open("Save#3.txt");
	}
	if (savefile == 4){
		std::ofstream("Save#4.txt", std::ios::out).close();
		savef.open("Save#4.txt");
	}
	if (savefile == 5){
		std::ofstream("Save#5.txt", std::ios::out).close();
		savef.open("Save#5.txt");
	}
	if (savefile == 6){
		std::ofstream("Save#6.txt", std::ios::out).close();
		savef.open("Save#6.txt");
	}
		savef << "Turn:";
		savef << " ";
		savef << turn;
		savef << " ";
		savef << "NumberOfPlayers:";
		savef << " ";
		savef << getnumberOfPlayers();
		savef << " ";
		savef << "PlayerNames:";
		savef << " ";
		for (int i = 0; i < getnumberOfPlayers(); i++){
			savef << getPlayerName(i);
			savef << " ";
		}
		savef << "PlayerRoles:";
		savef << " ";
		for (int i = 0; i < getnumberOfPlayers(); i++){
			savef << getPlayerRole(i);
			savef << " ";
		}
		savef << "PlayerLocations:";
		savef << " ";
		for (int i = 0; i < getnumberOfPlayers(); i++){
			savef << getPlayerLocation(i);
			savef << " ";
		}
		savef << "ActionsLeft:";
		savef << " ";
		for (int i = 0; i < getnumberOfPlayers(); i++){
			savef << getActionsLeft(i);
			savef << " ";
		}
		savef << "CityProperties:";
		savef << " ";
		for (int i = 0; i < 48; i++){
			savef << getCityColor(i);
			savef << " ";
			savef << getRCenter(i);
			savef << " ";
			savef << getDiseaseCubes(i,0);
			savef << " ";
			savef << getDiseaseCubes(i,1);
			savef << " ";
			savef << getDiseaseCubes(i, 2);
			savef << " ";
			savef << getDiseaseCubes(i, 3);
			savef << " ";

		}
		savef << "PandModelVariables:";
		savef << " ";
		savef << getoutbreakLevel();
		savef << " ";
		savef << getInfectionRate();
		savef << " ";
		savef << getDCLeft(0);
		savef << " ";
		savef << getDCLeft(1);
		savef << " ";
		savef << getDCLeft(2);
		savef << " ";
		savef << getDCLeft(3);

		savef.close();
		
		fstream mainf("SaveMain.txt");
		while (mainf >> str){
			contents.append(str);
			contents.append(" ");
		}
		mainf.close();
		std::ofstream("SaveMain.txt", std::ios::out).close();
		for (int i = 0; i < contents.length(); i++){
			if (contents[i] == '#'){ counter++; }
			strc++;
			if ((counter == savefile) && !begfound){ strbeg = i+1; begfound = true; }
			if (counter == savefile +1){ strc = strc - 3;  goto out; }
	
		}
	out:
		string ref;
		ref.append(" Used ");
		ref.append(sfname);
		ref.append(" ");
		/*cout << contents << std::endl;
		cout << ref << std::endl;
		cout << strbeg;
		cout << strc;*/


		contents.replace(strbeg, strc-strbeg, ref);
		mainf.open("SaveMain.txt");
		mainf << contents;
		mainf.close();
		Update();
		//cin >> ref;                     //debug

	

}

void PandModel::shuffleInfectionDeck(deque<infectionCard> &shuffleDeck)//passing by reference since I need to modify it directly
{
	int cardAmount = shuffleDeck.size();
	deque<infectionCard> tempDeck;
	for(int p = 0; p<cardAmount; p++)//transfer cards from original deck to tempDeck
		tempDeck.push_back(shuffleDeck[p]);
	for(int p = 0; p<cardAmount; p++)//empty deck and repopulate with shuffled cards
		shuffleDeck.pop_front();
	 //shuffled infection deck ////////may turn this into a function in model.h void shuffledeck(int array[], maxnum);
        int* shuffleInfection = new int[cardAmount];//array of random num 1 - decksize()
        const int infectionMax = cardAmount;
        {
                srand(time(NULL));
                for(int i = 0; i<cardAmount;i++)
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
		for(int p = 0; p<cardAmount; p++)
		shuffleDeck.push_back(tempDeck[shuffleInfection[p]]);//repopulating deck
}

void PandModel::shufflePlayerDeck(deque<playerCard> & shuffleDeck)
{
	int cardAmount = shuffleDeck.size();
	deque<playerCard> tempDeck;
	for(int p = 0; p<cardAmount; p++)//transfer cards from original deck to tempDeck
		tempDeck.push_back(shuffleDeck[p]);
	for(int p = 0; p<cardAmount; p++)//empty deck and repopulate with shuffled cards
		shuffleDeck.pop_front();
	 //shuffled infection deck ////////may turn this into a function in model.h void shuffledeck(int array[], maxnum);
        int* shufflePlayer = new int[cardAmount];//array of random num 1 - decksize()
        const int playerMax = cardAmount;
        {
                srand(time(NULL));
                for(int i = 0; i<cardAmount;i++)
                {
                        bool taken;
                        int playercardnum;
                        do
                        {
                                playercardnum = rand()%playerMax;
                                taken = true;
                                for(int j = 0; j<i; j++)
                                        if(playercardnum == shufflePlayer[j])
                                        {
                                                taken = false;
                                                break;
                                        }
                        }while(!taken);
                        shufflePlayer[i] = playercardnum;
                }
        }///////////////////////////////////////////////////////////////////////////////
		for(int p = 0; p<cardAmount; p++)
		shuffleDeck.push_back(tempDeck[shufflePlayer[p]]);//repopulating deck
}


void GameOver()//<------------needs to be a member function
{
	/* I will add test cases to check for the end of the game:
	   1. if all four diseases are cured = win
	   2. if outbreaks reach all the way to the end = lose
	   3. if unable to place number of disease cubes needed on the board = lose
	   4. if a player cannot draw two player cards after doing his actions = lose
	*/
};

#endif

