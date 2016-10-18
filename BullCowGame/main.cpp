/* This is the console exe, that makes use of the BullCow class
This acts as the view in the MVC patter, and is responsible for all
the user interaction.  For game logic see FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make syntax UnReal friendly
using Ftext = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;  //instantiate a new game

//entry point to the application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	
	return 0; //exit the application
}

//introduce the game
void PrintIntro() {
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
}

//plays the game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the number of turns asking for guesses
	while( !BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ){

		Ftext Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

//get a guess from the player
Ftext GetValidGuess() {

	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do {
		int32 CurrentTries = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTries << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		default:
			break;
		}
	} while (Status == EGuessStatus::OK);

	return Guess;

}

//asks player to play again
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	Ftext Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else {
		std::cout << "BETTER luck next time!\n";
	}
}
