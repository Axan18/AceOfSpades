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
    static bool getIsRaised() ;
    static int getHighestBet();
    static int getTurn();
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
class Bot : public Player
{
public:
    Bot(std::string card1, std::string card2, int bettingValue, int money, int wholeBet);
};
#endif
