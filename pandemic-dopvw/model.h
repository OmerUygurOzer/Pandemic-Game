#ifndef MODEL_H
#define MODEL_H
#include <string>
#include <deque>
#include <time.h>
#include <fstream>
#include <iomanip>



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
	int value;
	
};

struct playerCard
{
	int value; //Holds the card's number
	string cardType;
	string cardDescription;
	char color;
	bool remove;
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
	string playerName;
	int profession; //Player's profession will be designated by a value. Something else will transfer the value to
	//the data holding all of the professions and all of their effects
	std::string profName; //The name of their profession
	int location; //This will be the ID number of the city the character is currently located.
	


	playerCard cardsonhand[9]; //Player can hold 7 cards   --Upped to 9. --Vu
	int numOfCards;
	//playerCard CPextracard; //Extra card for the contigency planner   --Working on a workaround  --Vu
	bool extracardFlag;// = false; //whether a card is chosen already or not
	playerCard extracard;

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
	std::deque<playerCard> discardedEventCards;
	int diseaseCubes[4]; // number of disease cubes left for each color, (0,1,2,3 = red,black,blue,yellow)
	int outbreakLevel;//0-8, if 8 game is over?
	int trackOutbreak;//used for outbreak infected list
	int infectionRate;//not sure why this was removed before. Will need to reimplement to match board rate level/ ex: 2-2-2-3-3-4-4 maybe stack<int> infectionRate; populate in constructor and use increaseInfectRate();
	int infectRateArray[7]; //represents the infection rate  2-2-2-3-3-4-4
	int ForecastPlayed;
	bool QuietNightPlayed;//changed to bool. by default false
	bool ResilientPlayed;//changed to bool. by default false
	
	int numResearchCenters;
	
	// game win/lose variables
	bool gameWin;
	bool gameLose;
	bool cureMarkers[4]; //color of the cure (0,1,2,3 = (R)red,(G)black,(B)blue,(Y)yellow)
	bool outOfCubes;
	bool outOfCards;
	bool outbreakTooHigh;
	bool allCures;

	//SAVE-LOAD VARIABLES////////////////////////////
	string availability[6]; //availabilty of the files
	string gameName[6];
	int numberOfPlayers;
	int playerturn;
	bool loadflag;
	infectionCard SL_IC[48]; //Added by Omer for Save/Load Functions. Doesn't change the already implemented algorithm
	/////////////////////////////////////////////////

	////outbreak tracker for chain outbreak
	std::deque<city> trackInfect;//every city infected will be tracked. Could return this into main and use view to display
public:
	PandModel();
	//getters
	city getCityInfo(int citynum) {return cities[citynum];}//maybe seperate into getcityname, getadjcities, getcubes...etc
	string getCityName(int citynum) {return cities[citynum].cityName;}
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
	int getInfectionRate(){return infectRateArray[infectionRate];}//for view to access/display infection rate
	int getPlayerRole(int playerNo){ return players[playerNo].profession; } //returns the player role
	int getNumPlayCardsLeft(){return PlayerDeckD.size();}//

	Playerchar getPlayerInfo(int playernum){return players[playernum];}
	deque<infectionCard> copyInfectDiscardDeck(){return discardInfectionDeck;}//for view
	void removeDiscardInfect(int index);//resilient population
	int getDCLeft(int a);//Disease cubes left
	int getTurn();
	bool getloadflag(){ return loadflag; };//Whether the game is being loaded or starting as a new game
	void setloadflag(int x){ loadflag = x; };
	int colorToInt(char color); // returns int corresponding to color (0,1,2,3 = R,G,B,Y)
	void epidemicDrawn(); // call when an epidemic card is drawn
	bool GameOver();

	//event cards
	void setForecastPlayed(int value){ForecastPlayed = value;}
	void setQuietNightPlayed(bool value){QuietNightPlayed = value;}
	void setResilientPlayed(bool value){ResilientPlayed = value;}
	int ReturnForecast(){return ForecastPlayed;}
	bool ReturnQuietNight(){return QuietNightPlayed;}
	bool returnResilient(){return ResilientPlayed;}
	//game over funcs
	bool returnGamewin(){return gameWin;}
	bool returnGamelose(){return gameLose;}
	bool retoutOfCubes(){return outOfCubes;}
	bool retoutOfCards(){return outOfCards;}
	bool retoutbreakTooHigh(){return outbreakTooHigh;}
	bool retallCures(){return allCures;}
	
	playerCard drawPlayerCard();//will draw from playerDeckD and return card on top of deck+
	playerCard getPlayerCard(int num){return playerDeck[num];}//used for testing
	infectionCard drawInfectionCard();//will draw from top of infection deck
	void placeInfectionCard(infectionCard temp); //Place a card on top of infection deck
	infectionCard drawBottomInfectionCard();  // will draw from bottom of infection deck
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
	void addDiseaseCubes(int cityNum, char cubeColr);//Add cube(s) of a corresponding color to city
	void ShuttleFlight(int playernum);
	void setActionsLeft(int playernum, int addAction); //adds # of actions for a player
	int getActionsLeft (int playernum) {return players[playernum].ActionsLeft;}
	
	void addResearchCenter(int city){cities[city].researchcenter=true;}//build research center at current city. Will need a check to see if research center already exists
	void removeResearchCenter(int city){cities[city].researchcenter=false;}//remove a research center
	void buildResearchCenter(int playernum); //Operations Expert ability

	void shuffleInfectionDeck(deque<infectionCard> &shuffleDeck);//shuffle infection deck pass in a deque<infectionCard>
	void shufflePlayerDeck(deque<playerCard> & shuffleDeck);//shuffle player deck pass in a deque<playerCard>
	void mergeInfectionDecks(deque<infectionCard> &deckA, deque<infectionCard> &deckB); // puts deckA on top of deckB
	void outbreak(int city);
	void chainOutbreak(int cityNum, char color);
	bool researchCure(int playerNum);
	void treatCity(int city, int cubecolor, int role); // treat city for disease corresponding to cubecolor
	//Role action:
	void performRoleActions(int playernum, int actionNo , int loc); //Performs unique player actions
	void pickEvent(int playernum);

	void PlayCard(int playernum);
	void PlayEventCard(int playernum, playerCard eventcard);
	int CheckHand(int playernum) {	//If player has non-blank card, return 1
		int z = 0;
		for(int i = 0; i < 9; i++)
		{if(players[playernum].cardsonhand[i].value != -1)
		{z = 1;}
		}
		return z;
	}
	void ReceiveCard(int playernum, playerCard card);
	void discardCard(int playernum, playerCard card);
	int cardcount(int playernum)
	{
		players[playernum].numOfCards = 0;
		for(int i = 0; i < 9; i++)
			{
			if(players[playernum].cardsonhand[i].value != -1){
				players[playernum].numOfCards++;}
			}
		return players[playernum].numOfCards;}
	void ShareKnowledge(int playernum, int numofplayers);
	int countNumResearchCenters();
	void abilityCharterFlight(int playernum);

	void cleanHand(int playernum); //Cleans up the player's hand
	void handOverdraw(int playernum);

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
	void assignRoles();
	void updateHandsFile(int playernum);
};

