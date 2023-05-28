#include "table.hpp"
#include "cards.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <stack>
#include <string>
#include <iostream>

int main()
{
    sf::Music music; 
    try
    {
        if (!music.openFromFile("AoS.flac"))
        {
            throw std::runtime_error("Failed to open sound file");
        }
        music.setVolume(10);
        music.play(); 
    }
    catch (const std::exception& e)
    {
        // Obs³uga b³êdu
        std::cout << "Music error " << e.what() << std::endl;
        // Dodatkowe dzia³ania naprawcze lub zakoñczenie programu
    }
    int ending = 0;
    double playerBest;
    double bot1Best;
    double bot2Best;
    sf::Sprite foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton; //buttons for main screen
    sf::Texture foldTexture, checkOrCallTexture, raiseTexture, plusTexture, minusTexture;
    buttons(foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton, foldTexture, checkOrCallTexture, raiseTexture, plusTexture, minusTexture, Player::getIsRaised());
    deckOfCards cardDeck;
    cardDeck.shuffleDeck();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ace Of Spades");
    window.setFramerateLimit(60); 
    Pot gamePot(15);
    AbstractPlayer* abstractPlayer= new Player(cardDeck[0],cardDeck[3], 15, 1000, 15, false);
    Player* player = dynamic_cast<Player*>(abstractPlayer);
    AbstractPlayer* abstractBot1 = new Bot(cardDeck[1], cardDeck[4], 15, 1000, 15); 
    Bot* bot1 = dynamic_cast<Bot*>(abstractBot1);   
    AbstractPlayer* abstractBot2 = new Bot(cardDeck[2], cardDeck[6], 15, 1000, 15);
    Bot* bot2 = dynamic_cast<Bot*>(abstractBot2);  
    for (int i = 0; i < 6; i++)
    {
        cardDeck.erase(cardDeck.begin());
	}
    deckOfCards commonCards;
    commonCards.clear(); 
    for (int i = 0; i < 5; i++)
    {
        commonCards.push_back(cardDeck[i]);
    }
    bool showStartScreen = true; 
    while (window.isOpen())
    {
        sf::Event action; 

        while (window.pollEvent(action))
        {
            if (action.type == sf::Event::Closed)
                window.close();
            if (action.type == sf::Event::KeyPressed && action.key.code == sf::Keyboard::Escape)
                window.close();
            if (showStartScreen == false && player->getTurn()<5)
            {
                auto mousePosition = sf::Mouse::getPosition(window);
                auto translatedPosition = window.mapPixelToCoords(mousePosition); 

                if (action.type == sf::Event::MouseButtonPressed&& action.mouseButton.button == sf::Mouse::Left && plusButton.getGlobalBounds().contains(translatedPosition)&&(player->getBettingValue()+50)<=player->getMoney() && player->getIsActionTaken() == false)
                {
                    player->betIncrease();
                }
                if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && minusButton.getGlobalBounds().contains(translatedPosition)&&player->getBettingValue()>=50 && player->getIsActionTaken() == false)
                {
                    player->betDecrease();
                }
                if (AbstractPlayer::getIsRaised() == true&&player->getIsActionTaken()==false) 
                {
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && checkOrCallButton.getGlobalBounds().contains(translatedPosition)&&player->getMoney()>=Player::getHighestBet()&& player->getBettingValue() <= player->getMoney())
                    {
                        player->call(Player::getHighestBet(),gamePot);
                    }
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && raiseButton.getGlobalBounds().contains(translatedPosition)&& player->getBettingValue()>Player::getHighestBet()&&player->getBettingValue()<=player->getMoney())
                    {
                        player->raise(gamePot);
                    }
                } 
                if (AbstractPlayer::getIsRaised() == false && player->getIsActionTaken() == false ) 
                {
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && checkOrCallButton.getGlobalBounds().contains(translatedPosition))
                    {
                        player->check();
                    }
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && raiseButton.getGlobalBounds().contains(translatedPosition) && player->getBettingValue() > Player::getHighestBet()&& player->getBettingValue() <= player->getMoney())
                    { 
                        player->raise(gamePot);
                    }
                }
                if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && foldButton.getGlobalBounds().contains(translatedPosition) && player->getIsActionTaken() == false)
                {
					player->fold();
				}

                if (player->getIsActionTaken() == true)
                {
                    if(bot1->getIsFolded()!=true)
                    bot1->makeDecision(commonCards, AbstractPlayer::getTurn(), gamePot); 
                    if (bot2->getIsFolded() != true)
                    bot2->makeDecision(commonCards, AbstractPlayer::getTurn(), gamePot);
                    AbstractPlayer::raiseReset();
                    AbstractPlayer::turnIncrementer();
                    player->actionReset();
                }
            }
            else if((showStartScreen == false && player->getTurn() == 5))
            {
              playerBest=player->bestHand(commonCards);
              bot1Best=bot1->bestHand(commonCards);
              bot2Best=bot2->bestHand(commonCards);

              if (playerBest > bot1Best && playerBest > bot2Best)
              {
                  ending = 1;
                  AbstractPlayer::turnIncrementer(); 
              }
              else
              {
                  ending = 2;
                  AbstractPlayer::turnIncrementer(); 
              }
            }
        }
        if (showStartScreen)
        {
            startScreen(window, showStartScreen);
        }
        else
        {
            if(ending==1)
                endingScreen(window, "images/win.jpg");
            else if(ending==2)
                endingScreen(window, "images/lose.jpg");
            else
                mainScreen(window, *player,*bot1,*bot2, foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton, gamePot, commonCards, AbstractPlayer::getTurn());

            std::cout<<bot1->calculateChance(commonCards,player->getTurn())<<" //1" << std::endl; 
            std::cout << bot2->calculateChance(commonCards, player->getTurn())<<" //2" << std::endl;
        }
        window.display();
    }
    return 0;
}