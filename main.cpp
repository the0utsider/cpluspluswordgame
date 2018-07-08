#include <iostream>
#include <string>
#include "FKelimeOyunu.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void Playgame();
FText GetValidGuess();
void PrintGameSummary();
bool AskToPlayAgain();

FKelimeOyunu BCGame; //Create an instance of game (init looks for constructor)

//entry point of app
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		Playgame();
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);

	return 0; //exits the app
}


//functions (or methods)
void PrintIntro()
{
	std::cout << "\n wadap brother...you haven't asked but im down in the dumps...\n";
	std::cout << "all I can think about is yummy food for my fat yeap sayer chin \n";
	std::cout << "lets play a little game..";
	std::cout << std::endl;
	return;
}

void Playgame()
{
	BCGame.Reset();
	std::cout << "\n Can you guess " << BCGame.GetHiddenWordLength();
	std::cout << " letter food I'm thinking of? \n";

	//loop asking for guesses while the game is not won
	//and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() < BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess(); //loop checking valid guesses

		//only submit valid guess to the game 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		

		std::cout << "Letters you guessed at correct place = " << BullCowCount.Bulls << "\n";
		std::cout << "Letter existing in this word = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// loops it until user enters valid guess
FText GetValidGuess()
{
	FText Guess = ""; //was inside, moved/declared outside of loop to avoid compiler warnings
	EGuessStatus Status = EGuessStatus::Invalid_Status; //declared or initialized to invalid status before loop so you can access it inside the loop scope
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() <<  ". Enter your guess : ";
		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters(isogram). \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Guess you entered should be all lowercase characters. \n";
			break;
		default:
			// assume guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep loop until getting no errors
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "\n You guessed it BRO! CONGRATS \n";
	}
	else
	{
		std::cout << "\n sadface without hamburger..halal kebab next time \n";
	}
}

bool AskToPlayAgain()
{
	std::cout << "play again? Y/n: ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
