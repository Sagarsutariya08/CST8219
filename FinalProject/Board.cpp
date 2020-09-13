#include "Board.h"
#include "Settings.h"
#include<iostream>
#include <SFML/Audio.hpp>

using namespace std;
GameBoard::GameBoard(StateManager* stateManager) :
	GameScreen(stateManager),
	resolveTimeout(new SetTimeout()),
	playingField()
{
	playingField.setSize(calculatePlayingFieldScale());
	playingField.setCenter(calculateDeckSize() / 2.f);
	playingField.setViewport(sf::FloatRect(0.0625f, 0.0625f, 0.875f, 0.875f));
	deck = createDeck(stateManager->gameSettings->boardSize);
}

sf::Sound GameBoard::happysound(AssetManager::getInstance()->getSoundBuffer("HappySound.wav"));
sf::Sound GameBoard::sadsound(AssetManager::getInstance()->getSoundBuffer("SadSound.wav"));

GameBoard::~GameBoard()
{
	delete resolveTimeout;
	for (size_t i = 0; i < deck.size(); i++)
	{
		delete deck[i];
	}
	deck.clear();
}

void GameBoard::renderScreen(sf::RenderWindow& window)
{
	GameScreen::renderScreen(window);
	window.setView(playingField);
	renderDeck(window);
}

void GameBoard::updateScreen(sf::Time deltaTime)
{
	resolveTimeout->update(deltaTime);
	updateDeck(deltaTime);
}

void GameBoard::handleMouseClick(sf::Vector2f mousePosition)
{
	if (resolveTimeout->delaying)		// disable click events while resolving
	{
		return;
	}
	Card* clickedCard = cardClicked(mousePosition);
	if (clickedCard)
	{
		handleCardClick(clickedCard);
	}
}

std::vector<Card*> GameBoard::createDeck(sf::Vector2u boardSize)
{
	std::vector<Card*> deck;
	unsigned deckSize = boardSize.x * boardSize.y;
	//	unsigned deckSize = 20;
	unsigned pairsPerSuit = deckSize / 2 / Card::Suit::COUNT;
	unsigned cardIndex = 0;

	for (unsigned i = 0; i < Card::Suit::COUNT; i++) {
		for (unsigned j = 0; j < pairsPerSuit * 2; j++)
		{
			Card* card = new Card(cardIndex, static_cast<Card::Suit>(i));
			deck.push_back(card);
			cardIndex++;
		}
	}

	if ((deckSize / 2) % Card::Suit::COUNT)
	{
		for (size_t i = 0; i < (deckSize / 2) % Card::Suit::COUNT; i++)
		{
			for (size_t j = 0; j < 2; j++)
			{
				Card* card = new Card(cardIndex, static_cast<Card::Suit>(i));
				deck.push_back(card);
				cardIndex++;
			}
		}
	}

	std::random_device rd;
	std::mt19937 seed(rd());
	std::shuffle(std::begin(deck), std::end(deck), seed);
	int index = 0;
	for (unsigned i = 0; i < boardSize.x; i++)
	{
		for (unsigned j = 0; j < boardSize.y; j++)
		{
			sf::Vector2u position(i, j);
			deck[index]->setPosition(position);
			index++;
		}
	}
	return deck;
}

void GameBoard::renderDeck(sf::RenderWindow& window)
{
	for (size_t i = 0; i < deck.size(); i++)
	{
		deck[i]->renderCard(window);
	}
}

void GameBoard::updateDeck(sf::Time deltaTime)
{
	for (size_t i = 0; i < deck.size(); i++)
	{
		deck[i]->updateCard(deltaTime);
	}
}

Card* GameBoard::cardClicked(sf::Vector2f mousePosition)
{
	for (size_t i = 0; i < deck.size(); i++)
	{
		if (deck[i]->isCardClicked(mousePosition))
		{
			stateManager->getPlayers()[0]->increaseClickScore();
			return deck[i];
			break;
		}
	}
	return nullptr;
}

void GameBoard::handleCardClick(Card* clickedCard)
{
	std::vector<Card*>::iterator itSolved = std::find(solvedCards.begin(), solvedCards.end(), clickedCard);
	if (itSolved != solvedCards.end())			// ignore click on solved cards
	{
		return;
	}

	std::vector<Card*>::iterator itRevealed = std::find(revealedCards.begin(), revealedCards.end(), clickedCard);
	if (itRevealed == revealedCards.end())		// if card not already revealed, reveal it
	{
		revealedCards.push_back(clickedCard);
		clickedCard->flipCard();
	}

	if (revealedCards.size() == 2)				// when two cards are revealed, start resolving with time delay
	{
		if (revealedCards[0]->getSuit() == revealedCards[1]->getSuit())			// check if the two card are a pair
		{

			happysound.play();
			auto callback = std::bind(&GameBoard::resolvePair, this, true);
			resolveTimeout->startTimeout(sf::seconds(0.5), callback);
		}
		else
		{
			sadsound.play();
			auto callback = std::bind(&GameBoard::resolvePair, this, false);
			resolveTimeout->startTimeout(sf::seconds(1), callback);
		}
	}
}

void GameBoard::resolvePair(bool isPair)
{
	if (isPair)
	{


		solvedCards.insert(solvedCards.end(), revealedCards.begin(), revealedCards.end());
		revealedCards.clear();

		if (solvedCards.size() == deck.size())
		{
			finishGame();
			return;
		}
	}
	else
	{

		for (size_t i = 0; i < revealedCards.size(); i++)
		{
			revealedCards[i]->flipCard();
		}
		revealedCards.clear();
	}
}

void GameBoard::finishGame()
{
	stateManager->switchScreen(StateManager::Screen::EndScreen);
}

sf::Vector2f GameBoard::calculateDeckSize()
{
	sf::Vector2f deckSize;
	deckSize.x = stateManager->gameSettings->boardSize.x * (Card::getSize().x + 10.f);
	deckSize.y = stateManager->gameSettings->boardSize.y * (Card::getSize().y + 10.f);
	return deckSize;
}

sf::Vector2f GameBoard::calculatePlayingFieldScale()
{
	sf::Vector2f playingFieldSize(WIDTH * 0.875f, HEIGHT * 0.875f);
	sf::Vector2f deckSize = calculateDeckSize();
	if (deckSize.x > playingFieldSize.x)
	{
		playingFieldSize.x = deckSize.x;
		playingFieldSize.y = playingFieldSize.x;
	}
	if (deckSize.y > playingFieldSize.y)
	{
		playingFieldSize.y = deckSize.y;
		playingFieldSize.x = playingFieldSize.y;
	}
	return playingFieldSize;
}


