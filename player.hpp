#ifndef player_hpp
#define player_hpp
#include <string>
#include <SFML/Graphics.hpp>
class Pot
{
public:
    int pot;
    Pot(int pot);
};
class Player
{
private:
    int bettingValue, money, wholeBet;
    static int highestBet;
    static bool isRaised;
    std::string hand1, hand2;

    friend void mainScreen(sf::RenderWindow& window, Player player, sf::Sprite foldButton, sf::Sprite checkOrCallButton, sf::Sprite raiseButton, sf::Sprite moneyButton, sf::Sprite plusButton, sf::Sprite minusButton);
    friend class Bot;

public:
    Player();
    Player(std::string card1, std::string card2, int bettingValue, int money, int wholeBet);  
    int betIncrease();
    int betDecrease();
    int call(int highestBet, Pot& pot);
    int raise(int bettingValue, Pot& pot);
    int getBettingValue() const;
};
class Bot : public Player
{
public:
    Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet);
};
#endif
