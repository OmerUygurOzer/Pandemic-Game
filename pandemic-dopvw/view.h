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
	void showPlayerRoleInfo(int playernum);//
	void showPlayerHand(int);
	void showNeighbors(int citynum);
	void showCubeLocations();//
	void showPlayersLocation(int numberofplayers);//
	void showInfectionLevel();//stub
	void showHowManyPlayerCardsLeft();//stub
	void showDiscardedPlayerCards();//stub
	void showDiscardedInfectionCards();//stub
	void showPlayCard(playerCard);
	void showInfectCard(infectionCard);
	void listDescriptions(int role);//lists the descriptons of roles
	string listActions(int role,int line);//lists specific role actions
	void askPlayerNumber();
	void printCityColumns();
	void printResearchCenters();
	void dispatcherloc(int playernum);

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
	std::cout << "Let's get started!" << std::endl << std::endl;
	std::cout << "1- New Game" << std::endl;
	std::cout << "2- Load" << std::endl;
	//std::cout << "How many Players will be playing?"<< std::endl;					Moved to askPlayerNumber
}

void PandView::askPlayerNumber(){
	std::cout << "How many Players will be playing?" << std::endl;
}

void PandView::showCityInfo(int citynum)
{
	char infectionColor[4] = {'R', 'G', 'B', 'Y'};
	city temp = model.getCityInfo(citynum);//reference model 
	//print player info, eg. name, role
	std::cout<<"City: " <<temp.cityName<<std::endl;
	std::cout<<"City color: " <<temp.cityColor<<std::endl;

	std::cout<<"Cubes: ";
	for(int j = 0; j < 4; j++)//traverse through different color cubes that may be stored in this city
		if (temp.diseasecubes[j] > 0)
			for(int p = 0; p < temp.diseasecubes[j]; p++)
				std::cout<<infectionColor[j];//each letter printed represents a cube of that color
			
	std::cout<<endl;
	//std::cout<<"Research Center: " <<temp.researchcenter<<std::endl;//should be converted to yes or no
	std::cout<< "Research Center: ";
	if(model.returnResearch(citynum) == true){std::cout << "Yes";}
	if(model.returnResearch(citynum) == false){std::cout << "No";}
}
void PandView::showNeighbors(int citynum)
{
	std::string tempcity;
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "HoChiMinh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	city temp = model.getCityInfo(citynum);
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
	std::cout<<  "1. Move to an adjacent city  ||Profession Abilities:" << std::endl;
	std::cout<<  "2. Play a card		     ||"; std::cout << listActions(p,1)<< std::endl;
	std::cout << "3. Remove cube		     ||"; std::cout << listActions(p, 2) << std::endl;
	std::cout << "4. Shuttle Flight            ||"; std::cout << listActions(p, 3) << std::endl;
	std::cout << "5. List City Data            ||"; std::cout << listActions(p, 4) << std::endl;
	std::cout<<  "6. Research Cure             ||" << std::endl;//expansion for later
	std::cout<<  "7. Share Knowledge " << std::endl;

	//listActions(p); //additional actions that are unique to each player are being shown here
	//I think have the above line print if the player chooses to in Use Profession Ability
	std::cout<<"8. List other things         ||" << std::endl;

	std::cout << "9. Save current game         ||" << std::endl;
	std::cout << "10. Load a different game    ||" << std::endl;
	std::cout<<"12.______________ " << std::endl;
	std::cout<<"What would you like to do: ";
	
}


void PandView::showPlayerRoleInfo(int playernum)//
{
	Playerchar temp = model.getPlayerInfo(playernum-1);
	std::cout << "Player role: " << temp.profName << std::endl;
	std::cout << "Role details: " << std::endl;
	listDescriptions(temp.profession);
	/*if (temp.profession == 0){
		if (temp.extracardFlag){
			std::cout << "Extra event card: " << temp.CPextracard.cardType << std::endl;
		}
		else{
			std::cout << "Extra event card: " << "None" << std::endl;
		}
	
	}*/
	
}
void PandView::showPlayerInfo(int playernum)
{
	std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "HoChiMinh City",
							"Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
							"Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
							"Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};
	Playerchar temp = model.getPlayerInfo(playernum);//changing to match controller call
	std::cout<<"Player name: " <<  temp.playerName << std::endl;
	std::cout<<"Player location: " << cityname[temp.location] << std::endl;
	std::cout << "Player Role: " << temp.profName << std::endl;


}


