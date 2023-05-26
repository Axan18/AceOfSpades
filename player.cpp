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
//######## Player ######################################
Player::Player() : hand1(""), hand2(""), bettingValue(0), money(0), wholeBet(0), isActionTaken(false) {}
Player::Player(std::string card1, std::string card2,int bettingValue, int money, int wholeBet, bool isActionTaken) : hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), isActionTaken(isActionTaken){} 

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
	//turn++;
	isActionTaken = true;  
	return bettingValue;
}

int Player::raise(Pot& pot)
{
	money -= bettingValue;
	pot.setPot(bettingValue);
	wholeBet+= bettingValue;
	highestBet = bettingValue;
	isRaised = true;
	//turn++;
	isActionTaken = true; 
	return 0;
}
void Player::check()
{
	turn++;
	isActionTaken = true;
}

void Player::fold()
{
	turn = 0;
	isActionTaken = true; 
}
std::string Player::getCard(int index) const
{
	if(index==1)
		return hand1;
	else
		return hand2;
}
int Player::getWholeBet() const
{
	return wholeBet;
}
bool Player::getIsActionTaken() const
{ 
	return isActionTaken;
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
	turn++;
	isActionTaken = true;
	return bettingValue;
}

int Bot::raise(Pot& pot) 
{
	money -= bettingValue;
	pot.setPot(bettingValue);
	wholeBet += bettingValue;
	highestBet = bettingValue;
	isRaised = true;
	turn++;
	isActionTaken = true;
	return 0;
}
void Bot::check()
{
	turn++;
	isActionTaken = true;
}

void Bot::fold()
{
	turn = 0;
	isActionTaken = true;
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
double Bot::calculateChance(deckOfCards commonCards, int turn)
{ 
	double chance = 0;
	std::string color1 = hand1.substr(0, 1);
	std::string color2 = hand2.substr(0, 1);
	int value1 = stoi(hand1.substr(1, 2));
	int value2 = stoi(hand2.substr(1, 2));
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
		

	}
		
	
}
double Bot::oddsCalculator(deckOfCards commonCards, int turn, std::string color1, std::string color2, int value1, int value2, deckOfCards tableCards)
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
	}
	//pair


	





}
Bot::Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet) : Player(card1, card2, bettingValue, money, wholeBet, isActionTaken)
{
	// pozosta³e pola klasy Bot mo¿na zainicjowaæ tutaj
}
