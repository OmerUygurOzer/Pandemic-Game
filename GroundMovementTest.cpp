//Vu Huynh CS4170

//Prototype Program
//Purpose:
//	- Simulate adjacent city movement.
//	- Basic suggestion for storage of game data.
//	- Layout for other player actions.

// Things to address:
// -There'll be a lot more rules due to card effects, we need to account for all of them
// -There are different types of research centers, just having a value to determine the presence of one alone isn't enough
// -Disease cube types, might need a class of their own
// -Roles are cards, some cards allow you to change to an unsued role card, needs separate deck?
// -Some cards can affect another player
// -Discard Pile
// -A player using a card when it's not his turn
// -Card Shuffling

//We'll be using an array of classes for each set of data.


	/*  Five City Example Key:
	Value:  City:
	0		New York
	1		Chicago
	2		London
	3		Paris
	4		San Francisco

	Example Map
	4SF-------1CH		2LDN-----3PRS
	   \		\		/
		-------0NY------

		So:
		0(NewYork)	=	1, 2, 4
		1(Chicago)	=	0, 4
		2(London)	=	0, 3
		3(Paris)	=	2
		4(SanFran)	=	0, 1

	*/

#include <iostream>
using namespace std;
#include <string>


class Cities
{
	int value; //The city's ID number. Will be used with cards
	int researchcenter; //Could be a bool instead, 0 or 1 to indicate presence of a research center
	int diseasecubes; //Number of disease cubes currently
	int color; //Based on the number, this will determine the color of the city.
	int adjacentCities[4]; //I just randomly put in 4, I forgot how to do it dynamically with vectors
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

	void FillAdjacent(int a, int b, int c, int d)
	{
		adjacentCities[0] = a;
		adjacentCities[1] = b;
		adjacentCities[2] = c;
		adjacentCities[3] = d;
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

int main ()
{
	////////////////Print map on console for visual purposes right now////////////////
	//Not very clean, just wanted it visually for now

	cout<< endl << "Test Map" << endl << endl;
	cout<< "  4SF-------1CH        2LDN-----3PRS" << endl;
	cout<< "    \\        \\       /" << endl;
	cout<< "     -------0NY------" << endl << endl;
	Cities City[48]; //Initialize the 48 cities

	//int NUMPLAYERS
	//cin >> NUMPLAYERS
	// is NUMPLAYERS > 1  && < 5  ?     etc.
	Playerchar Players[2]; //Would rather make it a value input at the beginning, since the game is 2 to 4 players
						//Just going to use 2 for this example




	/////////////////////////////////////////////////////////////////////////////////////
	//Temporarily just set it fixed to Player 1's turn permanently to simulate movement//
	/////////////////////////////////////////////////////////////////////////////////////
	int Playerturn;
	Playerturn = 0;


	//////////////////////////////////////////////////////////////////////////////////////
	//Recap Map:



	/*  Five City Example
	Key:
	Value:  City:
	0		New York
	1		Chicago
	2		London
	3		Paris
	4		San Francisco

	Example Map
	4SF-------1CH		2LDN-----3PRS
	   \		\		/
		-------0NY------

		So..
		0(NewYork)	=	1, 2, 4
		1(Chicago)	=	0, 4
		2(London)	=	0, 3
		3(Paris)	=	2
		4(SanFran)	=	0, 1

	*/

	//Filling in adjacent cities, a little tedious but we can just use values only
	City[0].FillAdjacent(1,2,4,-1); //-1 is just a filler
	City[1].FillAdjacent(0,4,-1,-1);
	City[2].FillAdjacent(0,3,-1,-1);
	City[3].FillAdjacent(2,-1,-1,-1);
	City[4].FillAdjacent(0,1,-1,-1);
	

	///Initialize City value////////
	for(int i = 0; i <= 48; i++)
	{City[i].FillValue(i);}
	////////////////////////////////


	///Movement Simulation///
	Players[Playerturn].location = 0;  //Setting it by default the player is in New York
	//As the player is in New York the player should be allowed to move to 1(Chicago), 2(London), or 4(SF)
	//We will use isAdjacent in the class to allow the movements.


	//While ( Player's remaining moves left != 0 )   -  Using location for this test. Ends if player moves to -1.
	//All cities are adjacent to -1 right now, so you can break out from any city.
	while(Players[Playerturn].location != -1)
	{
		////////////////////////////////////////////////////////////////////////////////////////////
		//Switch : Move by ground / View Cards / Use card / Cure disease / Share knowledge / etc.//
		//////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////
		//Move by ground :
		//Player 0 would be odd, so Player+1. Perhaps use string Playername later?
		//  cout << "Player " << Playerturn+1 << " is at location " << Players[Playerturn].location << endl;
		//Above is old display by value only, now incorporating city name.

		cout << "Player " << Playerturn+1 << " is currently at (" << Players[Playerturn].location << ") ";
		valuetoname(Players[Playerturn].location);
		cout << endl;



		City[Players[Playerturn].location].PrintAdjacent();
		cout << "Move to: ";
		int x = -5; //Placeholder value
movement:
		cin >> x;
		/////////////////////////////If Destination is not in adjacentCities of PlayerLocation, return false///////
		if( (City[Players[Playerturn].location].isAdjacent(x)) == true)
		{
			Players[Playerturn].location = x;
		}
		else
		{
			cout << "Invalid location, please enter another location: ";
			goto movement;
		}

		//player moves remaining - 1;
		//////////////////////////////////////////

		//////////////////Movement by using a card////////////////////////
		/*
			showcards

			select card  -->  is card value = current city value?
						yes = prompt to move to any city

						no = prompt to move to city stated on card
		*/

		/////////////////Movement by research station/////////////////////
		/*
			Does player current location have a research station?
			
			yes = show other locations with research stations
					prompt to choose another city with research station
					does selection have research station?
							yes = move to location
							no = invalid move message


			no = cannot use move by research station


		*/

	}

	///////////////////// Next Player's Turn /////////////////////////////////////////////////////
	// if playerturn == NUMPLAYERS , playerturn = 0;  If last player, go back to first player
	// else playerturn += 1;        Else go to next player
	// go back to above loop if game end conditions have not been met
	//////////////////////////////////////////////////////////////////////////////////////////////


	return 0;
};


void valuetoname(int x)
{
	string cityname[48] = {"New York", "Chicago", "London", "Paris", "San Francisco"};

	cout << cityname[x];


};