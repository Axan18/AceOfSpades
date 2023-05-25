#ifndef player_hpp
#define player_hpp
#include <string>
#include <SFML/Graphics.hpp>
class Pot
{
    int pot;
public:
    int getPot() const;
    void setPot(int value);
    Pot(int pot);
};
class Player
{
private:
    int bettingValue, money, wholeBet;
    static int highestBet;
    static bool isRaised;
    int turn;
    std::string hand1, hand2;

    friend void mainScreen(sf::RenderWindow& window, Player player, sf::Sprite foldButton, sf::Sprite checkOrCallButton, sf::Sprite raiseButton, sf::Sprite moneyButton, sf::Sprite plusButton, sf::Sprite minusButton);
    friend class Bot;

public:
    Player();
    Player(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, int turn);
    static void highestBetInitialization(int value);
    static void isRaisedInitialization(bool value);
    static bool getIsRaised() ;
    static int getHighestBet();
    int betIncrease();
    int betDecrease();
    int call(int highestBet, Pot& pot);
    int raise(Pot& pot);
    void check();
    void fold(); 
    int getBettingValue() const;
    int getMoney() const;
    int getWholeBet() const;
    std::string getCard(int index) const;
};
class Bot : public Player
{
public:
    Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, int turn);
};
#endif
