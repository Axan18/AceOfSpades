#ifndef cards_hpp
#define cards_hpp
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
class deckOfCards : public std::vector<std::string>
{
public:
	deckOfCards();
	void shuffleDeck();
};
#endif