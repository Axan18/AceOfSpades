#include <SFML/Graphics.hpp>
#include "table.hpp"
#include <iostream>
#include "player.hpp"
#include "cards.hpp"

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
		sf::FloatRect foldButtonBounds = start.getGlobalBounds();
		std::cout << "Fold Button Bounds: left=" << foldButtonBounds.left << ", top=" << foldButtonBounds.top << ", width=" << foldButtonBounds.width << ", height=" << foldButtonBounds.height << std::endl;
		// Analogicznie dla pozosta³ych przycisków
		std::cout << "Fold Button Texture: " << start.getTextureRect().width << std::endl;
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
void buttons(sf::Sprite &foldButton, sf::Sprite  &checkOrCallButton, sf::Sprite  &raiseButton, sf::Sprite &moneyButton, sf::Sprite  &plusButton, sf::Sprite  &minusButton, sf::Texture &foldTexture, sf::Texture &checkOrCallTexture, sf::Texture &raiseTexture, sf::Texture &plusTexture, sf::Texture &minusTexture, bool isRaised)
{
	foldTexture.loadFromFile("images/buttons/fold.png");
	foldButton.setTexture(foldTexture);
	raiseTexture.loadFromFile("images/buttons/raise.png");
	raiseButton.setTexture(raiseTexture);
	if(isRaised==true)
		checkOrCallTexture.loadFromFile("images/buttons/call.png");
	else
	{
		checkOrCallTexture.loadFromFile("images/buttons/check.png");
	}
	checkOrCallButton.setTexture(checkOrCallTexture);
	plusTexture.loadFromFile("images/buttons/plus.png");
	plusButton.setTexture(plusTexture);
	minusTexture.loadFromFile("images/buttons/minus.png");
	minusButton.setTexture(minusTexture);

	foldButton.setScale(0.75f, 0.75f);
	raiseButton.setScale(0.75f, 0.75f);
	checkOrCallButton.setScale(0.75f, 0.75f);
	plusButton.setScale(0.2f, 0.2f);
	minusButton.setScale(0.2f, 0.2f);
	
	foldButton.setPosition(780, 575);
	checkOrCallButton.setPosition(905, 575);
	raiseButton.setPosition(1030, 575);
	plusButton.setPosition(1155, 575);
	minusButton.setPosition(1200, 575);

}

