#ifndef MODEL_H
#define MODEL_H
#include <string>

struct city//empty city container
{
	std::string cityName;//city name
	int adjacentCities[7];//I don't think any city has more than 6 adjacent cities, so 7
						  //adjacentCities will house the values of cities that are adjacent to the selected city
	char cityColor;//city color
	int diseasecubes; //Number of disease cubes currently
	int researchcenter; //Could be a bool instead, 0 or 1 to indicate presence of a research center
	
};

struct playerCard
{
	std::string cardType;
	std::string cardDescription;
};
struct infectionCard
{
	std::string cardType;
	std::string cardDescription;
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
	bool extracardFlag = false; //whether a card is chosen already or not


	//If player draws a card and num of cards > 7, player can use cards until less than 7, or discard.
	bool cardSlotAvailable[7];//if player uses a card from anywhere but end we'll need to keep track or use a shift

	int ActionsLeft; //This is an int that we'll be accessing to determine the remaining actions a player has left
};


class PandModel
{
	city cities[48];//48 cities, will fill in values with the constructor
	Playerchar players[4];//maximum 4 players
	playerCard playerDeck[59];//59 Player cards
	infectionCard infectionDeck[48];//48 infection cards
	int infectionLevel;

	
public:
	PandModel();
	//observers
	city getCityInfo(int citynum) {return cities[citynum];}//maybe seperate into getcityname, getadjcities, getcubes...etc
	int getNeighbor(int currentcity, int nextcity){return cities[currentcity].adjacentCities[nextcity];}

	bool validNeighbor(int currentcity, int nextcity); //stub - need function to work with Ly's new movement function to check adjacency

	Playerchar getPlayerInfo(int playernum){return players[playernum];}
	playerCard drawPlayerCard(int random);//use a random number generator between 0-58 without replacement and store in a stack otherwise forecast special event can not preview top  6 cards.
	infectionCard drawInfectionCard(int random);//use a random number generator between 0-47 without replacement and store in a vector otherwise epidemic card can not draw from bottom of deck.


	void PrintAdjacent();
	void FillAdjacent(int a, int b, int c, int d, int e, int f, int g, int citynum);
	//void FillValue(int x) {value = x;};
	bool isAdjacent(int x);	//For ground travel, will check if desired destination is included in adjacentCities
	//setters
	void setPlayerName(int playernum, std::string name);
	void setPlayerRole(int playernum, int profession, std::string profName);
	void setPlayerLocation(int playernum, int location);//use to set new location

	void ActionsInitialize(int playernum) {players[playernum].ActionsLeft = 0;}
	void setActionsLeft(int playernum, int addAction); // {Playerchar.ActionsLeft += addAction;       }
	int getActionsLeft (int playernum) {return players[playernum].ActionsLeft;}
	int getInfectionLevel(){return infectionLevel;}//for view to access/display infection level
	int getPlayerRole(int playerNo){ return players[playerNo].profession; } //returns the player role
	void setInfectionLevel();//stub
	
	//Role action:
	void performRoleActions(int playernum, int actionNo , int loc); //Performs unique player actions
	
};

PandModel::PandModel()//constructor
{
	char citycolors[48]= {'G', 'B', 'G', 'R', 'R', 'Y', 'Y', 'G', 'G', 'B',
							'G', 'B', 'R', 'R', 'G', 'R', 'Y', 'G', 'Y', 'Y',
                            'G', 'Y', 'Y', 'B', 'Y', 'B', 'R', 'Y', 'Y', 'B',
                            'G', 'G', 'B', 'R', 'B', 'G', 'B', 'Y', 'Y', 'R',
                            'R', 'B', 'R', 'R', 'G', 'R', 'B', 'B'};
	 std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
                            "Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
                            "Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
                            "Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};

	 for(int i = 0; i<48; i++)//city cards for infection deck
	 {
		 infectionDeck[i].cardType = "City";
		 infectionDeck[i].cardDescription = cityname[i];
	 }
	 for(int i = 0; i<48; i++)//city cards for player deck
	 {
		 playerDeck[i].cardType = "City";
		 playerDeck[i].cardDescription = cityname[i];
	 }
	 for(int i = 48; i<54; i++)//epidemic cards for player deck
	 {
		 playerDeck[i].cardType = "Epidemic";
		 playerDeck[i].cardDescription = "1.Increase\n 2.Infect\n 3.Intensify\n";
	 }
	 ////////////////////////////////////////////////Special Event Cards for player deck
	 playerDeck[54].cardType = "Special Event";
	 playerDeck[54].cardDescription = "Airlift: ";

	 playerDeck[55].cardType = "Special Event";
	 playerDeck[55].cardDescription = "Forecast: ";

	 playerDeck[56].cardType = "Special Event";
	 playerDeck[56].cardDescription = "Government Grant: ";

	 playerDeck[57].cardType = "Special Event";
	 playerDeck[57].cardDescription = "One Quiet Night: ";

	 playerDeck[58].cardType = "Special Event";
	 playerDeck[58].cardDescription = "Resilient Population: ";

	 for(int i = 0; i < 48; i++)
	{
		cities[i].cityName = cityname[i];
		cities[i].diseasecubes = 0;//I believe we need to radomize the cubes location.
		cities[i].cityColor = citycolors[i];
		cities[i].researchcenter = 0;

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

playerCard PandModel::drawPlayerCard(int random)
{
	return playerDeck[random];
}
#endif

