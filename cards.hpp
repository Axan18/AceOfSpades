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
struct Card
{
	int value;
	std::string suit;
	Card(int value, std::string suit);

	bool operator<(const Card& other) const {
		return value < other.value;
	}
};
#endif