// Written by Darshan Bhakta
// PANDEMIC! 
// This is just the main file that will ask for number of 
// players and names.

#include <iostream>
#include <string>
using namespace std;

int numberofplayers;
string player1, player2, player3, player4;

int main ()
{
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
// there are.
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

// Insert function call to start game?
return 0;
}
