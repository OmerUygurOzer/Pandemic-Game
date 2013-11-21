#include <C:/CxxTest/cxxtest/TestSuite.h>
#include <model.h>

// The function to test
void mergeInfectionDecks(deque<infectionCard> &deckA, deque<infectionCard> &deckB) // puts deckA on top of deckB
{
	// remove cards from bottom of deckA and put on top of deckB until none remain in deckA
	int cardAmount = deckA.size();
	infectionCard temp;
	
	for(int i = 0; i < cardAmount; i++) // repeat for how many cards are in deckA
	{
		temp = deckA.back(); // set temp as card on bottom deckA
		deckB.push_front(temp); // put temp on top of deckB
		deckA.pop_back(); // remove temp from deckA
	}
	
}

class MyTestSuite1 : public CxxTest::TestSuite
{
public:
	std::deque<infectionCard> infectionDeck; // infection draw deck
	std::deque<infectionCard> discardInfectionDeck; // infection discard deck

	void fillTestDecks() // fills the discard and draw decks for testing
	{
		std::string cityname[48] = {"Algiers", "Atlanta", "Baghdad", "Bangkok", "Beijing", "Bogota", "Buenos Aires", "Cairo", "Chennai", "Chicago", "Delhi", "Essen", "HoChiMinh City",
                            "Hong Kong", "Istanbul", "Jakarta", "Johannesburg", "Karachi", "Khartoum", "Kinshasa", "Kolkata", "Lagos", "Lima", "London", "Los Angeles", "Madrid",
                            "Manila", "Mexico City", "Miami", "Milan", "Moscow", "Mumbai", "New York", "Osaka", "Paris", "Riyadh", "San Francisco", "Santiago",
                            "Sao Paulo", "Seoul", "Shanghai", "St. Petersburg", "Sydney", "Taipei", "Tehran", "Tokyo", "Toronto", "Washington"};

		infectionCard infectCard;
		for(int i = 0; i<30; i++)  //fill draw deck with first 30 cards (top of deck is city 29 bottom is city 0)
		{
			infectCard.cardType = "City";
			infectCard.cardDescription = cityname[i];
			infectCard.city = i;
			infectCard.color = 0;  // color not important
			infectionDeck.push_front(infectCard);//add onto infectiondeck after info populated
		}
		for(int i = 30; i<48; i++)  // fill discard deck with final 18 cards (top of deck is city 47, bottom is city 30)
		{
			infectCard.cardType = "City";
			infectCard.cardDescription = cityname[i];
			infectCard.city = i;
			infectCard.color = 0;  // color not important
			discardInfectionDeck.push_front(infectCard);//add onto infectiondeck after info populated 
		}

	}

    void testDeckSizes(void) // test to make sure deck sizes are correct after merge
    {
		fillTestDecks(); // populate the decks
		TS_ASSERT_EQUALS(infectionDeck.size(), 30); // before merge should have 30 cards in draw deck
		TS_ASSERT_EQUALS(discardInfectionDeck.size(), 18); // before merge should have 18 cards in discard deck
		mergeInfectionDecks(discardInfectionDeck, infectionDeck); // puts discardInfectdionDeck on top of infectionDeck
		TS_ASSERT_EQUALS(infectionDeck.size(), 48); // after merge draw deck should have all 48 cards
		TS_ASSERT_EQUALS(discardInfectionDeck.size(), 0); // after merge discard deck should be empty
    }

	void testTopCard(void) // test to make sure top card is correct
	{
		infectionCard testCard1, testCard2; // cards to test with
		fillTestDecks(); // populate the decks
		testCard1 = discardInfectionDeck.front(); // set testCard1 as card on top of discard deck
		mergeInfectionDecks(discardInfectionDeck, infectionDeck); // puts discardInfectdionDeck on top of infectionDeck
		testCard2 = infectionDeck.front(); // set testCard2 as card on top of merged infectionDeck
		TS_ASSERT_EQUALS(testCard1.city, testCard2.city); // top of discard should now be on top of draw deck
	}

	void testCardPositions(void) // more complete test to test that all cards are in correct position
	{
		infectionCard testCard; // card to test with
		fillTestDecks(); // populate the decks
		mergeInfectionDecks(discardInfectionDeck, infectionDeck); // puts discardInfectdionDeck on top of infectionDeck
		for(int i = 0; i<48; i++) // go through cards of draw deck
		{
			testCard = infectionDeck.back(); // set as bottom card
			infectionDeck.pop_back(); // remove bottom card
			TS_ASSERT_EQUALS(testCard.city, i); // should be equal to i
		}
	}
};