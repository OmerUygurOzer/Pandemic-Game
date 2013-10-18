#ifndef VIEW_H
#define VIEW_H

class PandView
{


};
#endif

void valuetoname(int x)//will use this to normalize user interface
{
	string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "Ho Chi Minh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	cout << cityname[x];
};