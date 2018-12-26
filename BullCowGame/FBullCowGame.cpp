#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map // replace map with Unreal syntax

// Methods for the matching .h class

// constructor
FBullCowGame::FBullCowGame()
{
	Reset();
}

// Getters
//int FBullCowGame::GetMaxTries() const
//{
//	return MyMaxTries;
//}

// return the amount of tries you have based off word length
int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,6}, {5,10}, {6,15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

// return the length of private var MyHiddenWord - set by Reset()
int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

// Setters
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	return;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	// if guess is not isogram, return error
	if (!IsIsogram(guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if guess isn't all lowercase, return error
	else if (!IsLowercase(guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if guess length is wrong, return error
	else if (guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

// recieve a valid guess, increment turn, return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	FBullCowCount BullCowCount;
	MyCurrentTry++;
	int32 WordLength = MyHiddenWord.length(); // assume same length as guess

	// loop through all letters in hidden word
	
	for (int32 i = 0; i < WordLength; i++)
	{
		// compare letters against the guess
		for (int32 j = 0; j < WordLength; j++)
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
		
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

// check if word is isogram
bool FBullCowGame::IsIsogram(FString guess) const
{
	TMap<char, bool> LetterSeen;

	// treat 0 and 1 letter words as isograms
	if (guess.length() <= 1)
	{
		return true;
	}	

	// loop trough all the letters of the guess
	for (char letter : guess )
	{
		letter = tolower(letter);

		// if the letter is in the map, we do not have an isogram
		if (LetterSeen[letter]) { return false;	}
		else
		{
			LetterSeen[letter] = true; // add letter to the map
		}
	}
	

	// if not, add letter to the map
	return true;
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	for (char letter : guess)
	{
		if (!islower(letter))
		{
			return true;
		}
	}
}
