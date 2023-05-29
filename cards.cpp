#include <vector>
#include <string>
#include "cards.hpp"
#include <algorithm>
#include <random>
#include <chrono>

deckOfCards::deckOfCards() : std::vector<std::string>({
	"S14", "S02", "S03", "S04", "S05", "S06", "S07", "S08", "S09", "S10", "S11", "S12", "S13",
	"H14", "H02", "H03", "H04", "H05", "H06", "H07", "H08", "H09", "H10", "H11", "H12", "H13",
	"D14", "D02", "D03", "D04", "D05", "D06", "D07", "D08", "D09", "D10", "D11", "D12", "D13",
	"C14", "C02", "C03", "C04", "C05", "C06", "C07", "C08", "C09", "C10", "C11", "C12", "C13" })
{}
void deckOfCards::shuffleDeck()
{
	std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
	std::shuffle(this->begin(), this->end(), rng);
}

Card::Card(int value, std::string suit) : value(value), suit(suit) {};
deckOfCards::deckOfCards(deckOfCards& other) 
	: std::vector<std::string>(other) {}; // copy constructor