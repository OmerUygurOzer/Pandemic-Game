class Cities
{
	int value; //The city's ID number. Will be used with cards
	int researchcenter; //Could be a bool instead, 0 or 1 to indicate presence of a research center
	int diseasecubes; //Number of disease cubes currently
	int color; //Based on the number, this will determine the color of the city.
	int adjacentCities[7]; //I don't think any city has more than 6 adjacent cities, so 7
	//adjacentCities will house the values of cities that are adjacent to the selected city

	//Basically when you try to move to another city via ground, a function will be called to check if the move
	//is valid, using adjacentCities.
public:

	void PrintAdjacent()
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

	};

	void FillAdjacent(int a, int b, int c, int d, int e, int f, int g)
	{
		adjacentCities[0] = a;
		adjacentCities[1] = b;
		adjacentCities[2] = c;
		adjacentCities[3] = d;
		adjacentCities[4] = e;
		adjacentCities[5] = f;
		adjacentCities[6] = g;
	};

	void FillValue(int x)
	{value = x;};

	bool isAdjacent(int x)	//For ground travel, will check if desired destination is included in adjacentCities
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
};

struct Playerchar  //Probably want to change to a class when we do the cards in hand data
{
	int profession; //Player's profession will be designated by a value. Something else will transfer the value to
	//the data holding all of the professions and all of their effects
	int location; //This will be the ID number of the city the character is currently located.

	int cardsonhand[7]; //Player can hold 7 cards
	//If player draws a card and num of cards > 7, player can use cards until less than 7, or discard.




};


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