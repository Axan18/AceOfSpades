#include <string>
#include "player.hpp"
Pot::Pot(int pot)
{
	this->pot = pot;
}


Player::Player(std::string card1, std::string card2,int bettingValue, int money, int wholeBet) : hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet){}
	
int Player::betIncrease()
{
	bettingValue += 50;

	return wholeBet;
}
int Player::betDecrease()
{
	bettingValue -= 50;

	return wholeBet;
}
int Player::call(int highestBet, Pot& pot)
{
	bettingValue = highestBet;
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
