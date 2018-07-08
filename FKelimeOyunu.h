#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FKelimeOyunu 
{
public:
	FKelimeOyunu(); //constructor
	
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	int32 GetMaxTries() const;
	void Reset(); //TODO enrich return value.
	//counts bulls and cows, increases try number after valid guess.
	FBullCowCount SubmitValidGuess(FString);

	FString SelectIsogram();


private: //compile time values removed, see constructor values
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool bIsLowercase(FString) const;
	bool bIsIsogram(FString) const;

};