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
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	return;
}

FBullCowGame::FBullCowGame()
{
	reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::getCurrentTry() const {	return MyCurrentTry; }

int32 FBullCowGame::getHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::isGameWon() const { return bGameWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!isIsoGram(Guess)) //If Guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; //TODO Write function
	}
	else if (false)//If guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO Write function
	}
	else if (Guess.length() != getHiddenWordLength())//If guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK; //return okay
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
			return false; //word is not an isogram
		}
		else { //if not
			LetterSeen[Letter] = true;//add letter to map
		}
	}

	return true; //for example in cases where \0 is entered
}
