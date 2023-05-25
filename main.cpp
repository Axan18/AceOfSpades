#include "table.hpp"
#include "cards.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <stack>
#include <string>
#include <iostream>
int Player::highestBet = 0;
bool Player::isRaised = false;
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
    Player player(cardDeck[0],cardDeck[3], 15, 1000, 15,0);
    Bot bot1(cardDeck[1], cardDeck[4], 15, 1000, 15,0);
    Bot bot2(cardDeck[2], cardDeck[5], 15, 1000, 15,0);

    for (int i = 0; i < 6; i++)
    {
        cardDeck.erase(cardDeck.begin());
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
            if (showStartScreen == false)
            {
                auto mousePosition = sf::Mouse::getPosition(window);
                auto translatedPosition = window.mapPixelToCoords(mousePosition); 

                if (action.type == sf::Event::MouseButtonPressed&& action.mouseButton.button == sf::Mouse::Left && plusButton.getGlobalBounds().contains(translatedPosition)&&(player.getBettingValue()+50)<=player.getMoney())   
                {
                    player.betIncrease();
                }
                if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && minusButton.getGlobalBounds().contains(translatedPosition)&&player.getBettingValue()>=50)
                {
                    player.betDecrease();
                }
                if (Player::getIsRaised() == true)
                {
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && checkOrCallButton.getGlobalBounds().contains(translatedPosition)&&player.getMoney()>=Player::getHighestBet()&& player.getBettingValue() <= player.getMoney()) 
                    {
                        player.call(Player::getHighestBet(),gamePot);
                    }
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && raiseButton.getGlobalBounds().contains(translatedPosition)&& player.getBettingValue()>Player::getHighestBet()&&player.getBettingValue()<=player.getMoney())
                    {
                        player.raise(gamePot);
                    }
                }
                if (Player::getIsRaised() == false)
                {
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && checkOrCallButton.getGlobalBounds().contains(translatedPosition))
                    {
                        player.check();
                    }
                    if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && raiseButton.getGlobalBounds().contains(translatedPosition) && player.getBettingValue() > Player::getHighestBet()&& player.getBettingValue() <= player.getMoney())
                    { 
                        player.raise(gamePot);
                    }
                }
                if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && foldButton.getGlobalBounds().contains(translatedPosition)) 
                {
					player.fold(); 
				}
                
            }
        }
        if (showStartScreen)
        {
            startScreen(window, showStartScreen);
        }
        else
        {
            mainScreen(window, player, foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton, gamePot); 
        }
        window.display();
       //endingScreen(window, "images/win.jpg");
    }
    return 0;
}