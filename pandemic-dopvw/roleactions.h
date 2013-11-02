/*#include <iostream>

class RoleActions{ //What each player can do with their roles. Role Action stubs
	int player;
	int profession; 
	
	public:
		
		void setProfession(int x){
			profession = x;
		};
    
    int getProfession(){
    return profession;
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
		/*void listActions(){
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
		
		
	
};*/
