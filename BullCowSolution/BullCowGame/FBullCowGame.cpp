#include "FBullCowGame.h"
#include <map>
#define TMap std::map // Substitutions to begin practicing Unreal Engine syntax


FBullCowGame::FBullCowGame() // Constructor
{
	Reset();
}

int32 FBullCowGame::GetCurrentGuess() const { return CurrentGuess; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxGuesses() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4},{ 4, 7 },{ 5, 10 },{ 6, 15 },{ 7, 20 } };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	CurrentGuess = 1;
	HiddenWord = "steak"; // This MUST be an isogram
	bGameIsWon = false;
}

// Checks a guess against the game rules for validity
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	
	if (!IsIsogram(Guess)) // If the guess isn't an isogram
	{
		return EGuessStatus::ENotIsogram;
	}
	else if (!IsLowercase(Guess)) // If the guess isn't all lowercase
	{
		return EGuessStatus::ENotLowerCase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // If the guess length is wrong
	{
		return EGuessStatus::EWrongLength;
	}
	else
	{
		// Otherwise, return valid
		return EGuessStatus::EValid;
	}
}

// Submits a guess
// Assumes the guess is valid
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	CurrentGuess++;
	FBullCowCount BullCowCount;

	// Loop through all letters in the hidden word
	for (int32 i = 0; i < GetHiddenWordLength(); i++)
	{
		// Compare letters in the guess against the guess
		for (int32 j = 0; j < GetHiddenWordLength(); j++)
		{			
			if (HiddenWord[i] == Guess[j]) // If they match
			{
				if (i == j) // If they are in the same place
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
	if (GetHiddenWordLength() == BullCowCount.Bulls) // Check if game is won
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}

// Returns true if the word is an isogram (a.k.a. no repeats)
bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() < 2) { return true; }

	TMap<char, bool> LettersSeen;

	// Loop over each char in Guess
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);		
		if (LettersSeen[Letter]) // If the char has been seen already
		{
			return false; // Not an isogram
		}
		else
		{
			LettersSeen[Letter] = true; // Mark the char as seen
		}			
	}		
	return true;
}

// Returns True if the word is lowercase
bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter != ' ' && !islower(Letter)) // Skip over spaces and end-of-string characters, they return false
		{
			return false;
		}
	}
	return true;
}
