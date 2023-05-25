#include <string>
#include "player.hpp"
Pot::Pot(int pot)
{
	this->pot = pot;
}
Player::Player(std::string card1, std::string card2,int bettingValue, int money, int wholeBet, int turn) : hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), turn(turn){} 
void Player::highestBetInitialization(int value)
{
	highestBet = value;  
}
void Player::isRaisedInitialization(bool value)
{
	isRaised = value;
}
bool Player::getIsRaised()
{
	return isRaised;
}
int Player::getHighestBet()
{
	return highestBet;
}
int Player::getMoney() const
{
	return money; 
}
int Player::betIncrease()
{
	if((bettingValue+50)<=money)
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
	pot.pot += bettingValue;
	wholeBet+= bettingValue;
	turn++;
	return bettingValue;
}
int Player::raise(Pot& pot)
{
	money -= bettingValue;
	pot.pot += bettingValue; 
	wholeBet+= bettingValue;
	isRaised = true;
	turn++;
	return 0;
}
void Player::check()
{
	turn++;
}

Bot::Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, int turn) : Player(card1, card2, bettingValue, money, wholeBet, turn) 
{
	// pozosta³e pola klasy Bot mo¿na zainicjowaæ tutaj
}


