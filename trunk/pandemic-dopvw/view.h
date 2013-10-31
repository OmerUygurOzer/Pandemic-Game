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
	void showActionMenu();
	void showPlayerInfo(int playernum);
	void showNeighbors(int citynum);
	void showCubeLocations();//
	void showPlayersLocation(int numberofplayers);//
	void showInfectionLevel();//stub
	void showHowManyCardsLeft();//stub
	void showDiscardedCards();//stub
	void pActionCount(); //stub for player actions remaining per turn counter
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
	std::cout<<"Research Center: " <<temp.researchcenter<<std::endl;//should be converted to yes or no
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

void PandView::showActionMenu()
{
	std::cout<<std::endl;
	std::cout<<"1. move to adjacent" << std::endl;
	std::cout<<"2. use city card " << std::endl;
	std::cout<<"3. remove cube " << std::endl;
	std::cout<<"4. build research center " << std::endl;
	std::cout<<"5. list infected cities " << std::endl;
	std::cout<<"6. list other things " << std::endl;//expansion for later
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
	//std::cout<<"Player role: " << temp.playerName << std::endl;
	//::cout<<"Player cards: " << temp.playerName << std::endl;
}

void PandView::showCubeLocations()
{
	std::cout<<"This function will show infection cube location \n";
	city temp;
	for (int i = 0; i < 48; i++)
	{
		temp = getCityInfo(i);
		if (temp.diseasecubes > 0)
		{
			std::cout<<"City: " << temp.cityName << "cubes: "<<temp.diseasecubes << std::endl;
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
	std::cout<<"This function will show the current infection level \n";
}
void PandView::showHowManyCardsLeft()
{
	std::cout<<"This function will show how many cards are remaining in the deck \n";
}
void PandView::showDiscardedCards()
{
	std::cout<<"This function will show the cards that have been discarded \n";
}

#endif