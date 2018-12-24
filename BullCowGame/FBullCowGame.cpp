#include "FBullCowGame.h"

// Methods for the matching .h class

// constructor
FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getters
int FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

// Setters
void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";

	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;

	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

bool FBullCowGame::CheckGuessValidity(FString)
{
	return false;
}

// recieve a valid guess, increment turn, return count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	FBullCowCount BullCowCount;

	// increment the turn number
	MyCurrentTry++;

	// loop through all letters in guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		// compare letters against the hidden word
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				// if they are the same
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		

	return BullCowCount;
}
