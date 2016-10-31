// This class contains game logic for the Bull Cow Game.
// The only way to change the hidden word is to change its value in the Reset method.
// Rules:
// 1) Only supports words between 3 and 7 letters inclusive
// 2) Guesses must be lowercase
// 3) Guesses must be the same size as the hidden word
// 4) Guesses must be isograms (a.k.a. no repeating letters)
// 5) Guesses must be single words, will not work for multiple words separated by spaces
// 6) Bulls are correct letters in the correct spot
// 7) Cows are correct letters in the incorrect spot
#pragma once

#include <string>

// Substitutions to begin practicing Unreal Engine syntax
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	EValid,
	ENotIsogram,
	EWrongLength,
	ENotLowerCase
};

class FBullCowGame
{
public:	
	FBullCowGame(); // Constructor
	int32 GetMaxGuesses() const;
	bool IsGameWon() const;
	int32 GetCurrentGuess() const;
	EGuessStatus CheckGuessValidity(FString) const;
	int32 GetHiddenWordLength() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
private:
	int32 CurrentGuess;
	FString HiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString Word) const;
	bool IsLowercase(FString Word) const;
};
