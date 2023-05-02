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
    Pot gamePot(15);
    Player player();
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
        window.clear(); // wyczyszczenie okna
        mainScreen(window);
       // startScreen(window);
       //endingScreen(window, "images/win.jpg");
        window.display();
    }
    return 0;
}