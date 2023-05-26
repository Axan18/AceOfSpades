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
class AbstractPlayer
{
protected:

    static int highestBet;
    static bool isRaised;
    static int turn;


public:
    static bool getIsRaised();
    static int getHighestBet();
    static int getTurn();
    virtual int betIncrease()=0;
    virtual int betDecrease()=0;
    virtual int call(int highestBet, Pot& pot)=0;
    virtual int raise(Pot& pot)=0;
    virtual void check()=0;
    virtual void fold()=0;
    virtual int getBettingValue() const=0;
    virtual int getMoney() const=0;
    virtual int getWholeBet() const=0;
    virtual bool getIsActionTaken() const=0;
    virtual std::string getCard(int index) const=0;
};

class Player : public AbstractPlayer
{
private:

    int bettingValue, money, wholeBet;
    bool isActionTaken;
    std::string hand1, hand2;
    friend class Bot;

public:
    Player();
    Player(std::string card1, std::string card2, int bettingValue, int money, int wholeBet, bool isActionTaken);
    int betIncrease() override;
    int betDecrease() override;
    int call(int highestBet, Pot& pot) override;
    int raise(Pot& pot) override;
    void check() override;
    void fold() override;
    int getBettingValue() const override;
    int getMoney() const override;
    int getWholeBet() const override;
    bool getIsActionTaken() const override;
    std::string getCard(int index) const override;
};
class Bot : public AbstractPlayer, public Player
{
public:
    Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet);
    int betIncrease() override;
    int betDecrease() override;
    int call(int highestBet, Pot& pot) override;
    int raise(Pot& pot) override;
    void check() override;
    void fold() override;
    int getBettingValue() const override;
    int getMoney() const override;
    int getWholeBet() const override;
    bool getIsActionTaken() const override;
    std::string getCard(int index) const override;
    double calculateChance(deckOfCards commonCards, int turn); 
    double oddsCalculator(deckOfCards commonCards, int turn, std::string color1, std::string color2, int value1, int value2, deckOfCards tableCards); 
};
#endif
