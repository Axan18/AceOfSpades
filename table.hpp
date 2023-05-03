#ifndef table_hpp
#define table_hpp
#include <SFML/Graphics.hpp>
#include "player.hpp"
void startScreen(sf::RenderWindow &window, bool& showStartScreen);
void endingScreen(sf::RenderWindow &window, std::string image);
void mainScreen(sf::RenderWindow& window, Player player);
#endif 