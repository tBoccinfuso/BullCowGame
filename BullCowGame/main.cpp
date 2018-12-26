#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Faking Unreal syntax
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

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
	
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// Play the game
void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guess while the game is NOT won, and tries still left
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();		

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// Submit valid guess to game, print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls << " ";
		std::cout << "Cows = " << BullCowCount.Cows << std::endl;
	}

	PrintGameSummary();
	// TODO add a game summary
}

// get valid user guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid;

	// Keep looping till we get no errors
	do
	{		
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Guess #" << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);


		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Guess is not an isogram! (Word without repeating letters)\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter guess in all lowercase. \n\n";
			break;
		default: // Status = OK
			break;
		}
		
	} while (Status != EGuessStatus::OK);

	return Guess;
}

// Ask player if they want to play again
bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again with the same word? (y/n)\n";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done - you win!\n";
	}
	else
	{
		std::cout << "You lost!\n";
	}
}