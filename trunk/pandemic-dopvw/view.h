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
	
	
	void showCityInfo(int citynum);
	void showActionMenu(int citynum);
	void showPlayerInfo(int playernum);
	void showNeighbors(int citynum);
	void showCubeLocations();
	void showPlayersLocation();
	void showInfectionLevel();
	void showHowManyCardsLeft();
	void showDiscardedCards();

};

PandView::PandView()
{

}

PandView::PandView(PandModel m)
{
	model = m;
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

void PandView::showActionMenu(int citynum)
{
	std::cout<<std::endl;
	std::cout<<"1. move to adjacent" << std::endl;
	std::cout<<"2. use city card " << std::endl;
	std::cout<<"3. remove cube " << std::endl;
	std::cout<<"4. build research center " << std::endl;
	std::cout<<"5. list infected cities " << std::endl;
	std::cout<<"6. list other things " << std::endl;//expansion for later
	std::cout<<"What would you like to do : " << std::endl;
	
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



#endif