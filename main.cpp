#include "table.hpp"
#include "cards.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <stack>
#include <string>
#include "player.hpp"

int main()
{
    deckOfCards cardDeck;
    cardDeck.shuffleDeck();
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Ace Of Spades");
    window.setFramerateLimit(60); 
    Pot gamePot(15);
    Player player();
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
        }
        if (showStartScreen)
        {
            startScreen(window, showStartScreen);
        }
        else
        {
            mainScreen(window);
        }
        window.display();
       //endingScreen(window, "images/win.jpg");
    }
    return 0;
}