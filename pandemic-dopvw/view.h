#ifndef VIEW_H
#define VIEW_H
#include "Model.h"
#include <iostream>


class PandView: public PandModel //not sure if Im inheriting correctly. Will modify as I go.
{
	PandModel model;
public:
	PandView();
	PandView(PandModel m);
	
	void showIntro();
	void showCityInfo(int citynum);
	void showActionMenu(int p);
	void showPlayerInfo(int playernum);
	void showNeighbors(int citynum);
	void showCubeLocations();//
	void showPlayersLocation(int numberofplayers);//
	void showInfectionLevel();//stub
	void showHowManyCardsLeft();//stub
	void showDiscardedCards();//stub
	void listDescriptions(int role);//lists the descriptons of roles
	void listActions(int role);//lists specific role actions
};

PandView::PandView()
{

}

PandView::PandView(PandModel m)
{
	model = m;
}

void PandView::showIntro()
{
	std::cout << "Welcome to Pandemic!" << std::endl; 
	std::cout << "Let's get started!" << std::endl; 
	std::cout << "How many Players will be playing?"<< std::endl;
}
void PandView::showCityInfo(int citynum)
{
	city temp = getCityInfo(citynum);
	//print player info, eg. name, role
	std::cout<<"City: " <<temp.cityName<<std::endl;
	std::cout<<"City color: " <<temp.cityColor<<std::endl;
	std::cout<<"Cubes: " <<temp.diseasecubes<<std::endl;
	//std::cout<<"Research Center: " <<temp.researchcenter<<std::endl;//should be converted to yes or no
	std::cout<< "Research Center: ";
	if(returnResearch(citynum) == true){std::cout << "Yes";}
	if(returnResearch(citynum) == false){std::cout << "No";}
}
void PandView::showNeighbors(int citynum)
{
	std::string tempcity;
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	//tempcity = cityname[x];
	city temp = getCityInfo(citynum);
	int i = 0;
	while(temp.adjacentCities[i] != -1)
	{
		std::cout<<i+1<<". City: " << cityname[temp.adjacentCities[i]] <<std::endl;
		i++;
	}
}

void PandView::showActionMenu(int p)
{
	std::cout<<std::endl;
	std::cout<<"1. Move to an adjacent city" << std::endl;
	std::cout<<"2. Play a card " << std::endl;
	std::cout<<"3. Remove cube " << std::endl;
	std::cout<<"4. Shuttle Flight " << std::endl;
	std::cout<<"5. List infected cities " << std::endl;
	std::cout<<"6. List other things " << std::endl;//expansion for later
	//listActions(p); //additional actions that are unique to each player are being shown here
	//Commented this out since it was getting messy while debugging
	//Let's use listActions in another function, such as  7. Use Role Ability    -Vu
	std::cout<<"What would you like to do : ";
	
}

void PandView::showPlayerInfo(int playernum)
{
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	Playerchar temp = model.getPlayerInfo(playernum-1);
	std::cout<<"Player name: " <<  temp.playerName << std::endl;
	std::cout<<"Player location: " << cityname[temp.location] << std::endl;

	//////////////

	
	std::cout << "Player role: " << temp.profName << std::endl;

	/*   //Was getting messy, commenting out for now

	//std::cout << "Player role(int): " << temp.profession << std::endl; //Added to help with debug 
	std::cout << "Role details: " << std::endl;
	listDescriptions(temp.profession);
	if (temp.profession == 0){
		if (temp.extracardFlag){
			std::cout << "Extra event card: " << temp.CPextracard.cardType << std::endl;
		}
		else{
			std::cout << "Extra event card: " << "None" << std::endl;
		}
	}
	*/
    //std::cout<<"Player role: " << temp.playerName << std::endl;
	//::cout<<"Player cards: " << temp.playerName << std::endl;
	
}

