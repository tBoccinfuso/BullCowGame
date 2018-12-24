#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Faking Unreal syntax
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

// instantiate a new game (Class)
FBullCowGame BCGame;

// entry point
int main() {
	bool PlayAgain = false;
	do
	{
		PrintIntro();

		PlayGame();
		
		PlayAgain = AskToPlayAgain();

		std::cout << std::endl;
		system("pause");

	} while (PlayAgain == true);
	
	return 0;
}

// introduce the game
void PrintIntro() {
	constexpr int32 WORD_LENGTH = 9;
	
	std::cout << "Welcome to Bulls & Cows, a fun word game.\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

// Play the game
void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	for (int32 count = 1; count <= MaxTries; count++)
	{	
		// TODO make loop to check for validate guesses
		FBullCowCount BullCowCount = BCGame.SubmitGuess(GetGuess());
		// Submit valid guess to game, print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
	}

	// TODO add a game summary
}

// get user guess
FText GetGuess()
{
	FText Guess = "";
	int32 CurrentTry = BCGame.GetCurrentTry();

	std::cout << "Guess #" << CurrentTry << " Enter your guess: ";
	std::getline(std::cin, Guess);

	return Guess;
}

// Ask player if they want to play again
bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again? (y/n)\n";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}