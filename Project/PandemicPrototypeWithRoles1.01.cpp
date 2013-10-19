#include <iostream>
using namespace std;
#include <string>
#include <time.h>
#include <stdlib.h>


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

class RoleActions{ //What each player can do with their roles.
	int player;
	int profession;
	
	public:
		
		void setProfession(int x){
			profession = x;
		};
		void setPlayer(int y){
			player=y;	
		};
		int getAction(){
			int c;
			cout <<endl<< "What would you like to do?   ";
			cin >>c;
			return c;	
		};
		void performAction(){ //This is temporary. it will be improved
			int action;
			action = getAction();
			cout <<endl<< "Action performed!"<<endl<<endl ;
			
		};
		void listActions(){
			cout <<endl;
			if (profession==0){
				cout <<"A player who has the 'Contigency Plan' role can take any discarded Event card"<<endl;
				cout <<"and store it with this card."<<endl;
				cout <<"The stored Event card will be discarded once used!"<<endl;
			}
			if (profession==1){
				cout <<"A player who has the 'Dispatcher' role can move their fellow player pawns on your"<<endl;
				cout <<"turns as if they were their own."<<endl;
				cout <<"They can also move any pawn to another city containing a pawn for 1 action."<<endl;
			}
			if (profession==2){
				cout <<"A player who has the 'Medic' role can remove all cubes of a single color when they treat a city."<<endl;
				cout <<"They can administer known cures for free."<<endl;
			
			}
			if (profession==3){
				cout <<"A player who has the 'Operations Expert' can build a research station in their current city for"<<endl;
				cout <<"one action."<<endl;
				
			}
			if (profession==4){
				cout <<"A player who has the 'Quarantine Specialist' role can prevent disease cube placemenets in the city"<<endl;
				cout <<"they are in and all of the ones connected to it"<<endl;
				
			}
			if (profession==5){
				cout <<"A player who has the 'Researcher' role can give a player cards from their hands for 1 action per card."<<endl;
				cout <<"Both of their pawns must be in the same city but it doesn't matter which city they are in."<<endl;
			}
			if (profession==6){
				cout <<"A player who has the 'Scientist' role need only 4 cards of the same color to discover a cure."<<endl;
			}
		
					
		};
		
		
	
};




