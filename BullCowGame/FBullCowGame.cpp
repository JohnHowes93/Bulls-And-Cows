#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){Reset();}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	bGameIsWon = false;
	constexpr int32 MAX_TRIES = 5;
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	const FString HIDDEN_WORD = "house";
	MyHiddenWord = HIDDEN_WORD;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (Guess.length() != MyHiddenWord.length()) 
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else
	{
		return EGuessStatus::Ok;
	}
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // Assumes the guess will be same length as hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // increment bulls if they're in the same place
				}
				else 
				{ 
					BullCowCount.Cows++; // increment cows if not
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

bool FBullCowGame::IsIsogram(FString Word) const 
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) 
		{ 
			return false; 
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; 
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (islower(Letter)) { return false; }
		else { return true; }
	}
	return false;
}
