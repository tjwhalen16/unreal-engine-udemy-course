// This is the console executable, that makes use fo the BullCow class
// This acts as the view in a MVC pattern, and is responsible for all
// user interaction. For game logic see the FBallCowGame class.
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Substitutions to begin practicing Unreal Engine syntax
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate game that is re-used

int main()
{
	do
	{
		PrintIntro();
		PlayGame();		
	}
	while (AskToPlayAgain());
	
	return 0; // Exit application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxGuesses();

	// Loop asking for guesses while the game is NOT won
	// and there are still guesses remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentGuess() <= MaxTries)
	{
		FText Guess = GetValidGuess();		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess); // Submit valid gues to game class

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ", Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}


// Loop until user gives a valid guess
FText GetValidGuess()
{
	while (true) // Loop will end when a valid input is entered
	{
		// Get a guess from the player
		FText Guess = "";
		std::cout << "Guess " << BCGame.GetCurrentGuess() << " of " << BCGame.GetMaxGuesses() << "> ";
		std::cout << "Enter you guess: ";
		std::getline(std::cin, Guess);

		// Check the guess's validity
		EGuessStatus Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::EWrongLength:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::ENotIsogram:
			std::cout << "Please enter an Isogram (no repeating letters)\n\n";
			break;
		case EGuessStatus::ENotLowerCase:
			std::cout << "Please enter a word with only lower-case letters\n\n";
			break;
		default:
			return Guess; // Loop ends here when a valid input is entered
			break;
		}
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
	return Response[0] == 'y' || Response[0] == 'Y';
}



void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "You win!\n";
	}
	else
	{
		std::cout << "Better luck next time\n";
	}
}