PandModel::PandModel()//constructor
{
	cureMarkers[0] = false;
	cureMarkers[1] = false;
	cureMarkers[2] = false;
	cureMarkers[3] = false;
	outbreakLevel = 0;
	trackOutbreak = 0;
	infectionRate = 0;
	infectRateArray[0] = 2;
	infectRateArray[1] = 2;
	infectRateArray[2] = 2;
	infectRateArray[3] = 3;
	infectRateArray[4] = 3;
	infectRateArray[5] = 4;
	infectRateArray[6] = 4;
	ForecastPlayed = 0;
	QuietNightPlayed = false;
	ResilientPlayed = false;
	gameLose = false;
	gameWin = false;
	outOfCubes = false;
	outOfCards = false;
	outbreakTooHigh = false;
	allCures = false;
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

	 std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "HoChiMinh City",
                            "Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
                            "Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
                            "Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};

	 for(int i = 0; i<4; i++){ // have 24 disease cubes of each color at start of game
		 diseaseCubes[i] = 24;
	 }

	 for(int i = 0; i < 9; i++) //Empty player hand initialize    -Vu
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
		 SL_IC[i].cardType = "City";//Added by Omer for Save/Load Functions. Doesn't change the already implemented algorithm
		 infectCard.cardDescription = cityname[i];
		 SL_IC[i].cardDescription = cityname[i];
		 infectCard.city = i;
		 SL_IC[i].city = i;
		 infectCard.color = colorToInt(citycolors[i]);// set infection card color
		 SL_IC[i].color = colorToInt(citycolors[i]);
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
		 playerDeck[i].value = i;
	 }
	 ////////////////////////////////////////////////Special Event Cards for player deck
	 playerDeck[54].cardType = "Special Event";
	 playerDeck[54].cardDescription = "Airlift: Move a pawn ( yours or another player's) to any city. You must have a player's permission to move their pawn \n";
	 playerDeck[54].value = 54;

	 playerDeck[55].cardType = "Special Event";
	 playerDeck[55].cardDescription = "Forecast: Examine the top 6 cards of the Infection Draw Pile, rearrange them in the order of your choice, then place them back on the pile. \n";
	 playerDeck[55].value = 55;

	 playerDeck[56].cardType = "Special Event";
	 playerDeck[56].cardDescription = "Government Grant: Add a Research Station to any city for free \n";
	 playerDeck[56].value = 56;

	 playerDeck[57].cardType = "Special Event";
	 playerDeck[57].cardDescription = "One Quiet Night: The next player to begin the Playing the Infector phase of their turn may skip that phase entirely \n";
	 playerDeck[57].value = 57;

	 playerDeck[58].cardType = "Special Event";
	 playerDeck[58].cardDescription = "Resilient Population: Take a card from the Infection Discard Pile and remove it from the game \n";
	 playerDeck[58].value = 58;

	 for(int i = 0; i < 59; i++)
		 PlayerDeckD.push_back(playerDeck[i]);
	 shufflePlayerDeck(PlayerDeckD);

	 //initialize map
	 for(int i = 0; i < 48; i++)
	{
		cities[i].cityName = cityname[i];
		cities[i].cityColor = citycolors[i];
		cities[i].researchcenter = 0;
		for(int j = 0; j < 4; j++)
			cities[i].diseasecubes[j] = 0;//initialize cube count to 0
		cities[i].value = i;
	}


	 // ** Place starting infection cubes **
	for(int i = 3; i > 0; i--){
		infectionCard current;
		for(int f = 0; f < 3; f++){
			current = drawInfectionCard();  // Draw next card in infection deck
			cities[current.city].diseasecubes[current.color] = i;  // place i cubes of color and city matching drawn card
			diseaseCubes[current.color] = diseaseCubes[current.color] - i;  // remove the disease cubes from remaining
		}
	}


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

		players[0].extracardFlag = 0;
		players[1].extracardFlag = 0;
		players[2].extracardFlag = 0;
		players[3].extracardFlag = 0;

		
		addResearchCenter(1);//Atlanta CDC research center default
}

