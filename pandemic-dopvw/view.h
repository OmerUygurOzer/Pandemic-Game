#ifndef VIEW_H
#define VIEW_H
#include "Model.h"
#include <iostream>

class PandView:PandemicMap //not sure if Im inheriting correctly. Will modify as I go.
{
public:
	void showCityInfo();
	void showPlayerInfo();
	void showNeighbors();
	void showCubeLocations();
	void showPlayersLocation();
	void showInfectionLevel();
	void showHowManyCardsLeft();
	void showDiscardedCards();

};
#endif

void valuetoname(int x)//will use this to normalize user interface
{
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	std::cout << cityname[x];
};