void PandView::showCubeLocations()//need to rewrite to show all 4 types of cubes per city
{
	std::cout<<"This function will show infection cube location \n";
	city temp;
	char infectionColor[4] = {'R', 'G', 'B', 'Y'};

	for (int i = 0; i < 48; i++)
	{
		temp = model.getCityInfo(i);
		for(int j = 0; j < 5; j++)//traverse through different color cubes that may be stored in this city
		if (temp.diseasecubes[j] > 0)
		{
			
			std::cout<<"City: " << temp.cityName <<"  "; 
			for(int p = 0; p < temp.diseasecubes[j]; p++)
			std::cout<<infectionColor[j];//each letter printed represents a cube of that color
			std::cout<<endl;
		}
	}
}
void PandView::showPlayersLocation(int numberofplayers)
{
	std::cout<<"This function will show all players current location \n";
	Playerchar temp;
	city tempcity;
	for(int i = 0; i < numberofplayers; i++)
	{
		temp = getPlayerInfo(i);
		tempcity = getCityInfo(temp.location);
		std::cout<<"Player: "<<temp.playerName << "City: " << tempcity.cityName << std::endl;
	}
}
void PandView::showInfectionLevel()
{
	int temp = getInfectionRate();
	std::cout<<"Current Level of infection: " << temp<< std::endl;
}
void PandView::showHowManyCardsLeft()
{
	std::cout<<"This function will show how many cards are remaining in the deck \n";
}
void PandView::showDiscardedCards()
{
	std::cout<<"This function will show the cards that have been discarded \n";
}

void PandView::listActions(int role){
	if (role == 0){
		std::cout << "7. Store a discarded card" << std::endl;
		
	}
	if (role == 1){
		std::cout << "7. Move a pawn of your own" << std::endl;
		std::cout << "8. Move a pawn of another player" << std::endl;
		
	}
	if (role == 2){
		std::cout << "Passive abilities:" << std::endl;
	    std::cout << "* When a city is treated, all cubes of the same color are treated " << std::endl;
		std::cout << "* Known cures are administered with no action cost " << std::endl;
		

	}
	if (role == 3){
		std::cout << "7. Build a research station" << std::endl;
		

	}
	if (role == 4){
		std::cout << "Passive abilities:" << std::endl;
		std::cout << "* Prevents disease cube placemenets in the city and the ones surrounding " << std::endl;
	

	}
	if (role == 5){
		std::cout << "7. Give one of your cards to another player" << std::endl;
		
	}
	if (role == 6){
		std::cout << "Passive abilities:" << std::endl;
		std::cout << "* Needs only 4 cards of the same color to discover a cure " << std::endl;
	}

}

void PandView::listDescriptions(int role)
{
	//Playerchar temp = getPlayerInfo(player);

	std::cout <<std::endl;
	if (role==0){
		std::cout <<"A player who has the 'Contigency Plan' role can take any discarded Event card"<<std::endl;
		std::cout <<"and store it with this card."<<std::endl;
		std::cout <<"The stored Event card will be discarded once used!"<<std::endl;
	}
	if (role == 1){
		std::cout <<"A player who has the 'Dispatcher' role can move their fellow player pawns on your"<<std::endl;
		std::cout <<"turns as if they were their own."<<std::endl;
		std::cout <<"They can also move any pawn to another city containing a pawn for 1 action."<<std::endl;
	}
	if (role == 2){
		std::cout <<"A player who has the 'Medic' role can remove all cubes of a single color when they treat a city."<<std::endl;
		std::cout <<"They can administer known cures for free."<<std::endl;
	
	}
	if (role == 3){
		std::cout <<"A player who has the 'Operations Expert' can build a research station in their current city for"<<std::endl;
		std::cout <<"one action."<<std::endl;
		
	}
	if (role == 4){
		std::cout <<"A player who has the 'Quarantine Specialist' role can prevent disease cube placemenets in the city"<<std::endl;
		std::cout <<"they are in and all of the ones connected to it"<<std::endl;
		
	}
	if (role == 5){
		std::cout <<"A player who has the 'Researcher' role can give a player cards from their hands for 1 action per card."<<std::endl;
		std::cout <<"Both of their pawns must be in the same city but it doesn't matter which city they are in."<<std::endl;
	}
	if (role == 6){
		std::cout <<"A player who has the 'Scientist' role need only 4 cards of the same color to discover a cure."<<std::endl;
	}

	std::cout << std::endl;
};
#endif