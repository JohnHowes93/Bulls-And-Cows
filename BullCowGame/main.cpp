/* 

This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	do 
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());
	return 0;
}

void PrintIntro()
{
	std::cout << "\n\n ************** \n\n";
	std::cout << "\n\nWelcome to Bulls & Cows, a fun word game. \n";
	std::cout << "\n\n ************** \n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram? \n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{ 
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);	// Submit valid guess to the game
		std::cout << "Bulls = " << BullCowCount.Bulls << "\n"; 
		std::cout << "Cows = " << BullCowCount.Cows << "\n \n";
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess() // Loops continuously until the user gives a valid guess
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText PlayerGuess = "";
	do {
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry ;
	std::cout << ". Enter your guess : \n";
	std::getline(std::cin, PlayerGuess);
	Status = BCGame.CheckGuessValidity(PlayerGuess);
	switch (Status)
	{
	case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word";
		break;
	case EGuessStatus::Not_Isogram:
		std::cout << "Please enter an isogram";
		break;
	case EGuessStatus::Not_Lowercase:
		std::cout << "Please use lowercase";
		break;
	default:
		break;
	}
	std::cout << std::endl;
	} while (Status != EGuessStatus::Ok);
	return PlayerGuess;

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}


void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n\n ************** \n\n";
		std::cout << "\n\n Congratulations, you win! \n\n";
		std::cout << "\n\n ************** \n\n";
	}
	else
	{
		std::cout << "\n\n ************** \n\n";
		std::cout << "\n\n Uh oh, you lose \n\n";
		std::cout << "\n\n ************** \n\n";
	}
	return;
}

