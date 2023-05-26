#include <string>
#include "player.hpp"
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
int AbstractPlayer::highestBet = 0;
bool AbstractPlayer::isRaised = false;
int AbstractPlayer::turn = 1; 
Player::Player() : hand1(""), hand2(""), bettingValue(0), money(0), wholeBet(0), isActionTaken(false) {}
Player::Player(std::string card1, std::string card2,int bettingValue, int money, int wholeBet, bool isActionTaken) : hand1(card1),hand2(card2), bettingValue(bettingValue), money(money), wholeBet(wholeBet), isActionTaken(isActionTaken){} 
bool Player::getIsRaised()
{
	return isRaised;
}
int Player::getHighestBet()
{
	return highestBet;
}
int Player::getTurn()
{
	return turn; 
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
	pot.setPot(bettingValue); 
	wholeBet+= bettingValue;
	turn++;
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
	turn++;
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
Bot::Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet) : Player(card1, card2, bettingValue, money, wholeBet, isActionTaken)  
{
	// pozosta³e pola klasy Bot mo¿na zainicjowaæ tutaj
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

int AbstractPlayer::betIncrease()
{
	return 0;
}