void mainScreen(sf::RenderWindow &window, Player player,Bot botx,Bot boty, sf::Sprite foldButton, sf::Sprite checkOrCallButton, sf::Sprite raiseButton, sf::Sprite moneyButton, sf::Sprite plusButton, sf::Sprite minusButton, Pot &pot, deckOfCards cards, int turn)
{
	sf::Font font;
	try
	{
		if (!font.loadFromFile("COMIC.ttf"))
		{
			throw std::invalid_argument("Wrong argument");
		}
	}
	catch (std::invalid_argument& e)
	{ 
		std::cout << "No font detected" << e.what(); 
	}
	sf::Text bot1;
	bot1.setFont(font); bot1.setPosition(150, 5); 
	bot1.setString("Player1"); bot1.setCharacterSize(25); bot1.setFillColor(sf::Color::White); //Player1 name

	sf::Text bot2;
	bot2.setFont(font); bot2.setPosition(900, 5);
	bot2.setString("Player2"); bot2.setCharacterSize(25); bot2.setFillColor(sf::Color::White); //Player2 name

	sf::Text player1;
	player1.setFont(font); player1.setPosition(230, 500);
	player1.setString("Player"); player1.setCharacterSize(25); player1.setFillColor(sf::Color::White); //Player name

	sf::Text bot1Account;
	int bot1Cash = botx.getMoney(); std::string bot1CashString = "Player1 money: " + std::to_string(bot1Cash);
	bot1Account.setFont(font); bot1Account.setPosition(150,35); 
	bot1Account.setString(bot1CashString); bot1Account.setCharacterSize(25); bot1Account.setFillColor(sf::Color::White); //Player1 money

	sf::Text bot2Account;
	int bot2Cash = boty.getMoney(); std::string bot2CashString = "Player2 money: " + std::to_string(bot2Cash);
	bot2Account.setFont(font); bot2Account.setPosition(900, 35);  
	bot2Account.setString(bot2CashString); bot2Account.setCharacterSize(25); bot2Account.setFillColor(sf::Color::White); //Player2 money
	
	sf::Text player1Account;
	int player1Cash = player.getMoney(); std::string player1CashString = "Player money: "+std::to_string(player1Cash);
	player1Account.setFont(font); player1Account.setPosition(230, 530); 
	player1Account.setString(player1CashString); player1Account.setCharacterSize(25); player1Account.setFillColor(sf::Color::White); //Player money

	sf::Text bot1CashIn;
	int bot1WholeBet = botx.getWholeBet(); std::string bot1WholeBetStr = "Player1 whole bet: " + std::to_string(bot1WholeBet);
	bot1CashIn.setFont(font); bot1CashIn.setPosition(150, 65);
	bot1CashIn.setString(bot1WholeBetStr); bot1CashIn.setCharacterSize(25); bot1CashIn.setFillColor(sf::Color::White); //Player1 cash in

	sf::Text bot2CashIn;
	int bot2WholeBet = boty.getWholeBet(); std::string bot2WholeBetStr = "Player2 whole bet: " + std::to_string(bot2WholeBet);
	bot2CashIn.setFont(font); bot2CashIn.setPosition(900, 65);
	bot2CashIn.setString(bot2WholeBetStr); bot2CashIn.setCharacterSize(25); bot2CashIn.setFillColor(sf::Color::White); //Player2 cash in

	sf::Text player1CashIn;
	int player1WholeBet= player.getWholeBet(); std::string player1WholeBetStr = "Player whole bet: "+std::to_string(player1WholeBet); 
	player1CashIn.setFont(font); player1CashIn.setPosition(230, 560); 
	player1CashIn.setString(player1WholeBetStr); player1CashIn.setCharacterSize(25); player1CashIn.setFillColor(sf::Color::White); //Player cash in

	sf::Text gamePot; 
	int potValue = pot.getPot(); 
	std::string potValueStr = "Pot: "+std::to_string(potValue);
	gamePot.setFont(font); gamePot.setPosition(600, 350);
	gamePot.setString(potValueStr); gamePot.setCharacterSize(25); gamePot.setFillColor(sf::Color::White); //Gamepot 
	
	sf::Text callValue;
	int callVal = Player::getHighestBet(); std::string callValStr = std::to_string(callVal); 
	callValue.setFont(font); callValue.setPosition(950, 530);
	callValue.setString(callValStr); callValue.setCharacterSize(25); callValue.setFillColor(sf::Color::White); // Call money

	sf::Text raiseValue;
	int betVal = player.getBettingValue(); std::string betValStr = std::to_string(betVal); 
	raiseValue.setFont(font); raiseValue.setPosition(1070, 530);
	raiseValue.setString(betValStr); raiseValue.setCharacterSize(25); raiseValue.setFillColor(sf::Color::White); //Raise money

	sf::Sprite enemyCards[4], playerCards[2], commonCards[5], account[3], bet[3]; //cards & money
	sf::Texture cardPlaceholder, playerCardsTexture[2], commonCardsTexture[5]; //textures
	cardPlaceholder.loadFromFile("images/cards/back.jpg");
	window.clear(sf::Color(0, 102, 0));
	//card size: 104.5x149
	//enemy cards positioning 
	enemyCards[0].setPosition(10, 10); 
	enemyCards[1].setPosition(10, 169); 
	enemyCards[2].setPosition(1165.5f, 10); 
	enemyCards[3].setPosition(1165.5f, 169);
	//enemy cards textures
	for (int i = 0; i < 4; i++)
	{
		enemyCards[i].setTexture(cardPlaceholder);
		enemyCards[i].setScale(0.19f, 0.19f);
		window.draw(enemyCards[i]);
	}
	//common cards positioning 
	int space = 169;
	commonCards[0].setPosition(231.5f, 100);
	commonCards[1].setPosition(231.5f + 1*space, 100); 
	commonCards[2].setPosition(231.5f + 2*space, 100); 
	commonCards[3].setPosition(231.5f + 3*space, 100);
	commonCards[4].setPosition(231.5f + 4*space, 100);
	//player cards positioning
	playerCards[0].setPosition(505.5f, 500);
	playerCards[1].setPosition(660, 500);

	//common cards textures
	switch (turn)
	{
	case 1:
		for (int i = 0; i < 5; i++)
		{
			commonCards[i].setTexture(cardPlaceholder); 
			commonCards[i].setScale(0.19f, 0.19f); 
			window.draw(commonCards[i]);  
		}
		break;
	case 2:
		for (int i = 0; i < 5; i++)
		{
			if (i < 3)
			{
				commonCardsTexture[i].loadFromFile("images/cards/" + cards[i] + ".jpg");
				commonCards[i].setTexture(commonCardsTexture[i]);
				commonCards[i].setScale(0.19f, 0.19f);
				window.draw(commonCards[i]);
			}
			else
			{
				commonCards[i].setTexture(cardPlaceholder);
				commonCards[i].setScale(0.19f, 0.19f);
				window.draw(commonCards[i]);
			}
		}
	case 3:
		for (int i = 0; i < 5; i++)
		{
			if (i < 3) 
			{ 
				commonCardsTexture[i].loadFromFile("images/cards/" + cards[i] + ".jpg"); 
				commonCards[i].setTexture(commonCardsTexture[i]); 
				commonCards[i].setScale(0.19f, 0.19f); 
				window.draw(commonCards[i]); 
			}
			else
			{
				commonCards[i].setTexture(cardPlaceholder); 
				commonCards[i].setScale(0.19f, 0.19f); 
				window.draw(commonCards[i]);  
			} 
		}
	case 4:
		for (int i = 0; i < 5; i++)
		{
				commonCardsTexture[i].loadFromFile("images/cards/" + cards[i] + ".jpg"); 
				commonCards[i].setTexture(commonCardsTexture[i]);  
				commonCards[i].setScale(0.19f, 0.19f);
				window.draw(commonCards[i]);
		}
	}

		
	playerCardsTexture[0].loadFromFile("images/cards/" + player.getCard(1) + ".jpg");
	playerCardsTexture[1].loadFromFile("images/cards/" + player.getCard(2) + ".jpg");
	playerCards[0].setTexture(playerCardsTexture[0]);
	playerCards[1].setTexture(playerCardsTexture[1]);
	playerCards[0].setScale(0.19f, 0.19f); 
	playerCards[1].setScale(0.19f, 0.19f);

	//drawing
	{
		window.draw(bot1);
		window.draw(bot2);
		window.draw(player1);
		window.draw(bot1Account);
		window.draw(bot2Account);
		window.draw(player1Account);
		window.draw(bot1CashIn);
		window.draw(bot2CashIn);
		window.draw(player1CashIn);
		window.draw(callValue);
		window.draw(raiseValue);
		window.draw(gamePot);
		window.draw(minusButton);
		window.draw(plusButton);
		window.draw(checkOrCallButton);
		window.draw(foldButton);
		window.draw(raiseButton);
		window.draw(playerCards[0]);
		window.draw(playerCards[1]);
	}
}