int PandModel::colorToInt(char color) // returns int corresponding to color (0,1,2,3 = R,G,B,Y)
{
	if(color == 'R')
		return 0;
	if(color == 'G')
		return 1;
	if(color == 'B')
		return 2;
	if(color == 'Y')
		return 3;
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

void PandModel::assignRoles(){
	// ROLES ARE ASSIGNED RANDOMLY /////////////////////////////////////////

	char roles[7] = { 'a', 'a', 'a', 'a', 'a', 'a', 'a' };   //To keep a track of roles that are still available
	string rolenames[7] = { "Contingency Plan", "Dispatcher", "Medic", "Operations Expert", "Quarantine Specialist", "Researcher", "Scientist" }; //RoleNames

	for (int i = 0; i < numberOfPlayers; i++)
	{
		srand(time(NULL));
		bool taken = false;
		while (taken == false){ //Player roles are set(randomly)
			int p = rand() % 7;
			if (!(roles[p] == 't')){
				setPlayerRole(i, p, rolenames[p]);
				roles[p] = 't';
				taken = true;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////
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
	players[playernum].location = location;
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


void PandModel::ReceiveCard(int playernum, playerCard card)
{
//	cout << "RECEIVE DEBUG: YOU ARE PLAYER #:" << playernum << endl;

	for(int i = 0; i < 9; i++)
	{
		if(players[playernum].cardsonhand[i].value == -1)
		{
			players[playernum].cardsonhand[i]= card;
			
			i = 10; //If card placed into hand, end loop
		}
		
	}
	handOverdraw(playernum);
}

void PandModel::pickEvent(int playernum){
	if (!players[playernum].extracardFlag){
		if (discardedEventCards.size() == 0){
			cout << "No Event Card was has been played yet!" << endl;
			players[playernum].ActionsLeft = players[playernum].ActionsLeft + 1;
		}
		else{
			cout << "List of discarded cards:" << endl << endl;
			for (int i = 0; i < discardedEventCards.size(); i++){
				cout << i + 1 << ")" << discardedEventCards[i].cardDescription << endl;
			}
		}
		int temp;
		cout << "Which event card would you like to pick:";
		cin >> temp;
		cout << endl;
		while (temp<1 && temp > discardedEventCards.size() ){
			cout << "Invalid Input. Try again:";
			cin >> temp;
			cout << endl;
		}
		cout << "TEST:" << discardedEventCards[temp - 1].value << endl;
		players[playernum].extracard = playerDeck[discardedEventCards[temp - 1].value];
		discardedEventCards.erase(discardedEventCards.begin() + temp - 1);
		players[playernum].extracardFlag = true;
		players[playernum].ActionsLeft = players[playernum].ActionsLeft + 1;
	}
	else{
		cout <<  "You already have an extra card!" << endl;
		players[playernum].ActionsLeft = players[playernum].ActionsLeft + 1;

	}


}

void PandModel::PlayCard(int playernum)
{
	//Print cards in hand/////////////////////////////////////////
	cout << "Cards on hand:" << endl;
	//cout << "Color || Type || Name - Effect" << endl;
	int temp;
	bool skipped = false;
	for(int i = 0; i < 9; i++)
	{
		
		if(players[playernum].cardsonhand[i].value != -1)
		{
			temp = i;
			cout << "#" << i+1 << "    ";
			cout << players[playernum].cardsonhand[i].color << " || ";
			cout << players[playernum].cardsonhand[i].cardType << " || ";
			cout << players[playernum].cardsonhand[i].cardDescription << endl;

		}
	}
	temp++; temp++; //this isn't a bug

	if (players[playernum].extracardFlag){//Added by omer for contingency planner

		cout << "Your Extra Card:" << endl;

		cout << "#" << temp << "    ";
		cout << players[playernum].extracard.color << " || ";
		cout << players[playernum].extracard.cardType << " || ";
		cout << players[playernum].extracard.cardDescription << endl;
	}
	////////////////Hand print end////////////////////////////////

	int cardchoose;
	cout << "Choose your card: ";
	cin >> cardchoose;

	while(cardchoose < 0 || cardchoose > 9)//had to chang it for contigency planner
	{
		cout << "Invalid choice! Please choose again: ";
		cin >> cardchoose;
	}
	cout << endl << endl;

	if (cardchoose == temp){ 
		skipped = true;
		goto extra; }

	cardchoose = cardchoose - 1; //Player displays cards as 1 to 7. If select 1, we need to access deck[0]



	if(players[playernum].cardsonhand[cardchoose].value < 48 && players[playernum].cardsonhand[cardchoose].value >= 0)
	{
		if(players[playernum].location == players[playernum].cardsonhand[cardchoose].value)
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

			players[playernum].location = newlocation;
			discardPlayCard(players[playernum].cardsonhand[cardchoose]);
			players[playernum].cardsonhand[cardchoose].value = -1;
			cout << endl << "You have moved to : " << cities[newlocation].cityName << endl << endl;
			}

			if(choice ==2)
			{
			if(cities[players[playernum].cardsonhand[cardchoose].value].researchcenter == true)
			{
				cout << "This city already has a research center!" << endl << endl;
				setActionsLeft(playernum, 1);
				system("pause");
			}
			if(cities[players[playernum].cardsonhand[cardchoose].value].researchcenter == false)
			{
			buildResearchCenter(playernum);
		//	addResearchCenter(players[playernum].cardsonhand[cardchoose].value);
		//	cout << "A Research Center has been constructed in " << cities[players[playernum].cardsonhand[cardchoose].value].cityName;
			if(cities[players[playernum].location].researchcenter == true)
			{
				discardPlayCard(players[playernum].cardsonhand[cardchoose]);
				players[playernum].cardsonhand[cardchoose].value = -1;
			}
			cout << string(5, '\n');
			}


			}

		}
		else
		{
		cout << "City Card chosen, you have been moved to: " << players[playernum].cardsonhand[cardchoose].cardDescription << endl;
		players[playernum].location = players[playernum].cardsonhand[cardchoose].value;
		discardPlayCard(players[playernum].cardsonhand[cardchoose]);
		players[playernum].cardsonhand[cardchoose].value = -1;
		cout << endl << endl;
		}
	}

	int cardchosenvalue;
	cardchosenvalue = players[playernum].cardsonhand[cardchoose].value; //I should've did this sooner -Vu

	//if EVENT CARD
	if(cardchosenvalue >=54 && cardchosenvalue <= 58)
	{
		setActionsLeft(playernum, 1); //Event card takes up no turns
		cout << "Playing an event card: ";
		PlayEventCard(playernum, players[playernum].cardsonhand[cardchoose]);
	}

extra:
	if (skipped){
		setActionsLeft(playernum, 1); //Event card takes up no turns
		cout << "Playing an event card: ";
		PlayEventCard(playernum, playerDeck[players[playernum].extracard.value]);
		players[playernum].extracardFlag = false;
	}
}

void PandModel::PlayEventCard(int playernum, playerCard eventcard)
{
	int cardchosenvalue = eventcard.value;
	int wascardused = 0;

	//AIRLIFT
	if(cardchosenvalue == 54)
		{
			cout << "Event Played: Airlift!" << endl << endl;
		////AirLift Data Output////
		for(int i = 0; i < 16; i++)
		    {
                cout << left << setw(3) << i    << "  " << setw(20) << cities[i].cityName;
                cout << left << setw(3) << i+16 << "  " << setw(20) << cities[i+16].cityName;
                cout << left << setw(3) << i+32 << "  " << setw(20) << cities[i+32].cityName << endl;
			}
		cout << "Player locations:" << endl;
		for(int i = 0; i < numberOfPlayers; i++)
			{cout << i << "  " << players[i].playerName << " : " << cities[players[i].location].cityName << endl;}


			int chooseplayer;
			int chooselocation;
			cout << "Who would you like to move? (0-4) : ";
			cin >> chooseplayer;
			cout << endl << "Where would you like to move " << players[chooseplayer].playerName << "? (0-47):";
			cin >> chooselocation;
			players[chooseplayer].location = chooselocation;
			cout << players[chooseplayer].playerName << " has been moved to";
			cout << cities[players[chooseplayer].location].cityName << endl << endl;

			wascardused = 1;
			cout << endl << endl;			
		}
	//FORECAST//////////
	if(cardchosenvalue == 55)
		{
			cout << "Event card played: Forecast!" << endl;
			setForecastPlayed(1); //Forecast has to be played in controller.cpp, this flag plays it
			wascardused = 1;
		}

	//GOVERNMENT GRANT//
	if(cardchosenvalue == 56)
		{
			cout << "Event card played: Government Grant!" << endl << endl;
			cout << "Listing Cities in regard to possession of Research Stations..." << endl;
			for(int i = 0; i < 16; i++)
			 {
                cout << left << setw(2) << i    << "  " << setw(16) << cities[i].cityName;
				if(returnResearch(i) == 1){ cout << setw(5) << ":Yes";}
				else {cout << setw(5) << ":No";}

                cout << left << setw(3) << i+16 << "  " << setw(16) << cities[i+16].cityName;
				if(returnResearch(i+16) == 1){cout << setw(5) << ":Yes";}
				else {cout << setw(5) << ":No";}

                cout << left << setw(3) << i+32 << "  " << setw(16) << cities[i+32].cityName;
				if(returnResearch(i+32) == 1){ cout << setw(5) << ":Yes" << endl;}
				else {cout << setw(5) << ":No" << endl;}
			}
		int citychosen;
		cout << "Choose a city (0-47): ";
		cin >> citychosen;

		if(cities[citychosen].researchcenter == true)
			{
				cout << "This city already has a research center!" << endl << endl;
				setActionsLeft(playernum, 1);
			}

		if(cities[citychosen].researchcenter == false)
			{
				int decideRemove = 0;
				if( countNumResearchCenters() == 6)
				{
				cout << "Hit max limit of Research Centers!" << endl;
				cout << "Remove another Research Center?" << endl;
				cout << "1. Yes" << endl << "2. No" << endl;
				cin >> decideRemove;
				}

			if(decideRemove == 1)
			{
				cout << "Choose a city to remove a Research Center (0-47)" << endl;
				int removedyet = 0;
				int choosecity;
				while(removedyet = 0)
				{
					cin >> choosecity;
					if(choosecity >= 0 && choosecity <= 47) //In case the player puts in a bad number
					{
						if(cities[choosecity].researchcenter == true)
						{
							removeResearchCenter(choosecity);
							removedyet = 1;
						}
						if(cities[choosecity].researchcenter == false)
						{cout << "This city does not have a research center" << endl;}
					}

				}
			}

			if(decideRemove != 2){
				addResearchCenter(citychosen);
				wascardused = 1;
				cout << "A Research Center has been constructed in " << cities[citychosen].cityName;
				cout << string(5, '\n');
				}
			}
		}
	//ONE QUIET NIGHT///////////////////////////// --Needs work
	if(cardchosenvalue == 57)
		{
			cout << "Event card played: One Quiet Night!" << endl;
			setQuietNightPlayed(true);
			cout << "The next Infection Phase will be skipped!" << endl;
			//cout << "Card not implemented yet! Discarding card." << endl << endl;
			wascardused = 1;
		}
	//RESILIENT POPULATION/////////////////////  --Draw infection card, never play or push it
	if(cardchosenvalue == 58)
		{
			cout << "Event card played: Resilient Population!" << endl;
			setResilientPlayed(true);
			
			//cout << "Card not implemented yet! Discarding card." << endl << endl;
			wascardused = 1;
		}
	//Discard Event Card if Used/////
	if(wascardused == 1){discardCard(playernum, eventcard);}
}

void PandModel::discardCard(int playernum, playerCard card)
{
	for(int i = 0; i < 9; i++){
		if(card.value == players[playernum].cardsonhand[i].value)
			{
			discardPlayCard(card);
			if (card.cardType == "Special Event"){ discardedEventCards.push_back(card); }//Added by Omer for Contigency Planner
			players[playernum].cardsonhand[i].value = -1;
			}
	}
}

void PandModel::handOverdraw(int playernum)
{
	int numcards;
	numcards = cardcount(playernum);
//	cout << "DEBUG handOverdraw numcards : PLAYER:" << playernum << " # CARDS IN HAND: "<< numcards<<endl<<endl;
	while(numcards > 7)
	{
		int cardchoose = -1;
		int choice;

		cout << endl << "You have too many cards! - Discard cards or play your event cards" << endl << endl;


			cout << "Cards on hand:" << endl;
			for(int i = 0; i < 9; i++)
			{
				if(players[playernum].cardsonhand[i].value != -1){
					cout << "#" << i+1 << "    ";
					cout << players[playernum].cardsonhand[i].color << " || ";
					cout << players[playernum].cardsonhand[i].cardType << " || ";
					cout << players[playernum].cardsonhand[i].cardDescription << endl;}}
			cout << endl << "Choose a city card to discard it. Choose an event card to play or discard it." << endl;
			cout << "Choose a card (0-8):";

			while(cardchoose < 0 || cardchoose > 9){cin >> cardchoose;}
			cardchoose = cardchoose -1;
			if(players[playernum].cardsonhand[cardchoose].cardType == "City")
			{discardCard(playernum, players[playernum].cardsonhand[cardchoose]);}

			if(players[playernum].cardsonhand[cardchoose].value >= 54 && players[playernum].cardsonhand[cardchoose].value <= 58)
			{
				cout << "1. Play" << endl << "2. Discard" << endl;
				cin >> choice;

				if(choice == 1){PlayEventCard(playernum, players[playernum].cardsonhand[cardchoose]);}
				if(choice == 2){discardCard(playernum, players[playernum].cardsonhand[cardchoose]);}
				choice = 0;
			}
			numcards = cardcount(playernum);
			cleanHand(playernum);
	}

}

void PandModel::cleanHand(int playernum) //Shifts all cards in player's hand to the left and fills empty gaps
{
	playerCard tempdeck[9]; //Holds cleaned up values
	for(int i = 0; i < 9; i++)
	{tempdeck[i].value = -1;} //Initiliaze
	int z = 0;
	for(int i = 0; i < 9; i++)
	{
		if(players[playernum].cardsonhand[i].value != -1)
		{
			tempdeck[z] = players[playernum].cardsonhand[i];
			z = z + 1; //Increase tempdeck counter
		}
	}

	for(int i = 0; i < 9; i++)
	{players[playernum].cardsonhand[i] = tempdeck[i];} //Pass back cleaned hand
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

	if(cities[players[playernum].location].researchcenter == true) //If current city has researchcenter
	{

		if(z == 1){
			cout << endl << endl << "Please choose a location: ";
			int choice;
			int x = 0;

			while(x != 1) //Until player chooses valid location//infinite loop when already in the same city
				{
				cin >> choice;
				if(cities[choice].researchcenter == true && (players[playernum].location != choice) )
					{
					players[playernum].location = choice;
					x = 1;}
				if(players[playernum].location == choice)
					{
						cout << "Cannot move to same location." << endl << endl;
						setActionsLeft(playernum, 1);
						x = 1;
					}
				if(x == 0){cout << "Invalid Choice!" << endl;}
				}
			}
	}

	if(cities[players[playernum].location].researchcenter == false)
	{
		cout << "You can only use Shuttle Flight when you're on a city with a Research Center!" << endl;
		cout << endl;

		setActionsLeft(playernum, 1); //Returns action

	}

}

void PandModel::abilityCharterFlight(int playernum)
{
	cout << "Discard any city card to initiate charter flight:" << endl;

	cout << "Cards on hand:" << endl;
	for(int i = 0; i < 9; i++)
	{
		if(players[playernum].cardsonhand[i].value != -1)
		{
			cout << "#" << i+1 << "    ";
			cout << players[playernum].cardsonhand[i].color << " || ";
			cout << players[playernum].cardsonhand[i].cardType << " || ";
			cout << players[playernum].cardsonhand[i].cardDescription << endl;
		}
	}

	int cardchoose;
	cout << "Choose a city card: ";
	cin >> cardchoose;

	while(cardchoose < 0 || cardchoose > 8 || (players[playernum].cardsonhand[cardchoose-1].value >47) )
	{
		cout << "Invalid choice! Please choose again: ";
		cin >> cardchoose;
	}
	cout << endl << endl;

	cardchoose = cardchoose - 1;

			cout << "Charter Flight!   Choose your new location: ";
			int newlocation;
			cin >>newlocation;

			players[playernum].location = newlocation;
			discardPlayCard(players[playernum].cardsonhand[cardchoose]);
			players[playernum].cardsonhand[cardchoose].value = -1;
			cout << endl << "You have moved to : " << cities[newlocation].cityName << endl << endl;
			
}

void PandModel::ShareKnowledge(int playernum, int numofplayers)
{
	cout << "Sharing Knowledge allows you to give or take a City card from another player" << endl;
	cout << "The card must match the city you are in, and both players must be in the same city" << endl;
	cout << "The Researcher is able to give a city card without it having to match." << endl << endl;

	cout << "Current player locations:" << endl;
	for(int i = 0; i < numofplayers; i++)
	{
		cout << i+1 << "  ";
		getPlayerName(playernum);
		cout << "  ";
		getCityName(players[i].location);
		cout << endl;
	}

	int chooseplayer;
	cout << "Choose a player (1 - " << numofplayers << ") : ";
	cin >> chooseplayer;

	chooseplayer--;

	if(chooseplayer == playernum)
	{
		cout << "You don't need to Share Knowledge with yourself." << endl;
		setActionsLeft(playernum,1);
	}
	else if(players[playernum].location != players[chooseplayer].location)
	{
		cout << "This player is not in the same location as you." << endl;
		setActionsLeft(playernum,1);
	}


	else if(players[playernum].location == players[chooseplayer].location && playernum != chooseplayer)
	{
		cout << "Sharing knowledge with ";
		getPlayerName(chooseplayer);
		cout << endl << "Now displaying both players' cards..." << endl;

			for(int i = 0; i < 9; i++)
			{
				if(players[playernum].cardsonhand[i].value != -1){
					cout << "#" << i+1 << "    ";
					cout << players[playernum].cardsonhand[i].color << " || ";
					cout << players[playernum].cardsonhand[i].cardType << " || ";
					cout << players[playernum].cardsonhand[i].cardDescription << endl;}}
			cout << endl << endl;
			getPlayerName(chooseplayer);
			cout << "'s cards:" << endl;
			for(int i = 0; i < 9; i++)
			{
				if(players[chooseplayer].cardsonhand[i].value != -1){
					cout << "#" << i+1 << "    ";
					cout << players[chooseplayer].cardsonhand[i].color << " || ";
					cout << players[chooseplayer].cardsonhand[i].cardType << " || ";
					cout << players[chooseplayer].cardsonhand[i].cardDescription << endl;}}

			cout << "Give one of your cards or take a card?" << endl;
			cout << "1. Give" << endl << "2. Take" << endl;
			int giveOrTake;
			cin >> giveOrTake;

			int currentplayerrole = getPlayerRole(playernum);
			int chooseplayerrole = getPlayerRole(chooseplayer);


			if(giveOrTake == 1)
				{
				cout << "Choose which card to give (1 - 7) : ";
				int choosecard;
				cin >> choosecard;


				if( (players[playernum].cardsonhand[choosecard].value < 48) && (players[playernum].cardsonhand[choosecard].value >= 0) )
				{
					if(currentplayerrole == 5)
					{
						ReceiveCard(chooseplayer, players[playernum].cardsonhand[choosecard]);
						players[playernum].cardsonhand[choosecard].value = -1;
					}

					if(currentplayerrole != 5)
					{
						if(players[playernum].cardsonhand[choosecard].value != players[playernum].location)
						{
							cout << "This card does not match the current city you are in." << endl;
							setActionsLeft(playernum, 1);
						}

						if(players[playernum].cardsonhand[choosecard].value == players[playernum].location)
						{
							ReceiveCard(chooseplayer, players[playernum].cardsonhand[choosecard]);
							players[playernum].cardsonhand[choosecard].value = -1;
						}
					}
				}

				if(players[playernum].cardsonhand[choosecard].value < 0 || players[playernum].cardsonhand[choosecard].value >= 48)
					{
					cout << "Cannot share event cards!" << endl;
					setActionsLeft(playernum, 1);
					}

					}

				else if(giveOrTake == 2)
				{
					cout << "Choose which card to take (1 - 7) : ";
					int choosecard;
					cin >> choosecard;
					if(players[chooseplayer].cardsonhand[choosecard].value < 48 && players[chooseplayer].cardsonhand[choosecard].value >= 0)
					{
						if(chooseplayerrole == 5)
						{
							ReceiveCard(playernum, players[chooseplayer].cardsonhand[choosecard]);
							players[playernum].cardsonhand[choosecard].value = -1;
						}
						if(chooseplayerrole != 5)
						{
							if(players[chooseplayer].cardsonhand[choosecard].value != players[playernum].location)
							{
								cout << "This card does not match the current city you are in." << endl;
								setActionsLeft(playernum, 1);
							}

							if(players[chooseplayer].cardsonhand[choosecard].value == players[playernum].location)
							{
								ReceiveCard(playernum, players[chooseplayer].cardsonhand[choosecard]);
								players[chooseplayer].cardsonhand[choosecard].value = -1;
							}
						}
					}
					if(players[chooseplayer].cardsonhand[choosecard].value < 0 || players[chooseplayer].cardsonhand[choosecard].value >= 48)
					{
						cout << "Event cards cannot be shared." << endl;
						setActionsLeft(playernum, 1);
					}
				cleanHand(playernum);
				cleanHand(chooseplayer);
			}
			else
			{
				cout << "Invalid Input." << endl;
				setActionsLeft(playernum, 1);
			}

	}


}

int PandModel::countNumResearchCenters(){
	numResearchCenters = 0;
	for(int i = 0; i < 48; i++)
	{
		if (cities[i].researchcenter == true)
		{numResearchCenters++;}

	}
	return numResearchCenters;
}

void PandModel::buildResearchCenter(int playernum)
{
			cout << "Listing Cities in regard to possession of Research Stations..." << endl;
			for(int i = 0; i < 16; i++)
			 {
                cout << left << setw(2) << i    << "  " << setw(16) << cities[i].cityName;
				if(returnResearch(i) == 1){ cout << setw(5) << ":Yes";}
				else {cout << setw(5) << ":No";}

                cout << left << setw(3) << i+16 << "  " << setw(16) << cities[i+16].cityName;
				if(returnResearch(i+16) == 1){cout << setw(5) << ":Yes";}
				else {cout << setw(5) << ":No";}

                cout << left << setw(3) << i+32 << "  " << setw(16) << cities[i+32].cityName;
				if(returnResearch(i+32) == 1){ cout << setw(5) << ":Yes" << endl;}
				else {cout << setw(5) << ":No" << endl;}
			}
		int citychosen;
		citychosen = players[playernum].location;
		if(cities[citychosen].researchcenter == true)
			{
				cout << "This city already has a research center!" << endl << endl;
				setActionsLeft(playernum, 1);
				system("pause");
			}
		if(cities[citychosen].researchcenter == false)
			{
				int decideRemove = 0;
				if( countNumResearchCenters() >= 6)
				{
				cout << "Hit max limit of Research Centers!" << endl;
				cout << "Remove another Research Center?" << endl;
				cout << "1. Yes" << endl << "2. No" << endl;
				cin >> decideRemove;
				}

			if(decideRemove == 1)
			{
				cout << "Choose a city to remove a Research Center (0-47)" << endl;
				int removedyet = 0;
				int choosecity;
				while(removedyet != 1)
				{
					cin >> choosecity;
					if(choosecity >= 0 && choosecity <= 47) //In case the player puts in a bad number
					{
						if(cities[choosecity].researchcenter == true)
						{
							removeResearchCenter(choosecity);
							removedyet = 1;
						}
						if(cities[choosecity].researchcenter == false)
						{cout << "This city does not have a research center. Choose another city" << endl;}
					}

				}
			}

			if(decideRemove != 2){
				addResearchCenter(citychosen);
				cout << "A Research Center has been constructed in " << cities[citychosen].cityName;
				cout << string(5, '\n');
				}
			}
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
	if(!PlayerDeckD.empty())
	{
		playerCard temp;
		temp = PlayerDeckD.front();//from the top
		PlayerDeckD.pop_front();//remove top card
		return temp; 
	}
	else
	{
		playerCard temp;
		temp.value = 0; //Holds the card's number
		temp.cardType = "none";
		temp.cardDescription = "none";
		temp.color = 'n';
		return temp;
	}
}

infectionCard PandModel::drawInfectionCard()//will draw from the top of the deck
{
	infectionCard temp;
	temp = infectionDeck.front();//from the top
	discardInfectionDeck.push_back(temp);//add to discarded cards deck//may need to separate this out as a separate function depending on game rules
	infectionDeck.pop_front();//remove top card

	return temp;  
}

void PandModel::placeInfectionCard(infectionCard temp)
{
	infectionDeck.push_front(temp);
}

infectionCard PandModel::drawBottomInfectionCard() // will draw from bottom of infection deck
{
	infectionCard temp;
	temp = infectionDeck.back();//from the top
	discardInfectionDeck.push_back(temp);//add to discarded cards deck//may need to separate this out as a separate function depending on game rules
	infectionDeck.pop_back(); // remove bottom card
	return temp;  
}

void PandModel::epidemicDrawn()
{
	infectionCard drawnInfCard;

	// Increase infection rate by 1
	infectionRate++;
	// might need to test game over here
	
	drawnInfCard = drawBottomInfectionCard();
	if (cities[drawnInfCard.city].diseasecubes[drawnInfCard.color] > 0){// If adding cubes causes city to go over 3 cubes then outbreak

		diseaseCubes[drawnInfCard.color] = diseaseCubes[drawnInfCard.color] + cities[drawnInfCard.city].diseasecubes[drawnInfCard.color] - 3; // set stock cubes
		cities[drawnInfCard.city].diseasecubes[drawnInfCard.color] = 3; // city now at 3 cubes

		outbreak(drawnInfCard.city); // start outbreak in the city

	}else{ // otherwise add 3 cubes to city/color on card
		cities[drawnInfCard.city].diseasecubes[drawnInfCard.color] = 3; // city now at 3 cubes
		diseaseCubes[drawnInfCard.color] = diseaseCubes[drawnInfCard.color] - 3;  // remove 3 cubes from stock pile
	}
	
	// Shuffle infection discard pile
	shuffleInfectionDeck(discardInfectionDeck);

	// Place on top of infection deck
	mergeInfectionDecks(discardInfectionDeck, infectionDeck); // puts discardInfection Deck on top of infectionDeck
}

void PandModel::discardPlayCard(playerCard discarding)
{
	if (!discarding.remove){ discardPlayerDeckD.push_back(discarding); }//Modified by Omer for contingency planner
}





void PandModel::Load(int loadf){
	string temp;
	int tempint;
	fstream savef;
	int playernum;
	int dcubes[4];
	loadflag = true;
	int decksize;

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
	for (int i = 0; i < 7; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		infectRateArray[i] = tempint;
	}
	savef >> temp;
	dcubes[0] = atoi(temp.c_str());
	savef >> temp;
	dcubes[1] = atoi(temp.c_str());
	savef >> temp;
	dcubes[2] = atoi(temp.c_str());
	savef >> temp;
	dcubes[3] = atoi(temp.c_str());
	loadDCLeft(dcubes[0], dcubes[1], dcubes[2], dcubes[3]);
	savef >> temp;
	tempint = atoi(temp.c_str());
	ForecastPlayed = tempint;
	savef >> temp;
	tempint = atoi(temp.c_str());
	QuietNightPlayed = tempint;
	savef >> temp;
	tempint = atoi(temp.c_str());
	ResilientPlayed = tempint;
	
	//NEW LINE

	savef >> temp;//savef << "CardsRelatedVariables:";
	//savef << " ";
	for (int i = 0; i < numberOfPlayers; i++){
		savef >> temp;//savef << "Player" << i << "Deck";
		//savef << " ";
		for (int x = 0; x < 7; x++){
			savef >> temp;//savef << players[i].cardsonhand[x].value;
			//savef << " ";
			tempint = atoi(temp.c_str());
			if (tempint != -1){ players[i].cardsonhand[x] = playerDeck[tempint]; };
			
		}
	}

	savef >> temp; // savef << "DiscardedInfection:";
	//savef << " ";
	savef >> temp;
	decksize = atoi(temp.c_str());
	discardInfectionDeck.clear();

	for (int i = 0; i < decksize; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		discardInfectionDeck.push_back(SL_IC[tempint]);
		savef >> temp;
		tempint = atoi(temp.c_str());
		discardInfectionDeck.back().color = tempint;
	}
	
	savef >> temp; // savef << "DiscardedPlayer:";
	//savef << " ";
	savef >> temp;//savef << discardPlayerDeckD.size();
	decksize = atoi(temp.c_str());
	//savef << " ";
	discardPlayerDeckD.clear();
	for (int i = 0; i < decksize; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		discardPlayerDeckD.push_back(playerDeck[tempint]);
	}
	discardedEventCards.clear();
	savef >> temp; //DiscardedEventCards
	savef >> temp; 
	decksize = atoi(temp.c_str());
	for (int i = 0; i < decksize; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		discardedEventCards.push_back(playerDeck[tempint]);
	}

	savef >> temp; //Has extra:
	for (int i = 0; i < numberOfPlayers; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		players[i].extracardFlag = tempint;

	}

	savef >> temp; //Extras:
	for (int i = 0; i < numberOfPlayers; i++){
		savef >> temp;
		tempint = atoi(temp.c_str());
		if (temp != "-1"){ players[i].extracard = playerDeck[tempint]; }


	}
	



	savef.close();


}

void PandModel::Save(int savefile , string sfname, int turn){
	int counter = 0 , strc = 1, strbeg=0;
	string str;
	string contents="";
	fstream savef;
	bool begfound=false;
	int tempint;

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
		for (int i = 0; i < 7; i++){
			savef << infectRateArray[i];
			savef << " ";
		}
		savef << getDCLeft(0);
		savef << " ";
		savef << getDCLeft(1);
		savef << " ";
		savef << getDCLeft(2);
		savef << " ";
		savef << getDCLeft(3);
		savef << " ";
		savef << ForecastPlayed;
		savef << " ";
		savef << QuietNightPlayed;
		savef << " ";
		savef << ResilientPlayed;
		savef << " ";

		//NEW LINE

		savef << endl;

		savef << "CardsRelatedVariables:";
		savef << " ";
		for (int i = 0; i < numberOfPlayers; i++){
			savef << "Player" << i+1 << "Deck";
			savef << " ";
			for (int x = 0; x < 7; x++){
				savef << players[i].cardsonhand[x].value;
				savef << " ";
			}
		}
		savef << "DiscardedInfection:";
		savef << " ";
		savef << discardInfectionDeck.size();
		savef << " ";
		std::deque<infectionCard> copyIC;
		tempint = discardInfectionDeck.size();
		for (int i = 0; i < tempint; i++){
			copyIC.push_back(discardInfectionDeck.back());
			savef << discardInfectionDeck.back().city;
			savef << " ";
			savef << discardInfectionDeck.back().color;
			discardInfectionDeck.pop_back();
			savef << " ";
		}
		//RELOADING THE DISCARDED INFECTION DECK
		for (int i = 0; i < tempint; i++){
			discardInfectionDeck.push_back(copyIC.back());
			copyIC.pop_back();
		}

		savef << "DiscardedPlayer:";
		savef << " ";
		savef << discardPlayerDeckD.size();
		savef << " ";
		std::deque<playerCard> copyPC;
		tempint = discardPlayerDeckD.size();
		for (int i = 0; i < tempint; i++){
			copyPC.push_back(discardPlayerDeckD.back());
			savef << discardPlayerDeckD.back().value;
			discardPlayerDeckD.pop_back();
			savef << " ";
		}

		//RELOADING THE DISCARDED PLAYER DECK
		for (int i = 0; i < tempint; i++){
			discardPlayerDeckD.push_back(copyPC.back());
			copyPC.pop_back();
		}

		savef << "DiscardedEvent:";
		savef << " ";
		savef << discardedEventCards.size();
		savef << " ";
		copyPC.clear();

		tempint = discardedEventCards.size();
		for (int i = 0; i < tempint; i++){
			copyPC.push_back(discardedEventCards.back());
			savef << discardedEventCards.back().value;
			discardedEventCards.pop_back();
			savef << " ";
		}


		//RELOADING THE DISCARDED EVENT CARDS
		for (int i = 0; i < tempint; i++){
			discardedEventCards.push_back(copyPC.back());
			copyPC.pop_back();
		}

		savef << "Has Extra:";
		savef << " ";
		for (int i = 0; i < numberOfPlayers; i++){
			savef << players[i].extracardFlag;
			savef << " ";
		}

		savef << "Extras:";
		savef << " ";
		for (int i = 0; i < numberOfPlayers; i++){
			if (players[i].extracardFlag) { savef << players[i].extracard.value; }
			else { savef << -1; }
			savef << " ";
		}






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
			if (counter == savefile +1){ strc = strc - 2;  goto out; }
	
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

void PandModel::mergeInfectionDecks(deque<infectionCard> &deckA, deque<infectionCard> &deckB) // puts deckA on top of deckB
{
	// remove cards from bottom of deckA and put on top of deckB until none remain in deckA
	int cardAmount = deckA.size();
	infectionCard temp;
	
	for(int i = 0; i < cardAmount; i++) // repeat for how many cards are in deckA
	{
		temp = deckA.back(); // set temp as card on bottom deckA
		deckB.push_front(temp); // put temp on top of deckB
		deckA.pop_back(); // remove temp from deckA
	}
	
}

void PandModel::treatCity(int city, int cubecolor, int role) // remove 1 cube of cubecolor from city, all cubes of cubecolor if medic
{
	if(role == 2) // if medic
	{
		cities[city].diseasecubes[cubecolor] = 0; // remove all cubes
	}
	else if(cities[city].diseasecubes[cubecolor] > 0)  // if not medic and there are cubes on the city
	{
		cities[city].diseasecubes[cubecolor]--; // remove one cube
	}
}

void PandModel::addDiseaseCubes(int cityNum, char cubeColr)
{
	//(0,1,2,3 = red,black,blue,yellow)
	int cubeIndex;
	if(cubeColr = 'R') cubeIndex = 0;
	if(cubeColr = 'G') cubeIndex = 1;
	if(cubeColr = 'B') cubeIndex = 2;
	if(cubeColr = 'Y') cubeIndex = 3;
	if(cities[cityNum].diseasecubes[cubeIndex] + 1 > 3)//if city already has 3 cubes of that color
	{
		outbreak(cityNum);//cause an outbreak
		cout<<"Outbreak! \n";
	}
	else
		cities[cityNum].diseasecubes[cubeIndex] = cities[cityNum].diseasecubes[cubeIndex] + 1;

}
void PandModel::outbreak(int cityNum)//
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
	bool alreadyInfected = false;
	std::deque<int> chainThese;
	while(cities[cityNum].adjacentCities[i] != -1)
	{
		
		//infect cities with cubes of city colors
		//if neighbor has 3 already, do not add 4th
		//instead of adding 4th, a chain reaction outbreak occurs after current outbreak is complete
		if(cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] < 3)
		{
			for(int j = 0; j < trackInfect.size(); j++)//go through infect track to see if already infected
			{
				if(cities[cities[cityNum].adjacentCities[i]].value == trackInfect[j].value)
				{
					alreadyInfected = true;
					break;
				}
			}
			if(!alreadyInfected)//if not already infected, infect and add to tracker
			{
				cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex]++;//increase disease cube count by 1 at neighbors
				trackInfect.push_back(cities[cities[cityNum].adjacentCities[i]]);//add infected city to tracker
			}
			
		}
		else if(cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] == 3)//if this neighbor has 3 cubes, cause another outbreak at this city
			chainThese.push_back(cities[cities[cityNum].adjacentCities[i]].value);	 //need to save city value of those we need to chain outbreak. make another deque.
		
		i++;
	
	}
	//needs to happen after the outbreak is complete. When complete, we should have a completed already infected list.
		while (chainThese.size()>0)
		{
			outbreakLevel++;//when chain reaction outbreak occurs, move outbreak marker by 1(increase outbreak level by 1)//done recursively
			//cause a chain reaction outbreak
			chainOutbreak(chainThese.front(), cubeColor);//will use the cube color of orginal outbreak
			trackOutbreak++;

			//chainOutbreak(chainThese.front(),cubecolor);//cause outbreak at this neighbor
			chainThese.pop_front();
		}
	//reset tracker
	if(trackOutbreak == 0)
		trackInfect.clear();//have to stop this when recursion maybe an int counter only if at base recursion
	else trackOutbreak--;
}
void PandModel::chainOutbreak(int cityNum, char color)
{
	//0,1,2,3 = red,black,blue,yellow
	int infectIndex;
	if(color == 'R') infectIndex = 0;
	else if(color == 'G') infectIndex = 1;
	else if(color == 'B') infectIndex = 2;
	else if(color == 'Y') infectIndex = 3;
	//Then place 1 disease cube of the same color on every city connected to that city where outbreak originates.
	int i = 0;
	bool alreadyInfected = false;
	std::deque<int> chainThese;
	while(cities[cityNum].adjacentCities[i] != -1)
	{
		
		//infect cities with cubes of city colors
		//if neighbor has 3 already, do not add 4th
		//instead of adding 4th, a chain reaction outbreak occurs after current outbreak is complete
		if(cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] < 3)
		{
			for(int j = 0; j < trackInfect.size(); j++)//go through infect track to see if already infected
			{
				if(cities[cities[cityNum].adjacentCities[i]].value == trackInfect[j].value)
				{
					alreadyInfected = true;
					break;
				}
			}
			if(!alreadyInfected)//if not already infected, infect and add to tracker
			{
				cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex]++;//increase disease cube count by 1 at neighbors
				trackInfect.push_back(cities[cities[cityNum].adjacentCities[i]]);//add infected city to tracker
			}
			
		}
		else if(cities[cities[cityNum].adjacentCities[i]].diseasecubes[infectIndex] == 3)//if this neighbor has 3 cubes, cause another outbreak at this city
			chainThese.push_back(cities[cities[cityNum].adjacentCities[i]].value);	 //need to save city value of those we need to chain outbreak. make another deque.
		
		i++;
	
		
	//Then place 1 disease cube of the same color on every city connected to that city where outbreak originates.
		//(phat)found city with 3 cubes, infect neighbors if not already infected. Check through array
	//except do not add to cities that have already had an outbreak or chain outbreak.
		//(phat)keep track of cities that have already been infected maybe with an array of already infected cities.
	//cities can have up to 3 diseasce cubes of each color.
	}

}
bool PandModel::researchCure(int playerNum)
{
	//check to see if research station available.
	//city temp = getCityInfo(players[playerNum].location);
	if (cities[players[playerNum].location].researchcenter)
	{

		int R = 0, G = 0, B = 0, Y = 0;//count how many cards of each color
		deque<playerCard> temp;

		for (int i = 0; i < 9; i++)
		if (players[playerNum].cardsonhand[i].value != -1)
		{
			if (players[playerNum].cardsonhand[i].color == 'B') B++;
			if (players[playerNum].cardsonhand[i].color == 'R') R++;
			if (players[playerNum].cardsonhand[i].color == 'G') G++;
			if (players[playerNum].cardsonhand[i].color == 'Y') Y++;
		}
		//if available see if we have enough cards of the same color
		if (players[playerNum].profession == 6)//if scientist
		if (B>3 || R > 3 || G > 3 || Y > 3)//check for 4 of the same color cards
		{
			//display cards that have enough to research cure
			cout << "Choose 4 cards to discard \n";
			if (B > 3)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'B')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (R>3)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'R')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (G>3)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'G')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (Y>3)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'Y')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			//check to see if cure exists
			if (temp[0].color == 'R' && cureMarkers[0] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'G' && cureMarkers[1] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'B' && cureMarkers[2] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'Y' && cureMarkers[3] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			//if cure does not exist discard cards for cure
			int cardNum[4];
			cin >> cardNum[0];
			cin >> cardNum[1];
			cin >> cardNum[2];
			cin >> cardNum[3];
			for (int i = 0; i < 4; i++)
			for (int j = 0; j < 9; j++)
			if (players[playerNum].cardsonhand[j].value == temp[cardNum[i] - 1].value)
				discardCard(playerNum, players[playerNum].cardsonhand[j]);

			cleanHand(playerNum);
			//color of the cure (0,1,2,3 = (R)red,(G)black,(B)blue,(Y)yellow)
			if (temp[0].color == 'R') cureMarkers[0] = true;
			if (temp[0].color == 'G') cureMarkers[1] = true;
			if (temp[0].color == 'B') cureMarkers[2] = true;
			if (temp[0].color == 'Y') cureMarkers[3] = true;
		}
		else return false;//can not research
		if (players[playerNum].profession != 6)//if not scientist
		if (B > 4 || R > 4 || G > 4 || Y > 4)//check for 4 of the same color cards
		{
			cout << "Choose 5 cards to discard \n";
			//display cards that have enough to research cure
			if (B > 4)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'B')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (R>4)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'R')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (G>4)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'G')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			if (Y>4)
			for (int i = 0; i < 9; i++)
			if (players[playerNum].cardsonhand[i].color == 'Y')
			{
				cout << i + 1 << ": " << players[playerNum].cardsonhand[i].cardDescription << endl;
				temp.push_back(players[playerNum].cardsonhand[i]);
			}
			//check to see if cure exists
			if (temp[0].color == 'R' && cureMarkers[0] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'G' && cureMarkers[1] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'B' && cureMarkers[2] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			if (temp[0].color == 'Y' && cureMarkers[3] == true)
			{
				cout << "This cure has already been discovered \n";
				return false;
			}
			//if cure does not exist discard cards for cure
			int cardNum[5];
			cin >> cardNum[0];
			cin >> cardNum[1];
			cin >> cardNum[2];
			cin >> cardNum[3];
			cin >> cardNum[4];
			for (int i = 0; i < 5; i++)
			for (int j = 0; j < 9; j++)
			if (players[playerNum].cardsonhand[j].value == temp[cardNum[i] - 1].value)
				discardCard(playerNum, players[playerNum].cardsonhand[j]);

			cleanHand(playerNum);
			//color of the cure (0,1,2,3 = (R)red,(G)black,(B)blue,(Y)yellow)
			if (temp[0].color == 'R') cureMarkers[0] = true;
			if (temp[0].color == 'G') cureMarkers[1] = true;
			if (temp[0].color == 'B') cureMarkers[2] = true;
			if (temp[0].color == 'Y') cureMarkers[3] = true;
		}
		else return false;//can not research
		//if scientist discard 4 else discard 5
		return true;//research successful
	}
	else
	{
		cout << "You are not at a research center \n";
		return false;//research unsuccessful
	}

}
void PandModel::updateHandsFile(int pno){ //PIPE DATA UPDATE
	fstream hfile;
	hfile.open("C:\\Pand\\hfile.txt");
	std::ofstream("C:\\Pand\\hfile.txt", std::ios::out).close();
	hfile << players[pno].playerName;
	hfile << " ";
	hfile << players[pno].profession;
	hfile << " ";
		for (int x = 0; x < 7; x++){
			hfile << players[pno].cardsonhand[x].value;
			hfile << " ";
		}
		if (players[pno].extracardFlag){ hfile << players[pno].extracard.value << " "; }
		else { hfile << "-1"; hfile << " "; }

		hfile << numberOfPlayers;
		hfile << " ";
		for (int i = 0; i < numberOfPlayers; i++){
			hfile << players[i].location;
			hfile << " ";
		}

	hfile.close();

	fstream savef;
	savef.open("C:\\Pand\\citydetails.txt");
	std::ofstream("C:\\Pand\\citydetails.txt", std::ios::out).close();

	for (int i = 0; i < 48; i++){
		if (getCityColor(i) == 'G'){ savef << "1"; }
		if (getCityColor(i) == 'R'){ savef << "2"; }
		if (getCityColor(i) == 'Y'){ savef << "3"; }
		if (getCityColor(i) == 'B'){ savef << "4"; }
		}
	for (int i = 0; i < 48; i++){
		if (getCityColor(i) == 'G'){ savef << getDiseaseCubes(i,1); }
		if (getCityColor(i) == 'R'){ savef << getDiseaseCubes(i, 0); }
		if (getCityColor(i) == 'Y'){ savef << getDiseaseCubes(i, 3); }
		if (getCityColor(i) == 'B'){ savef << getDiseaseCubes(i, 2); }
	}
	for (int i = 0; i < 48; i++){
		savef << getRCenter(i);
	}





}
bool PandModel::GameOver()
{
	// case 1 game won, all cures
	if (cureMarkers[0] == true && cureMarkers[1] == true && cureMarkers[2] == true && cureMarkers[3] == true)
	{
		gameWin = true;
		allCures = true;
		return true;
	}

	// case 2 game loss outbreak level
	else if (outbreakLevel == 8)
	{
		gameLose = true;
		outbreakTooHigh = true;
		return true;
	}

	// case 3:game loss as a temp I would just check to see if available cubes does not equal 0
	else if (diseaseCubes[0] == 0 ||diseaseCubes[1] == 0 ||diseaseCubes[2] == 0 ||diseaseCubes[3] == 0)
	{
		gameLose = true;
		outOfCubes = true;
		return true;
	}

	// case 4: game loss
	else if (PlayerDeckD.size() < 2)
	{
		gameLose = true;
		outOfCards = true;
		return true;
	}
	else return false;
}

void PandModel::removeDiscardInfect(int index)//resilient population
{
	int size = discardInfectionDeck.size();
	infectionCard *temp = new infectionCard[size];
	for(int i = 0; i < discardInfectionDeck.size(); i++)//copy contents to temp
		temp[i] = discardInfectionDeck[i];
	discardInfectionDeck.clear();//erase contents
	for(int i = 0; i < size; i++)//put everything back minus the city chosen
		if(i!= index)
			discardInfectionDeck.push_back(temp[i]);
}


#endif

