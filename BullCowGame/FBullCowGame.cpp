#pragma once

#include "pch.h"
#include "FBullCowGame.h"
#include<map>

#define TMAP std::map

void FBullCowGame::reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";

	bGameWon = false;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	return;
}

FBullCowGame::FBullCowGame(){ reset(); } //default constructor

int32 FBullCowGame::getCurrentTry() const {	return MyCurrentTry; }

int32 FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::isGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!isIsoGram(Guess)) //If Guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!isLowerCase(Guess))//If guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != getHiddenWordLength())//If guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK; 
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMAP<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

//Receives a valid guess, increases turn and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in HiddenWord
	for (int32 HWChar = 0; HWChar < HiddenWordLength; HWChar++)
	{
		//loop through all letters in guess
		for (int32 GuessChar = 0; GuessChar < HiddenWordLength; GuessChar++)
		{
			if (Guess[GuessChar] == MyHiddenWord[HWChar])
			{
				if (HWChar == GuessChar)
				{
					//increment bulls if they are in the same place
					BullCowCount.Bulls++;
				}
				else
				{
					//increment cows
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == getHiddenWordLength()) { bGameWon = true; }
	return BullCowCount;
}

bool FBullCowGame::isIsoGram(FString Guess) const
{
	//treat 0 and 1 letter strings as isograms
	if (Guess.length() <= 1) { return true;	}

	//set up map
	TMAP <char, bool> LetterSeen;
	//loop through all letters
	for (auto Letter : Guess) {
		Letter = tolower(Letter);

		if (LetterSeen[Letter]) {//if letter is in map
			return false; 
		}
		else { //if not
			LetterSeen[Letter] = true;
		}
	}

	return true; //for example in cases where \0 is entered
}

bool FBullCowGame::isLowerCase(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