int main ()
{
	char roles [7] = {'a','a' ,'a', 'a', 'a', 'a', 'a'};   //To keep a track of roles that are still available
	string rolenames[7] = {"Contingency Plan" , "Dispatcher" , "Medic" , "Operations Expert" , "Quarantine Specialist" , "Researcher" , "Scientist"}; //RoleNames
	RoleActions Role[2];//Role Actions are being managed
	
	
	Cities City[48]; //Initialize the 48 cities

	//int NUMPLAYERS
	//cin >> NUMPLAYERS
	// is NUMPLAYERS > 1  && < 5  ?     etc.
	Playerchar Players[2]; //Would rather make it a value input at the beginning, since the game is 2 to 4 players
						//Just going to use 2 for this example

	//Assigning the roles for both players
	// 't' means the profession is already taken
	// randomly assigns a profession to every player
	
	
	
	for (int ply = 0 ; ply<2 ; ply++){
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

	//cout << "Player 1 is a " << rolenames[(Players[0].profession)]<<endl;
	//Role[0].listActions(); cout<<endl;
	//cout << "Player 2 is a " << rolenames[(Players[1].profession)]<<endl;
	//Role[1].listActions(); cout<<endl;

	

	/////////////////////////////////////////////////////////////////////////////////////
	//Temporarily just set it fixed to Player 1's turn permanently to simulate movement//
	/////////////////////////////////////////////////////////////////////////////////////
	int Playerturn;
	Playerturn = 0;


	//-1 Is a filler
	City[0].FillAdjacent(25,34,14,7, -1, -1, -1);
	City[1].FillAdjacent( 9, 47, 28, -1, -1, -1, -1);
	City[2].FillAdjacent( 14, 7, 35, 17, 44, -1, -1);
	City[3].FillAdjacent( 20, 8, 15, 12, 13, -1, -1);
	City[4].FillAdjacent( 40, 39, -1, -1, -1, -1, -1);
	City[5].FillAdjacent( 27, 28, 22, 6, 38, -1, -1);
	City[6].FillAdjacent( 5, 38, -1, -1, -1, -1, -1);
	City[7].FillAdjacent( 0, 14, 2, 35, 18, -1, -1);
	City[8].FillAdjacent( 31, 10, 20, 3, 15, -1, -1);
	City[9].FillAdjacent( 36, 24, 27, 1, 46, -1, -1);
	City[10].FillAdjacent( 44, 17, 31, 8, 20, -1, -1);
	City[11].FillAdjacent( 23, 34, 29, 41, -1, -1, -1);
	City[12].FillAdjacent( 15, 3, 13, 26, -1, -1, -1);
	City[13].FillAdjacent( 20, 3, 12, 26, 43, 40, -1);
	City[14].FillAdjacent( 41, 29, 0, 7, 2, 30, -1);
	City[15].FillAdjacent( 3, 8, 42, 12, -1, -1, -1);
	City[16].FillAdjacent( 19, 18, -1, -1, -1, -1, -1);
	City[17].FillAdjacent( 44, 2, 35, 31, 10, -1, -1);
	City[18].FillAdjacent( 7, 21, 19, 16, -1, -1, -1);
	City[19].FillAdjacent( 21, 18, 16, -1, -1, -1, -1);
	City[20].FillAdjacent( 10, 8, 3, 13, -1, -1, -1);
	City[21].FillAdjacent( 38, 19, 18, -1, -1, -1, -1);
	City[22].FillAdjacent( 27, 5, 37, -1, -1, -1, -1);
	City[23].FillAdjacent( 32, 25, 34, 11, -1, -1, -1);
	City[24].FillAdjacent( 36, 9, 27, 42, -1, -1, -1);
	City[25].FillAdjacent( 32, 23, 34, 0, 38, -1, -1);
	City[26].FillAdjacent( 43, 13, 12, 42, 36, -1, -1);
	City[27].FillAdjacent( 9, 24, 22, 5, 28, -1, -1);
	City[28].FillAdjacent( 1, 27, 5, 47, -1, -1, -1);
	City[29].FillAdjacent( 11, 34, 14, -1, -1, -1, -1);
	City[30].FillAdjacent( 41, 14, 44, -1, -1, -1, -1);
	City[31].FillAdjacent( 17, 10, 8, -1, -1, -1, -1);
	City[32].FillAdjacent( 23, 25, 46, 47, -1, -1, -1);
	City[33].FillAdjacent( 45, 43, -1, -1, -1, -1, -1);
	City[34].FillAdjacent( 11, 23, 25, 0, 29, -1, -1);
	City[35].FillAdjacent( 17, 2, 7, -1, -1, -1, -1);
	City[36].FillAdjacent( 45, 26, 9, 24, -1, -1, -1);
	City[37].FillAdjacent( 22, -1, -1, -1, -1, -1, -1);
	City[38].FillAdjacent( 5, 6, 21, 25, -1, -1, -1);
	City[39].FillAdjacent( 4, 40, 45, -1, -1, -1, -1);
	City[40].FillAdjacent( 4, 39, 45, 43, 13, -1, -1);
	City[41].FillAdjacent( 11, 30, 14, -1, -1, -1, -1);
	City[42].FillAdjacent( 24, 26, 15, -1, -1, -1, -1);
	City[43].FillAdjacent( 33, 40, 13, 26, -1, -1, -1);
	City[44].FillAdjacent( 30, 2, 17, 10, -1, -1, -1);
	City[45].FillAdjacent( 36, 33, 40, 39, -1, -1, -1);
	City[46].FillAdjacent( 32, 47, 9, -1, -1, -1, -1);
	City[47].FillAdjacent( 46, 32, 28, 1, -1, -1, -1);

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
		
		/* I'm adding this part to make the game seem more realistic. 
		it will need to be improved obviously but we'll get back to it later */
		cout << "Player 1 is a " << rolenames[(Players[0].profession)]<<endl;
		Role[0].listActions(); cout<<endl;
		Role[0].performAction();

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
	string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	cout << cityname[x];
};
