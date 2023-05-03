#include <SFML/Graphics.hpp>
#include "table.hpp"


void startScreen(sf::RenderWindow& window, bool& showStartScreen)
{
	sf::Sprite start, aceOfSpades;
	sf::Texture gameName;
	gameName.loadFromFile("images/startScreen.jpg");
	aceOfSpades.setTexture(gameName);
	sf::Texture startButton;
	startButton.loadFromFile("images/startButton.png");
	start.setTexture(startButton);
	start.setPosition(480, 350);
	window.clear(sf::Color::Black);
	window.draw(aceOfSpades);
	window.draw(start);

	auto mousePosition = sf::Mouse::getPosition(window);
	auto translatedPosition = window.mapPixelToCoords(mousePosition);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.getGlobalBounds().contains(translatedPosition))
	{
		showStartScreen = false; // zmiana flagi, ¿eby przejœæ do ekranu gry
	}
}
void endingScreen(sf::RenderWindow &window, std::string image)
{
	sf::Sprite inscription;
	sf::Texture text;
	text.loadFromFile(image);
	inscription.setTexture(text);
	window.clear(sf::Color::Black);
	window.draw(inscription);
}
void mainScreen(sf::RenderWindow &window)
{
	sf::Sprite enemyCards[4], playerCards[2], commonCards[5], account[3], bet[3]; //cards & money
	sf::Sprite foldButton, checkOrCallButton, raiseButton, moneyButton, plusButton, minusButton; //buttons
	sf::Texture cardPlaceholder, playerCardsTexture[2], commondCardsTexture[5], foldTexture, checkOrCallTexture, raiseTexture, plusTexture,minusTexture; //textures
	cardPlaceholder.loadFromFile("images/cards/back.jpg");
	window.clear(sf::Color(0, 102, 0));
	//card size: 104.5x149
	//enemy cards positioning 
	enemyCards[0].setPosition(10, 10); 
	enemyCards[1].setPosition(10, 169); 
	enemyCards[2].setPosition(1165.5, 10); 
	enemyCards[3].setPosition(1165.5, 169); 
	//common cards positioning 
	int space = 169;
	commonCards[0].setPosition(231.5, 100);
	commonCards[1].setPosition(231.5 + 1*space, 100); 
	commonCards[2].setPosition(231.5 + 2*space, 100); 
	commonCards[3].setPosition(231.5 + 3*space, 100);
	commonCards[4].setPosition(231.5 + 4*space, 100);
	//player cards positioning
	playerCards[0].setPosition(505.5, 500);
	playerCards[1].setPosition(660, 500);
	//buttons positioning
	foldButton.setPosition(780, 575);
	checkOrCallButton.setPosition(905, 575);
	raiseButton.setPosition(1030, 575);
	plusButton.setPosition(1155, 575);
	minusButton.setPosition(1200, 575);
	
		for (int i = 0; i < 4; i++)							//setting textures
		{
			enemyCards[i].setTexture(cardPlaceholder);
			enemyCards[i].setScale(0.15, 0.15);
			window.draw(enemyCards[i]);
		}
		for (int i = 0; i < 5; i++)
		{
			commonCards[i].setTexture(cardPlaceholder); 
			commonCards[i].setScale(0.15, 0.15);  
			window.draw(commonCards[i]);   
		}

	playerCards[0].setTexture(cardPlaceholder);
	playerCards[1].setTexture(cardPlaceholder);
	playerCards[0].setScale(0.15, 0.15); 
	playerCards[1].setScale(0.15, 0.15);

	foldTexture.loadFromFile("images/buttons/fold.png"); 
	foldButton.setTexture(foldTexture);
	foldButton.setScale(0.75, 0.75);

	raiseTexture.loadFromFile("images/buttons/raise.png");
	raiseButton.setTexture(raiseTexture); 
	raiseButton.setScale(0.75, 0.75); 

	checkOrCallTexture.loadFromFile("images/buttons/check.png");
	checkOrCallButton.setTexture(checkOrCallTexture); 
	checkOrCallButton.setScale(0.75, 0.75);

	plusTexture.loadFromFile("images/buttons/plus.png"); 
	plusButton.setTexture(plusTexture);
	plusButton.setScale(0.2, 0.2);

	minusTexture.loadFromFile("images/buttons/minus.png"); 
	minusButton.setTexture(minusTexture);  
	minusButton.setScale(0.2, 0.2); 

	//drawing
	window.draw(minusButton);
	window.draw(plusButton);
	window.draw(checkOrCallButton);
	window.draw(foldButton);
	window.draw(raiseButton); 
	window.draw(playerCards[0]);
	window.draw(playerCards[1]);

}
