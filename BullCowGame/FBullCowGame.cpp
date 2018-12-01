#include "pch.h"
#include "FBullCowGame.h"

void FBullCowGame::reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";
	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	return;
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
	return BullCowCount;
}

FBullCowGame::FBullCowGame()
{
	reset();
}

int32 FBullCowGame::GetMaxTries() const
{
	return MyMaxTries;
}

int32 FBullCowGame::getCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::getHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) //If Guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false)//If guess isn't lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != getHiddenWordLength())//If guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
		return EGuessStatus::OK; //return okay
}
