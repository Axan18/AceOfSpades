#include <string>
#include "player.hpp"
#include "cards.hpp"
#include <iostream>
#include <algorithm>
int Pot::getPot() const
{
	return pot;
}
void Pot::setPot(int value)
{
	pot += value;
}
Pot::Pot(int pot) {
	this->pot = pot;
}
//######## AbstractPlayer ###########################
int AbstractPlayer::highestBet = 0;
bool AbstractPlayer::isRaised = false;
int AbstractPlayer::turn = 1; 
AbstractPlayer::AbstractPlayer(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, bool isActionTaken)
	:hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), isActionTaken(isActionTaken) 
{
	// Tutaj mo¿esz umieœciæ dodatkow¹ logikê konstruktora
}
bool AbstractPlayer::getIsRaised()
{
	return isRaised;
}

int AbstractPlayer::getHighestBet()
{
	return highestBet;
}

int AbstractPlayer::getTurn()
{
	return turn;
}

void AbstractPlayer::turnIncrementer()
{
	turn++;
}
void AbstractPlayer::raiseReset()
{
	isRaised = false;
}
double AbstractPlayer::bestHand(deckOfCards tableCards) const
{
	std::string color1 = this->getCard(1).substr(0, 1);
	std::string color2 = this->getCard(2).substr(0, 1);
	int value1 = stoi(this->getCard(1).substr(1, 2));
	int value2 = stoi(this->getCard(2).substr(1, 2));

	int stop = 5;
	double highCard = 0;
	double pair = 0;
	double twoPair = 0;
	double threeOfAKind = 0;
	double straight = 0;
	double flush = 0;
	double fullHouse = 0;
	double fourOfAKind = 0;
	double straightFlush = 0;
	double royalFlush = 0;
	double cardsLeft =45;
	std::vector< Card > cards;
	cards.push_back(Card(value1, color1));
	cards.push_back(Card(value2, color2));
	for (int i = 0; i < stop; i++)
		cards.push_back(Card(stoi(tableCards[i].substr(1, 2)), tableCards[i].substr(0, 1)));
	std::sort(cards.begin(), cards.end());
	//high card
	{
		int higherCard = std::max(value1, value2);
		highCard = higherCard;
	}
	//pair \ two of pair
	int pairValue[2] = { 0,0 };
	int pairCounter = 0;
	for (int i = cards.size() - 1; 0 < i; i--)
	{
		if (cards[i].value == cards[i - 1].value)
		{
			pairValue[pairCounter] = cards[i].value;
			i--;
			pairCounter++;
		}
	}
	switch (pairCounter)
	{
	case 1:
		pair = pairValue[0];
		break;
	case 2:
		twoPair = std::max(pairValue[0],pairValue[1]);
		break;
	default: pair = 0; break;
	}
	//three of a kind
	int threeValue;
	for (int i = cards.size() - 1; 1 < i; i--)
	{
		if (cards[i].value == cards[i - 1].value && cards[i].value == cards[i - 2].value)
		{

			threeValue = cards[i].value;
			threeOfAKind = threeValue * 0.1;
		}
	}
	//straight	
	int straightValue = 0;
	int counter=0;
	for (int i = 0; i < cards.size()-1; i++)
	{
		if (cards[i].value + 1 == cards[i+1].value)
		{
			counter++;

		}
		if (counter == 5)
		{
			straightValue = cards[i+1].value; 
			break;
		}
	}
	straight = straightValue * 0.15;
	//flushes
	int counterFlush = 0;
	std::vector <int> suitCounts(4, 0);
	for (const Card& card : cards) {
		if (card.suit == "S")
			suitCounts[0]++;
		else if (card.suit == "H")
			suitCounts[1]++;
		else if (card.suit == "D")
			suitCounts[2]++;
		else if (card.suit == "C")
			suitCounts[3]++;
	}
	if (suitCounts[0] >= 5 || suitCounts[1] >= 5 || suitCounts[2] >= 5 || suitCounts[3] >= 5)
	{
		for (int i = 0; i < cards.size() - 1; i++) 
		{
			if (cards[i].value + 1 == cards[i + 1].value) 
			{
				counterFlush++; 

			}
			if (counterFlush == 5) 
			{
				straightFlush = cards[i + 1].value;   
				if(cards[i+1].value==14)
					royalFlush = 4.5; 
			}
		}
		if(counterFlush!=5)
			flush = 1; 
	}
	//full
	if (threeOfAKind != 0 && pairCounter == 1 && pairValue[0] != threeValue)
		fullHouse = threeOfAKind; 
	//quads
	for (int i = cards.size() - 1; 2 < i; i--)
	{
		if (cards[i].value == cards[i - 1].value && cards[i].value == cards[i - 2].value && cards[i].value == cards[i - 3].value)
		{
			fourOfAKind = cards[i-2].value;
		}
	}
	if(royalFlush!=0)
		return 10;
	else if (straightFlush != 0)
		return 9+(straightFlush * 0.01);
	else if (fourOfAKind != 0)
		return 8 + (fourOfAKind * 0.01); 
	else if (fullHouse != 0)
		return 7+(fullHouse * 0.01); 
	else if (flush != 0)
		return 6+(highCard * 0.01); 
	else if (straight != 0)
		return 5+(straightValue * 0.01);
	else if (threeOfAKind != 0)
		return 4+(threeOfAKind * 0.01);
	else if (twoPair != 0)
		return 3+(twoPair * 0.01);
	else if (pair != 0)
		return 2+(pairValue[0] * 0.01);
	else
		return 1+(highCard*0.01);
}
//######## Player ######################################
Player::Player(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, bool isActionTaken) 
	: hand1(card1), hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), isActionTaken(isActionTaken), 
	AbstractPlayer(card1, card2, bettingValue, money, wholeBet, isActionTaken) { 
	// Inicjalizacja pól specyficznych dla Player
}
int Player::getMoney() const
{
	return money; 
}
int Player::betIncrease()
{
	bettingValue += 50;	
	return bettingValue;
}
int Player::betDecrease()
{
	bettingValue -= 50;
	
	return bettingValue; 
}
int Player::getBettingValue() const 
{
	return bettingValue; 
}
int Player::call(int highestBet, Pot& pot)
{
	bettingValue = highestBet;
	money -= bettingValue;
	pot.setPot(bettingValue); 
	wholeBet+= bettingValue;
	isActionTaken = true;  
	return bettingValue;
}

