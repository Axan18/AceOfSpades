#include "table.hpp"
#include "cards.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <stack>
#include <string>
#include <iostream>

int main()
{
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
    Bot bot1(cardDeck[1], cardDeck[4], 15, 1000, 15);
    Bot bot2(cardDeck[2], cardDeck[5], 15, 1000, 15);
    for (int i = 0; i < 6; i++)
    {
        cardDeck.erase(cardDeck.begin());
	}
    deckOfCards commonCards;
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
                if (Player::getIsRaised() == true&&player->getIsActionTaken()==false && player->getTurn()<5)
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
                if (Player::getIsRaised() == false && player->getIsActionTaken() == false )
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
                    //Bot actions
                }
            }
            //else
            //{
            //    //ending screen
            //}
        }
        if (showStartScreen)
        {
            startScreen(window, showStartScreen);
        }
        else
        {
            mainScreen(window, *player,bot1,bot2, foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton, gamePot, commonCards, AbstractPlayer::getTurn()); 
            std::cout<<player->getTurn()<<std::endl;
        }
        window.display();
       //endingScreen(window, "images/win.jpg");
    }
    return 0;
}