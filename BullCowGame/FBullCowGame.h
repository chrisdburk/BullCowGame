/*
Contains the game logic (no views or user interaction)
Game is a guess the word game.
*/

#pragma once
#include <string>

//Make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
	public:
		FBullCowGame();
		void reset();


		int32 getCurrentTry() const;
		int32 getHiddenWordLength() const;
		EGuessStatus CheckGuessValidity(FString) const;
		bool isGameWon() const;

		int32 GetMaxTries() const;

		FBullCowCount SubmitGuess(FString);
		// counts bulls and cows and increasing turn number assuming valid guess


	private:
		int32 MyCurrentTry;
		bool bGameWon;
		FString MyHiddenWord;

		bool isIsoGram(FString) const;
		bool isLowerCase(FString) const;
};