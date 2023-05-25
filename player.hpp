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
    static int turn;
    bool isActionTaken;
    std::string hand1, hand2;
    friend class Bot;

public:
    Player();
    Player(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, bool isActionTaken);
    static void highestBetInitialization(int value);
    static void isRaisedInitialization(bool value);
    static void turnInitialization(int value);
    static bool getIsRaised() ;
    static int getHighestBet();
    static int getTurn();
    int betIncrease();
    int betDecrease();
    int call(int highestBet, Pot& pot);
    int raise(Pot& pot);
    void check();
    void fold(); 
    int getBettingValue() const;
    int getMoney() const;
    int getWholeBet() const;
    bool getIsActionTaken() const;
    std::string getCard(int index) const;
};
class Bot : public Player
{
public:
    Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet);
};
#endif