void Player::raise(Pot& pot)
{
	money -= bettingValue;
	pot.setPot(bettingValue);
	wholeBet+= bettingValue;
	highestBet = bettingValue;
	AbstractPlayer::isRaised = true; 
	isActionTaken = true;
}
void Player::check()
{
	isActionTaken = true;
}

void Player::fold()
{
	isFolded= true;
	isActionTaken = true;
}
std::string Player::getCard(int index) const
{
	if (index == 1)
		return hand1;
	else
		return hand2;
}
void Player::actionReset()
{
	isActionTaken = false;
}
int Player::getWholeBet() const
{
	return wholeBet;
}
bool Player::getIsActionTaken() const
{
	return isActionTaken;
}
bool Player::getIsFolded() const
{
	return isFolded;
}
//######## Bot ######################################
int Bot::getMoney() const
{
	return money;
}
int Bot::betIncrease()
{
	bettingValue += 50;
	return bettingValue;
}
int Bot::betDecrease()
{
	bettingValue -= 50;

	return bettingValue;
}
int Bot::getBettingValue() const
{
	return bettingValue;
}
int Bot::call(int highestBet, Pot& pot)
{
	bettingValue = highestBet;
	money -= bettingValue;
	pot.setPot(bettingValue);
	wholeBet += bettingValue;
	return bettingValue;
}
void Bot::raise(Pot& pot)
{
	money -= bettingValue;
	pot.setPot(bettingValue);
	wholeBet += bettingValue;
	highestBet = bettingValue;
	AbstractPlayer::isRaised = true; 
}
void Bot::check()
{

}
void Bot::fold()
{
	isFolded = true; 
}
std::string Bot::getCard(int index) const
{
	if (index == 1)
		return hand1;
	else
		return hand2;
}
int Bot::getWholeBet() const
{
	return wholeBet;
}
bool Bot::getIsActionTaken() const
{
	return isActionTaken;
}
bool Bot::getIsFolded() const 
{
	return isFolded;
}
void Bot::makeDecision(deckOfCards commonCards, int turn, Pot& gamePot)  
{
	double chance = calculateChance(commonCards, turn); 
	switch (turn)
	{
		case 1:
			if (chance >= 0.6)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + (log(2 * chance) / 4) * money)
				{
				this->bettingValue = AbstractPlayer::getHighestBet() + log(2 * chance) / 4;
				}
				else
				{
					this->bettingValue = this->getMoney(); 
				}
				this->raise(gamePot); 
			}
			else if (chance > 0.4&&chance <0.6) 
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + 100)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + 100; 
				}
				else
				{
					this->bettingValue = this->getMoney(); 
				}
				this->call(AbstractPlayer::getHighestBet(), gamePot); 
			}
			else if(chance<=0.4 &&chance >=0.25)
			{
				if (AbstractPlayer::getIsRaised() == true)
				{
					this->call(AbstractPlayer::getHighestBet(), gamePot);
				}
				else
				{
					this->check();
				}
			}
			else
				this->fold();
			break;
		case 2:
			if (chance >= 1.2)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + (log(2 * chance) / 4) * money)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + log(2 * chance) / 4;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->raise(gamePot);
			}
			else if (chance > 0.9 && chance < 1.2)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + 200)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + 200;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->call(AbstractPlayer::getHighestBet(), gamePot);
			}
			else if (chance > 0.7 && chance <= 0.9)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + 100)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + 100;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->call(AbstractPlayer::getHighestBet(), gamePot);
			}
			else if (chance <= 0.7 && chance >= 0.45)
			{
				if (AbstractPlayer::getIsRaised() == true)
				{
					this->call(AbstractPlayer::getHighestBet(), gamePot);
				}
				else
				{
					this->check();
				}
			}
			else
				this->fold();
			break;
		case 3:
			if (chance >= 1.2)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + (log(2 * chance) / 4) * money)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + log(2 * chance) / 4;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->raise(gamePot);
			}
			else if (chance > 0.9 && chance < 1.2)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + 200)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + 200;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->call(AbstractPlayer::getHighestBet(), gamePot);
			}
			else if (chance > 0.7 && chance <= 0.9)
			{
				if (this->getMoney() > AbstractPlayer::getHighestBet() + 100)
				{
					this->bettingValue = AbstractPlayer::getHighestBet() + 100;
				}
				else
				{
					this->bettingValue = this->getMoney();
				}
				this->call(AbstractPlayer::getHighestBet(), gamePot);
			}
			else if (chance <= 0.7 && chance >= 0.45)
			{
				if (AbstractPlayer::getIsRaised() == true)
				{
					this->call(AbstractPlayer::getHighestBet(), gamePot);
				}
				else
				{
					this->check();
				}
			}
			else
				this->fold();
			break;
		default: this->fold(); 
	}
}
double Bot::calculateChance(deckOfCards commonCards, int turn) 
{ 
	double chance = 0;
	std::string color1 = this->getCard(1).substr(0, 1);
	std::string color2 = this->getCard(2).substr(0, 1);
	int value1 = stoi(this->getCard(1).substr(1, 2));
	int value2 = stoi(this->getCard(2).substr(1, 2)); 
	switch (turn)
	{
	case 1:
		if (value1 == value2)
		{
			chance += 0.51;
			chance += ((pow(13, value1) - pow(2, value2)) / pow(9.8, value1)) * 0.01;
		}
		else
		{
			if (color1 == color2)
			{
				chance += 0.15;
				if (std::max(value1, value2) < 7)
					chance += 0.3;
				else if (std::max(value1, value2) < 10)
					chance += 0.4;
				else
					chance += 0.5;
			}
			else
			{
				if (std::max(value1, value2) < 7)
					chance += 0.15;
				else if (std::max(value1, value2) < 10)
					chance += 0.25;
				else
					chance += 0.45;
			}
		}
		return chance;
	case 2:
		return oddsCalculator(turn, color1, color2, value1, value2, commonCards);  
		break;
	case 3:
		return oddsCalculator(turn, color1, color2, value1, value2, commonCards);
		break;
	default: return 0;
	}
}
double Bot::oddsCalculator( int turn, std::string color1, std::string color2, int value1, int value2, deckOfCards tableCards)
{
	int stop = 0;
	if (turn == 1)
		stop = 3;
	else if (turn == 2)
		stop = 4;
	else if (turn == 3)
		stop = 5;
	double highCard = 0;
	double pair = 0;
	double twoPair = 0;
	double threeOfAKind = 0;
	double straight = 0;
	double flush = 0;
	double fullHouse = 0;
	double fourOfAKind = 0;
	double straightFlush = 0;
	double royalFlush = 0;
	double cardsLeft;
	switch (turn)
	{
	case 2: cardsLeft = 47; break;
	case 3: cardsLeft = 46; break;
	case 4: cardsLeft = 45; break;
	}
	std::vector< Card > cards;
	cards.push_back(Card(value1, color1)); 
	cards.push_back(Card(value2, color2));
	for (int i = 0; i < stop; i++)
		cards.push_back(Card(stoi(tableCards[i].substr(1,2)),tableCards[i].substr(0,1)));
	std::sort(cards.begin(), cards.end());
	//high card
	{
		int higherCard = std::max(value1, value2);
		highCard = higherCard * 0.01;
		highCard += 1 / ((cardsLeft - (14 - higherCard)) / (14 - higherCard));
	}
	//pair \ two of pair
	int pairValue[2] = { 0,0 };
	int pairCounter = 0;
	for (int i=cards.size()-1; 0<i;i--)
	{
		if (cards[i].value == cards[i - 1].value)
		{
			pairValue[pairCounter] = cards[i].value;
			i--; 
			pairCounter++; 
		}
	}
	switch (pairCounter)
	{
	case 0: 
		pair = 1 / (((cardsLeft - 3*cards.size())/(3 * cards.size()))+1);
		threeOfAKind =  1 /(1+(((cardsLeft - 3 * cards.size()) / (3 * cards.size()))  *  ((cardsLeft-1 - 2) / 2)));
		break;
	case 1:  
		pair = pairValue[0] * 0.07;
		threeOfAKind = 1 / (1+((cardsLeft - 2) / 2));
		if (turn == 1)
		{
			threeOfAKind += 1 / (1 + (((cardsLeft - 3 * cards.size()) / (3 * cards.size())) * ((cardsLeft - 1 - 2) / 2)));
		}
		break;
	case 2: 
		pair = pairValue[0] * 0.07;
		pair += pairValue[1] * 0.07;
		threeOfAKind = 1 / (1 + (cardsLeft - 4) / 4);
		break;
	default: pair = 0; break;
	}
	//three of a kind
	int threeValue=0;
	for (int i = cards.size() - 1; 1 < i; i--)
	{
		if (cards[i].value == cards[i - 1].value && cards[i].value == cards[i - 2].value)
		{

				threeValue = cards[i].value; 
				threeOfAKind = threeValue * 0.1;
		}
	}
	//straight	
	int counterFlush = 0;
	std::vector <int> suitCounts(4, 0);
	for (const Card& card : cards) {
		if (card.suit == "S")
			suitCounts[0]++;
		else if (card.suit == "H")
			suitCounts[1]++;
		else if (card.suit == "D")
			suitCounts[2]++;
		else if (card.suit == "C")
			suitCounts[3]++;
	}
	if (suitCounts[0] >= 5 || suitCounts[1] >= 5 || suitCounts[2] >= 5 || suitCounts[3] >= 5)
	{
		for (int i = 0; i < cards.size() - 1; i++) 
		{
			if (cards[i].value + 1 == cards[i + 1].value) 
			{
				counterFlush++; 
			}
			if (counterFlush == 5) 
			{
				straightFlush = 3.5;   
				if(cards[i+1].value==13)
					royalFlush = 4.5; 
			}
		}
		if(counterFlush!=5)
			flush = 2.2; 
	}
	//full
	if(threeOfAKind!=0 && pairCounter==1 && pairValue[0]!=threeValue)
		fullHouse = 2.7;
	//quads
	for (int i = cards.size() - 1; 2 < i; i--)
	{
		if (cards[i].value == cards[i - 1].value && cards[i].value == cards[i - 2].value && cards[i].value == cards[i - 3].value)
		{
			fourOfAKind = 3;
		}
	}
	return highCard + pair + twoPair + threeOfAKind + straight + flush + fullHouse + fourOfAKind + straightFlush + royalFlush; 
} 
Bot::Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet)
	: hand1(card1), hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), 
	AbstractPlayer(card1, card2, bettingValue, money, wholeBet, isActionTaken) { }