#pragma once
#include <string>

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

		int32 GetMaxTries() const;
		int32 getCurrentTry() const;
		int32 getHiddenWordLength() const;
		EGuessStatus CheckGuessValidity(FString) const;
		bool isGameWon() const;


		FBullCowCount SubmitGuess(FString);
		// counts bulls and cows and increasing turn number assuming valid guess


	private:
		int32 MyCurrentTry;
		int32 MyMaxTries;
		bool bGameWon;
		FString MyHiddenWord;
};