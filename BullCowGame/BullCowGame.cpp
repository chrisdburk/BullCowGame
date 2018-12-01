// BullCowGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/**/

#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
FText getGuess();
bool AskToPlayAgain();

FBullCowGame FBCGame; //Instantiate

int32 main()
{
	bool bPlayAgain = false;
	do
	{ 
		printIntro();
		playGame();
		
		bPlayAgain = AskToPlayAgain();
	}
	while(bPlayAgain);
	return 0;
}

//introduce the game
void printIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << FBCGame.getHiddenWordLength() << " letter isogram that I am thinking of?" << std::endl;
	std::cout << std::endl;
	return;
}

void playGame() {
	FBCGame.reset();
	int32 MaxTries = FBCGame.GetMaxTries();

	for (int32 i = 0; i < MaxTries; i++) { //TODO change from for to while loop once we validate tries
		FText Guess = getGuess(); //TODO make loop checking valid

		FBullCowCount BullCowCount = FBCGame.SubmitGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << "\n\n";

		std::cout << "You guessed:  " << Guess << std::endl;
		//TODO Add a game summary
	}
	return;
}

//get the guess from the player
FText getGuess() 
{
	FText guess = "";
	EGuessStatus Status = EGuessStatus::Not_Isogram;
	do {
		std::cout << "Try " << FBCGame.getCurrentTry() << ":  Please enter your guess:  ";
		std::getline(std::cin, guess);

		Status = FBCGame.CheckGuessValidity(guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a word without repeating letters";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << FBCGame.getHiddenWordLength() << " letter word";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter all lowercase letters";
			break;
		default:
			//assume guess is valid
			break;

		std::cout << std::endl;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
}
