#include <string>
#include "player.hpp"
Pot::Pot(int pot)
{
	this->pot = pot;
}
Player::Player(std::string card1, std::string card2,int bettingValue, int money, int wholeBet) : hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet){} 
	
int Player::betIncrease()
{
	if((bettingValue+50)<=money)
	bettingValue += 50;	
	return bettingValue;
}
int Player::betDecrease()
{
	if(bettingValue>=50)
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
	return bettingValue;
}
int Player::raise(int bettingValue,Pot& pot)
{
	return 0;
}

Bot::Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet) : Player(card1, card2, bettingValue, money, wholeBet)
{
	// pozosta³e pola klasy Bot mo¿na zainicjowaæ tutaj
}


