
#include "Model.h"
#include <iostream>

std::string valuetoname(int x)//will use this to normalize user interface
{
	std::string temp;
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	temp = cityname[x];
	return temp;
};

class PandView:PandemicMap //not sure if Im inheriting correctly. Will modify as I go.
{
public:
	void showCityInfo(int citynum);
	void showActionMenu(int citynum);
	void showPlayerInfo();
	void showNeighbors(int citynum);
	void showCubeLocations();
	void showPlayersLocation();
	void showInfectionLevel();
	void showHowManyCardsLeft();
	void showDiscardedCards();

};

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
	city temp = getCityInfo(citynum);
	int i = 0;
	while(temp.adjacentCities[i] != -1)
	{
		std::string cityName = valuetoname(temp.adjacentCities[i]);
		std::cout<<"City: " << cityName <<std::endl;
		i++;
	}
}

void PandView::showActionMenu(int citynum)
{
	std::cout<<"1. move to adjacent" << std::endl;
	std::cout<<"2. use city card " << std::endl;
	std::cout<<"3. remove cube " << std::endl;
	std::cout<<"4. build research center " << std::endl;
	std::cout<<"5. list infected cities " << std::endl;
	std::cout<<"6. list other things " << std::endl;//expansion for later
	std::cout<<"What would you like to do : " << std::endl;
	int answer;
	std::cin>>answer;//modify to restrict input from 1-6
	//use answer to bring up other menu items.
	switch (answer)
	{
	case 1: showNeighbors(citynum);//and move to neighbor
		break;
	case 2: //use citycard
		break;
	case 3://remove cube
		break;
	case 4: //build research
		break;
	case 5: //show infected cities
		break;
	case 6://misc
		break;
	}
}