void PandView::showCubeLocations()//show all 4 types of cubes per city
{
	std::cout<<"This function will show infection cube location \n";
	city temp;
	char infectionColor[4] = {'R', 'G', 'B', 'Y'};

	for (int i = 0; i < 48; i++)
	{
		temp = model.getCityInfo(i);
		for(int j = 0; j < 4; j++)//traverse through different color cubes that may be stored in this city
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
		temp = model.getPlayerInfo(i);
		tempcity = model.getCityInfo(temp.location);
		std::cout<<"Player: "<<temp.playerName << "City: " << tempcity.cityName << std::endl;
	}
}
void PandView::showInfectionLevel()
{
	int temp = model.getInfectionRate();
	std::cout<<"Current Level of infection: " << temp<< std::endl;
}

void PandView::showDiscardedInfectionCards()
{
	std::cout<<"This function will show the cards that have been discarded \n";
}
void PandView::showPlayCard(playerCard card)
{
	std::cout<<card.cardType<<" \n";
	std::cout<<card.cardDescription<<std::endl;
}
void PandView::showInfectCard(infectionCard card)
{
	std::cout<<"Infect \n";
	std::cout<<card.cardDescription<<std::endl;
}

string PandView::listActions(int role,int line){
	if (role == 0){
		
		if (line == 1){ return "a. Store a discarded card";}
		if (line == 2){ return ""; }
		if (line == 3){ return ""; }
		if (line == 4){ return ""; }
	}
	if (role == 1){
		if (line == 1){return "a. Move a pawn next to another pawn";}
		if (line == 2){return "b. Move a pawn of another player";}
		if (line == 3){ return "to a city its nearby"; }
		if (line == 4){ return ""; }
	}
	if (role == 2){
		if (line == 1){return "Passive Abilities:";}
		if (line == 2){return "*When a city is treated,";}
		if (line == 3){ return "all cubes of the same color are treated"; }
		if (line == 4){ return "*Known cures are administered with no action cost"; }

	}
	if (role == 3){
		if (line == 1){ return "a. Build a research station";}
		if (line == 2){ return ""; }
		if (line == 3){ return ""; }
		if (line == 4){ return ""; }

	}
	if (role == 4){
		if (line == 1){ return "Passive Abilities:"; }
		if (line == 2){	return "*Prevents disease cube placemenets in the city";}
		if (line == 3){ return "and the ones surrounding"; }
		if (line == 4){ return ""; }

	}
	if (role == 5){
		if (line == 1){return "a. Give one of your cards to another player";}
		if (line == 2){ return ""; }
		if (line == 3){ return ""; }
		if (line == 4){ return ""; }
	}
	if (role == 6){
		if (line == 1){ return "Passive Abilities:"; }
		if (line == 2){	return  "*Needs only 4 cards of the same color to discover a cure";}
		if (line == 3){ return "to discover a cure"; }
		if (line == 4){ return ""; }
	}

}

void PandView::printCityColumns()
{
	for(int i = 0; i < 16; i++)
	{
		cout << left << setw(3) << i    << "  " << setw(20) << getCityName(i);
		cout << left << setw(3) << i+16 << "  " << setw(20) << getCityName(i+16);
		cout << left << setw(3) << i+32 << "  " << setw(20) << getCityName(i+32) << endl;
	}
	cout << endl;
}
void PandView::printResearchCenters()
{
		for(int i = 0; i < 16; i++)
        {
                cout << left << setw(2) << i    << "  " << setw(15) << getCityName(i);
				if(model.returnResearch(i) == 1){ cout << setw(5) << ":Yes" << '|';}
				else {cout << setw(5) << ":No" << '|';}

                cout << left << setw(3) << i+16 << "  " << setw(15) << getCityName(i+16);
				if(model.returnResearch(i+16) == 1){cout << setw(5) << ":Yes" << '|';}
				else {cout << setw(5) << ":No" << '|';}

                cout << left << setw(3) << i+32 << "  " << setw(16) << getCityName(i+32);
				if(model.returnResearch(i+32) == 1){ cout << setw(5) << ":Yes" << endl;}
				else {cout << setw(5) << ":No" << endl;}
		
		}
		cout << endl;

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

void PandView::showHowManyPlayerCardsLeft()
{
	int amt= model.getNumPlayCardsLeft();
	std::cout<<"There are " << amt << " play cards left \n";
}

void PandView::showPlayerHand(int playernum)
{
	Playerchar temp = model.getPlayerInfo(playernum);
	//Print cards in hand/////////////////////////////////////////
	cout << "Cards on hand:" << endl;
	//cout << "Color || Type || Name - Effect" << endl;

	for(int i = 0; i < 9; i++)
	{
		
		if(temp.cardsonhand[i].value != -1)
		{
			cout << "#" << i+1 << "    ";
			cout << temp.cardsonhand[i].color << " || ";
			cout << temp.cardsonhand[i].cardType << " || ";
			cout << temp.cardsonhand[i].cardDescription << endl;
		}
	}
	////////////////Hand print end////////////////////////////////
}


#endif