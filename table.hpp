#ifndef table_hpp
#define table_hpp
#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "cards.hpp"
void startScreen(sf::RenderWindow &window, bool& showStartScreen);
void endingScreen(sf::RenderWindow &window, std::string image);
void mainScreen(sf::RenderWindow& window, Player player, Bot bot1, Bot bot2, sf::Sprite foldButton, sf::Sprite checkOrCallButton, sf::Sprite raiseButton, sf::Sprite moneyButton, sf::Sprite plusButton, sf::Sprite minusButton, Pot &pot, deckOfCards cards, int turn);
void buttons(sf::Sprite& foldButton, sf::Sprite& checkOrCallButton, sf::Sprite& raiseButton, sf::Sprite& moneyButton, sf::Sprite& plusButton, sf::Sprite& minusButton, sf::Texture &foldTexture, sf::Texture &checkOrCallTexture, sf::Texture &raiseTexture, sf::Texture &plusTexture, sf::Texture &minusTexture, bool isRaised);
#endif 