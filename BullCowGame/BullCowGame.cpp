// BullCowGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/*

*/
#pragma once

#include "pch.h"
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void printIntro();
void playGame();
FText getGuess();
void PrintGameSummary(bool);
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
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << FBCGame.getHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void playGame() {
	FBCGame.reset();
	int32 MaxTries = FBCGame.GetMaxTries();

	//Loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while(!FBCGame.isGameWon() && (FBCGame.getCurrentTry() <= FBCGame.GetMaxTries())) {
		FText Guess = getGuess();

		FBullCowCount BullCowCount = FBCGame.SubmitGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ".  Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary(FBCGame.isGameWon());
	return;
}

//get the guess from the player
FText getGuess() 
{
	FText guess = "";
	EGuessStatus Status = EGuessStatus::Not_Isogram;
	do {
		std::cout << "Try " << FBCGame.getCurrentTry() << " of " << FBCGame.GetMaxTries() << ":  Please enter your guess:  ";
		std::getline(std::cin, guess);

		Status = FBCGame.CheckGuessValidity(guess);

		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "please enter a word without repeating letters\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "please enter a " << FBCGame.getHiddenWordLength() << " letter word\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "please enter all lowercase letters\n\n";
			break;
		default:
			//assume guess is valid
			break;

		std::cout << std::endl;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors

	return guess;
}

void PrintGameSummary(bool bGameWon) {
	if (bGameWon)
	{
		std::cout << "CONGRATS!  YOU WIN!\n";
	}else {
		std::cout << "Better luck next time.\n";
	}
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? with the same hidden word(y/n)";
	FText response = "";
	std::getline(std::cin, response);

	return (response[0] == 'y') || (response[0] == 'Y');
}