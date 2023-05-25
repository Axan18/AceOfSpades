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
    buttons(foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton, foldTexture, checkOrCallTexture, raiseTexture, plusTexture, minusTexture);
    deckOfCards cardDeck;
    cardDeck.shuffleDeck();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ace Of Spades");
    window.setFramerateLimit(60); 
    Pot gamePot(15);
    Player player(cardDeck[0],cardDeck[3], 15, 1000, 15);
    Bot bot1(cardDeck[1], cardDeck[4], 15, 1000, 15);
    Bot bot2(cardDeck[2], cardDeck[5], 15, 1000, 15);
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

                if (action.type == sf::Event::MouseButtonPressed&& action.mouseButton.button == sf::Mouse::Left && plusButton.getGlobalBounds().contains(translatedPosition))   
                {
                    player.betIncrease();
                }
                if (action.type == sf::Event::MouseButtonPressed && action.mouseButton.button == sf::Mouse::Left && minusButton.getGlobalBounds().contains(translatedPosition))
                {
                    player.betDecrease();
                }
            }
        }
        if (showStartScreen)
        {
            startScreen(window, showStartScreen);
        }
        else
        {
            mainScreen(window, player, foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton); 
            //sf::FloatRect foldButtonBounds = plusButton.getGlobalBounds();
            //std::cout << "Fold Button Bounds: left=" << foldButtonBounds.left << ", top=" << foldButtonBounds.top << ", width=" << foldButtonBounds.width << ", height=" << foldButtonBounds.height << std::endl;
            //// Analogicznie dla pozosta³ych przycisków
            //std::cout << "Fold Button Texture: " << foldButton.getTextureRect().width << std::endl; 

        }
        window.display();
       //endingScreen(window, "images/win.jpg");
    }
    return 0;
}