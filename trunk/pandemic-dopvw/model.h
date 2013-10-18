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
struct Playerchar  //Probably want to change to a class when we do the cards in hand data
{
	int profession; //Player's profession will be designated by a value. Something else will transfer the value to
	//the data holding all of the professions and all of their effects
	int location; //This will be the ID number of the city the character is currently located.

	int cardsonhand[7]; //Player can hold 7 cards
	//If player draws a card and num of cards > 7, player can use cards until less than 7, or discard.
};

class PandemicMap
{
	city cities[48];//48 cities, will fill in values with the constructor
	//int value; //The city's ID number. Will be used with cards
	//int color; //Based on the number, this will determine the color of the city.

	//Basically when you try to move to another city via ground, a function will be called to check if the move
	//is valid, using adjacentCities.
public:
	PandemicMap();
	//observers
	city getCityInfo();//maybe seperate into getcityname, getadjcities, getcubes...etc
	Playerchar getPlayerInfo();
	void PrintAdjacent();
	void FillAdjacent(int a, int b, int c, int d, int e, int f, int g, int citynum);
	void FillValue(int x) {value = x;};
	bool isAdjacent(int x);	//For ground travel, will check if desired destination is included in adjacentCities
};

PandemicMap::PandemicMap()//constructor
{
	 std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
                            "Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
                            "Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
                            "Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	for(int i = 0; i < 48; i++)
		cities[i].cityName = cityname[i];
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


}

/*void PandemicMap::PrintAdjacent()/////////////////moving this to view.h
	{
		cout << "Adjacent cities are: | ";
		for(int i = 0; i < 4; i++)
		{
			if(adjacentCities[i] != -1)
			{
			cout << adjacentCities[i] << " | ";
			}
		}
		cout << endl;

	};*/

void PandemicMap::FillAdjacent(int a, int b, int c, int d, int e, int f, int g, int citynum)
	{
		cities[citynum].adjacentCities[0] = a;
		cities[citynum].adjacentCities[1] = b;
		cities[citynum].adjacentCities[2] = c;
		cities[citynum].adjacentCities[3] = d;
		cities[citynum].adjacentCities[4] = e;
		cities[citynum].adjacentCities[5] = f;
		cities[citynum].adjacentCities[6] = g;
	};

	

bool PandemicMap::isAdjacent(int x)	//For ground travel, will check if desired destination is included in adjacentCities
	{
		int hold = 20;

		for(int i = 0; i < 4; i++)
		{
			if(adjacentCities[i] == x)
			{hold = 1;}
			//cout << "Holdvalue: " << hold << endl;
			//Use this to test if hold is updating properly to show true
		}
		if(hold == 1)
		{
			return true;
		}
		else if(hold ==20)
			return false;
	}




void valuetoname(int x); //Converts by integer value into the city's name.
//Problem right now: All the city names are at the bottom of this program.
//It might be handier to house all of the information in another class above, then have Cities inherit the information
//and call the name with a function.
//I would say just put it in the Cities class itself, but we're going to have an array of those.
//We'd have the 48 city names  X 48 instances of the class, wasting memory

//////////////////////////////////////////////////////////////////////////////////////////
//Considered Functions? Other classes?
//////////////////////////////////////////////////////////////////////////////////////////
//Insert here-
//
//void GenerateCities(Cities); //Some way to generate all Cities data (value, adjacent, etc out of main?)
//
//
//Deck
//Draw card
//Game End?
//Card effects, Profession effects
//////////////////////////////////////////////////////////////////////////////////////////



